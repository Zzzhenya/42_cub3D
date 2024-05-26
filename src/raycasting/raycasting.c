/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:00:20 by ohladkov          #+#    #+#             */
/*   Updated: 2024/05/26 17:17:48 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	cast_all_rays(t_data *data, t_player *player, t_ray *ray)
{
	init_struct_ray(ray, player);
	ray->ray_count = 0;
	ray->ray_angle = player->pa_rad - (FOV_R / 2);
	while (ray->ray_count < CASTED_RAYS)
	{
		cast_ray(data, player, ray);
		draw_player_dir(data, ray->wall_hit_x, ray->wall_hit_y);
		ray->ray_angle += FOV_R / CASTED_RAYS;
		ray->ray_count++;
		update_ray(ray);
	}
}

void	cast_ray(t_data *data, t_player *player, t_ray *ray)
{
	(void)data;
	float	x_step;
	float	y_step;
	float	x_intercept;
	float	y_intercept;
	float	hor_wall_hit_x;
	float	hor_wall_hit_y;
	int		found_hor_wall_hit = 0;

	// ---------------------- horisontal ray-grid intersection --------------
	
	// find the y-coordinate of the closest hor.intersection
	
	y_intercept = floor(player->py / CELLSIZE) * CELLSIZE;
	if (ray->down)
		y_intercept += CELLSIZE;

	// find the x-coordinate of the closest hor.intersection

	x_intercept = player->px + (y_intercept - player->py) / tan(ray->ray_angle);
	
	// calculate for increment xstep and ystep

	y_step = CELLSIZE;
	if (ray->up)
		y_step *= -1;

	x_step = CELLSIZE / tan(ray->ray_angle);
	if (ray->left && (x_step > 0))
		x_step *= -1;
	else if (ray->right && (x_step < 0))
		x_step *= -1;

	float next_horz_touch_x = x_intercept;
	float next_horz_touch_y = y_intercept;

	// if (ray->up)
	// 	next_horz_touch_y--;
		
	// increment x-step and y_step until we find a wall
	while (next_horz_touch_x >= 0 && next_horz_touch_x <= (15 * CELLSIZE) && next_horz_touch_y >= 0 && next_horz_touch_y <= (CELLSIZE * data->rows))
	{
		printf("next_horz_touch_x - %f |  next_horz_touch_y - %f\n", next_horz_touch_x, next_horz_touch_y);
		printf("x_step - %f |  y_step - %f\n", x_step, y_step);
		if (has_wall_at(data, next_horz_touch_x, next_horz_touch_y - ray->up))
		{
			found_hor_wall_hit = 1;
			hor_wall_hit_x = next_horz_touch_x;
			hor_wall_hit_y = next_horz_touch_y;
			break ;
		}
		else
		{
			next_horz_touch_x += x_step;
			next_horz_touch_y += y_step;
		}
	}


	// ---------------------- vertical ray-grid intersection ----------------

	int		found_vert_wall_hit = 0;
	float	vert_wall_hit_x;
	float	vert_wall_hit_y;

	// find the x-coordinate of the closest vertical intersection

	x_intercept = floor(player->px / CELLSIZE) * CELLSIZE;
	if (ray->right)
		x_intercept += CELLSIZE;

	// find the y-coordinate of the closest vertical intersection

	y_intercept = player->py + (x_intercept - player->px) * tan(ray->ray_angle);

	// calculate for increment xstep and ystep

	x_step = CELLSIZE;
	if (ray->left)
		x_step *= -1;

	y_step = CELLSIZE * tan(ray->ray_angle);
	if (ray->up && (y_step > 0))
		y_step *= -1;
	else if (ray->down && (y_step < 0))
		y_step *= -1;

	float next_vert_touch_x = x_intercept;
	float next_vert_touch_y = y_intercept;

	// if (ray->left)
	// 	next_vert_touch_x--;

	// increment x-step and y_step until we find a wall
	while (next_vert_touch_x >= 0 && next_vert_touch_x <= (15 * CELLSIZE) && next_vert_touch_y >= 0 && next_vert_touch_y <= (CELLSIZE * data->rows))
	{
		if (has_wall_at(data, next_vert_touch_x - ray->left, next_vert_touch_y))
		{
			found_vert_wall_hit = 1;
			vert_wall_hit_x = next_vert_touch_x;
			vert_wall_hit_y = next_vert_touch_y;
			break ;
		}
		else
		{
			next_vert_touch_x += x_step;
			next_vert_touch_y += y_step;
		}
	}

	// calculate both horizontal and vertical distances and choose the smalest value
	float	horz_hit_distance;
	float	vert_hit_distance;

	if (found_hor_wall_hit)
		horz_hit_distance = get_distance(player->px, player->py, hor_wall_hit_x, hor_wall_hit_y);
	else
		horz_hit_distance = MAX_VALUE;
	
	if (found_vert_wall_hit)
		vert_hit_distance = get_distance(player->px, player->py, vert_wall_hit_x, vert_wall_hit_y);
	else
		vert_hit_distance = MAX_VALUE;

	// olny store the smallest of the distances
	if (horz_hit_distance < vert_hit_distance)
	{
		ray->wall_hit_x = hor_wall_hit_x;
		ray->wall_hit_y = hor_wall_hit_y;
		ray->distance = horz_hit_distance;
		ray->vert_hit = 0;
	}
	else
	{
		ray->wall_hit_x = vert_wall_hit_x;
		ray->wall_hit_y = vert_wall_hit_y;
		ray->distance = vert_hit_distance;
		ray->vert_hit = 1;
	}
}
