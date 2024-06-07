/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:00:20 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/07 21:54:43 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	cast_all_rays(t_data *data, t_player *player, t_ray *ray, float scl)
{
	init_struct_ray(ray, player);
	ray->ray_count = 0;
	while (ray->ray_count < CASTED_RAYS)
	{
		cast_ray(data, player, ray);
		draw_player_dir(data, ray->wall_hit_x, ray->wall_hit_y, scl);
		ray->ray_count++;
		ray->angle += ((60 * (PI / 180)) / CASTED_RAYS);
		update_angle(ray);
	}
}

void	cast_ray(t_data *data, t_player *player, t_ray *ray)
{
	float	x_step;
	float	y_step;
	float	x_intercept;
	float	y_intercept;
	float	next_horz_touch_x;
	float	next_horz_touch_y;
	float	horz_wall_hit_x;
	float	horz_wall_hit_y;
	int		found_horz_wall_hit;
	int		len;

	// ---------------------- horisontal ray-grid intersection --------------

	// find the y-coordinate of the closest hor.intersection
	y_intercept = floor(player->py / TILE_SIZE) * TILE_SIZE;
	if (ray->down)
		y_intercept += TILE_SIZE;

	// find the x-coordinate of the closest hor.intersection
	x_intercept = player->px + (y_intercept - player->py) / tan(ray->angle);

	// calculate for increment xstep and ystep
	y_step = TILE_SIZE;
	if (ray->up)
		y_step *= -1;

	x_step = TILE_SIZE / tan(ray->angle);
	if ((ray->left && (x_step > 0)) || (ray->right && (x_step < 0)))
		x_step *= -1;

	next_horz_touch_x = x_intercept;
	next_horz_touch_y = y_intercept;

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
	float next_vert_touch_x;
	float next_vert_touch_y;

	// find the x-coordinate of the closest vertical intersection
	x_intercept = floor(player->px / TILE_SIZE) * TILE_SIZE;
	if (ray->right)
		x_intercept += TILE_SIZE;

	// find the y-coordinate of the closest vertical intersection
	y_intercept = player->py + (x_intercept - player->px) * tan(ray->angle);

	// calculate for increment xstep and ystep
	x_step = TILE_SIZE;
	if (ray->left)
		x_step *= -1;

	y_step = TILE_SIZE * tan(ray->angle);
	if ((ray->up && (y_step > 0)) || (ray->down && (y_step < 0)))
		y_step *= -1;

	next_vert_touch_x = x_intercept;
	next_vert_touch_y = y_intercept;

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


// void	cast_ray(t_data *data, t_player *player, t_ray *ray)
// {
// 	t_raycast	*horz;
// 	t_raycast	*vert;

// 	horz = horz_intersection(data, player, ray);
// 	vert = vert_intersection(data, player, ray);
// 	horz->hit_dist = get_hit_dist(horz, player);
// 	vert->hit_dist = get_hit_dist(vert, player);
// 	update_ray_coordinates(ray, horz, vert);
// 	free(horz);
// 	horz = NULL;
// 	free(vert);
// 	vert = NULL;
// }

// t_raycast	*horz_intersection(t_data *data, t_player *pl, t_ray *ray)
// {
// 	t_raycast	*h;
// 	int			tmp;

// 	h = ft_calloc(1, sizeof(t_raycast));
// 	h->y_intercept = floor(pl->py / TILE_SIZE) * TILE_SIZE;
// 	if (ray->down)
// 		h->y_intercept += TILE_SIZE;
// 	h->x_intercept = pl->px + (h->y_intercept - pl->py) / tan(ray->angle);
// 	h->y_step = TILE_SIZE;
// 	if (ray->up)
// 		h->y_step *= -1;
// 	h->x_step = TILE_SIZE / tan(ray->angle);
// 	if ((ray->left && (h->x_step > 0)) || (ray->right && (h->x_step < 0)))
// 		h->x_step *= -1;
// 	h->next_touch_x = h->x_intercept;
// 	h->next_touch_y = h->y_intercept;
// 	tmp = floor(h->next_touch_y / TILE_SIZE);
// 	if (tmp >= 0 && tmp < data->rows)
// 		calc_vert_intersection(data, h, ray->up);
// 	return (h);
// }

// t_raycast	*vert_intersection(t_data *data, t_player *pl, t_ray *ray)
// {
// 	t_raycast	*v;
// 	int			tmp;

// 	v = ft_calloc(1, sizeof(t_raycast));
// 	v->x_intercept = floor(pl->px / TILE_SIZE) * TILE_SIZE;
// 	if (ray->right)
// 		v->x_intercept += TILE_SIZE;
// 	v->y_intercept = pl->py + (v->x_intercept - pl->px) * tan(ray->angle);
// 	v->x_step = TILE_SIZE;
// 	if (ray->left)
// 		v->x_step *= -1;
// 	v->y_step = TILE_SIZE * tan(ray->angle);
// 	if ((ray->up && (v->y_step > 0)) || (ray->down && (v->y_step < 0)))
// 		v->y_step *= -1;
// 	v->next_touch_x = v->x_intercept;
// 	v->next_touch_y = v->y_intercept;
// 	tmp = floor(v->next_touch_y / TILE_SIZE);
// 	if (tmp >= 0 && tmp < data->rows)
// 		calc_vert_intersection(data, v, ray->left);
// 	return (v);
// }

// void	update_ray_coordinates(t_ray *ray, t_raycast *horz, t_raycast *vert)
// {
// 	if (horz->hit_dist < vert->hit_dist)
// 	{
// 		ray->wall_hit_x = horz->wall_hit_x;
// 		ray->wall_hit_y = horz->wall_hit_y;
// 		ray->distance = horz->hit_dist;
// 		ray->vert_hit = 0;
// 	}
// 	else
// 	{
// 		ray->wall_hit_x = vert->wall_hit_x;
// 		ray->wall_hit_y = vert->wall_hit_y;
// 		ray->distance = vert->hit_dist;
// 		ray->vert_hit = 1;
// 	}
// }
