/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:00:20 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/04 21:47:25 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	cast_all_rays(t_data *data, t_player *player, t_ray *ray, float scale_map)
{
	init_struct_ray(ray, player);
	ray->ray_count = 0;
	while (ray->ray_count < CASTED_RAYS)
	{
		cast_ray(data, player, ray);
		draw_player_dir(data, ray->wall_hit_x, ray->wall_hit_y, scale_map);
		ray->ray_count++;
		ray->ray_angle += ((60 * (PI / 180)) / CASTED_RAYS);
		update_ray_angle(ray);
	}
}

void	cast_ray(t_data *data, t_player *player, t_ray *ray)
{
	(void)data;
	float	x_step;
	float	y_step;
	float	x_intercept;
	float	y_intercept;
	float	horz_wall_hit_x;
	float	horz_wall_hit_y;
	int		found_horz_wall_hit = 0;
	int 	len;

	// ---------------------- horisontal ray-grid intersection --------------

	// find the y-coordinate of the closest hor.intersection

	y_intercept = floor(player->py / TILE_SIZE) * TILE_SIZE;
	if (ray->down)
		y_intercept += TILE_SIZE;

	// find the x-coordinate of the closest hor.intersection
	x_intercept = player->px + (y_intercept - player->py) / tan(ray->ray_angle);

	// calculate for increment xstep and ystep
	y_step = TILE_SIZE;
	if (ray->up)
		y_step *= -1;

	x_step = TILE_SIZE / tan(ray->ray_angle);
	if ((ray->left && (x_step > 0)) || (ray->right && (x_step < 0)))
		x_step *= -1;

	float next_horz_touch_x = x_intercept;
	float next_horz_touch_y = y_intercept;

	if (floor(next_horz_touch_y / TILE_SIZE) < data->rows && floor(next_horz_touch_y / TILE_SIZE) >= 0)
	{
		len = (int)ft_strlen(data->map->map[(int)floor(next_horz_touch_y / TILE_SIZE)]);
		while (next_horz_touch_x >= 0 && next_horz_touch_x <= (len) * TILE_SIZE && next_horz_touch_y >= 0 && next_horz_touch_y <= ((data->rows) * TILE_SIZE))
		{
			if (floor(next_horz_touch_y / TILE_SIZE) >= data->rows)
				break ;
			len = (int)ft_strlen(data->map->map[(int)floor(next_horz_touch_y / TILE_SIZE)]);
			if (has_wall_at(data, next_horz_touch_x, next_horz_touch_y - ray->up) == 1)
			{
				found_horz_wall_hit = 1;
				horz_wall_hit_x = next_horz_touch_x;
				horz_wall_hit_y = next_horz_touch_y;
				break ;
			}
			else
			{
				next_horz_touch_x += x_step;
				next_horz_touch_y += y_step;
			}
		}

	}
	// ---------------------- vertical ray-grid intersection ----------------

	int		found_vert_wall_hit = 0;
	float	vert_wall_hit_x;
	float	vert_wall_hit_y;

	// find the x-coordinate of the closest vertical intersection
	x_intercept = floor(player->px / TILE_SIZE) * TILE_SIZE;
	if (ray->right)
		x_intercept += TILE_SIZE;

	// find the y-coordinate of the closest vertical intersection
	y_intercept = player->py + (x_intercept - player->px) * tan(ray->ray_angle);

	// calculate for increment xstep and ystep
	x_step = TILE_SIZE;
	if (ray->left)
		x_step *= -1;

	y_step = TILE_SIZE * tan(ray->ray_angle);
	if ((ray->up && (y_step > 0)) || (ray->down && (y_step < 0)))
		y_step *= -1;

	float next_vert_touch_x = x_intercept;
	float next_vert_touch_y = y_intercept;

	if (floor(next_vert_touch_y / TILE_SIZE) < data->rows && floor(next_vert_touch_y / TILE_SIZE) >= 0)
	{
		len = (int)ft_strlen(data->map->map[(int)round(next_vert_touch_y / TILE_SIZE)]);
		while (next_vert_touch_x >= 0 && next_vert_touch_x <= (len * TILE_SIZE) && next_vert_touch_y >= 0 && next_vert_touch_y <= ((data->rows) * TILE_SIZE))
		{
			if (floor(next_vert_touch_y / TILE_SIZE) >= data->rows)
				break ;
			len = (int)ft_strlen(data->map->map[(int)round(next_vert_touch_y / TILE_SIZE)]);
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
	}

	// calculate both horizontal and vertical distances and choose the smalest value
	float	horz_hit_distance;
	float	vert_hit_distance;

	if (found_horz_wall_hit)
		horz_hit_distance = get_distance(player->px, player->py, horz_wall_hit_x, horz_wall_hit_y);
	else
		horz_hit_distance = MAX_VAL;

	if (found_vert_wall_hit)
		vert_hit_distance = get_distance(player->px, player->py, vert_wall_hit_x, vert_wall_hit_y);
	else
		vert_hit_distance = MAX_VAL;

	// only store the smallest of the distances
	if (horz_hit_distance < vert_hit_distance)
	{
		ray->wall_hit_x = horz_wall_hit_x;
		ray->wall_hit_y = horz_wall_hit_y;
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
