/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:00:20 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/07 15:25:25 by ohladkov         ###   ########.fr       */
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
	t_raycast	*horz;
	t_raycast	*vert;

	horz = horz_intersection(data, player, ray);
	vert = vert_intersection(data, player, ray);
	horz->hit_dist = get_hit_dist(horz, player);
	vert->hit_dist = get_hit_dist(vert, player);
	update_ray_coordinates(ray, horz, vert);
	free(horz);
	horz = NULL;
	free(vert);
	vert = NULL;
}

t_raycast	*horz_intersection(t_data *data, t_player *pl, t_ray *ray)
{
	t_raycast	*h;
	int			tmp;

	h = ft_calloc(1, sizeof(t_raycast));
	h->y_intercept = floor(pl->py / TILE_SIZE) * TILE_SIZE;
	if (ray->down)
		h->y_intercept += TILE_SIZE;
	h->x_intercept = pl->px + (h->y_intercept - pl->py) / tan(ray->angle);
	h->y_step = TILE_SIZE;
	if (ray->up)
		h->y_step *= -1;
	h->x_step = TILE_SIZE / tan(ray->angle);
	if ((ray->left && (h->x_step > 0)) || (ray->right && (h->x_step < 0)))
		h->x_step *= -1;
	h->next_touch_x = h->x_intercept;
	h->next_touch_y = h->y_intercept;
	tmp = floor(h->next_touch_y / TILE_SIZE);
	if (tmp >= 0 && tmp < data->rows)
		calc_vert_intersection(data, h, ray->up);
	return (h);
}

t_raycast	*vert_intersection(t_data *data, t_player *pl, t_ray *ray)
{
	t_raycast	*v;
	int			tmp;

	v = ft_calloc(1, sizeof(t_raycast));
	v->x_intercept = floor(pl->px / TILE_SIZE) * TILE_SIZE;
	if (ray->right)
		v->x_intercept += TILE_SIZE;
	v->y_intercept = pl->py + (v->x_intercept - pl->px) * tan(ray->angle);
	v->x_step = TILE_SIZE;
	if (ray->left)
		v->x_step *= -1;
	v->y_step = TILE_SIZE * tan(ray->angle);
	if ((ray->up && (v->y_step > 0)) || (ray->down && (v->y_step < 0)))
		v->y_step *= -1;
	v->next_touch_x = v->x_intercept;
	v->next_touch_y = v->y_intercept;
	tmp = floor(v->next_touch_y / TILE_SIZE);
	if (tmp >= 0 && tmp < data->rows)
		calc_vert_intersection(data, v, ray->left);
	return (v);
}

void	update_ray_coordinates(t_ray *ray, t_raycast *horz, t_raycast *vert)
{
	if (horz->hit_dist < vert->hit_dist)
	{
		ray->wall_hit_x = horz->wall_hit_x;
		ray->wall_hit_y = horz->wall_hit_y;
		ray->distance = horz->hit_dist;
		ray->vert_hit = 0;
	}
	else
	{
		ray->wall_hit_x = vert->wall_hit_x;
		ray->wall_hit_y = vert->wall_hit_y;
		ray->distance = vert->hit_dist;
		ray->vert_hit = 1;
	}
}
