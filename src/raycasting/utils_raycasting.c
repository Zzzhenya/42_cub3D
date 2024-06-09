/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:43:47 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/09 19:30:53 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

float	get_distance(float px, float py, float hit_x, float hit_y)
{
	float	x;
	float	y;

	x = px - hit_x;
	y = py - hit_y;
	return (sqrt((x * x) + (y * y)));
}

float	get_hit_dist(t_raycast *src, t_player *pl)
{
	if (src->found_wall_hit)
		return (get_distance(pl->px, pl->py, src->wall_hit_x, src->wall_hit_y));
	else
		return (MAX_VAL);
}

void	calc_horz_intersection(t_data *data, t_raycast *h, int side)
{
	char	**map;

	map = data->map->map;
	h->len = (int)ft_strlen(map[(int)floor(h->next_touch_y / TILE_SIZE)]);
	while (h->next_touch_x >= 0 && h->next_touch_x <= (h->len * TILE_SIZE) && \
	h->next_touch_y >= 0 && h->next_touch_y <= (data->rows * TILE_SIZE))
	{
		if (floor(h->next_touch_y / TILE_SIZE) >= data->rows)
			break ;
		h->len = (int)ft_strlen(map[(int)floor(h->next_touch_y / TILE_SIZE)]);
		if (has_wall_at(data, h->next_touch_x, h->next_touch_y - side) == 1)
		{
			h->found_wall_hit = 1;
			h->wall_hit_x = h->next_touch_x;
			h->wall_hit_y = h->next_touch_y;
			break ;
		}
		else
		{
			h->next_touch_x += h->x_step;
			h->next_touch_y += h->y_step;
		}
	}
}

void	calc_vert_intersection(t_data *data, t_raycast *v, int side)
{
	v->len = (int)ft_strlen(data->map->map[(int)round(v->next_touch_y / TILE_SIZE)]);
	while (v->next_touch_x >= 0 && v->next_touch_x <= (float)(v->len * TILE_SIZE) && \
	v->next_touch_y >= 0 && v->next_touch_y <= (float)(data->rows * TILE_SIZE))
	{
		if (floor(v->next_touch_y / TILE_SIZE) >= data->rows)
			break ;
		v->len = \
		(int)ft_strlen(data->map->map[(int)round(v->next_touch_y / TILE_SIZE)]);
		if (has_wall_at(data, v->next_touch_x - side, v->next_touch_y))
		{
			v->found_wall_hit = 1;
			v->wall_hit_x = v->next_touch_x;
			v->wall_hit_y = v->next_touch_y;
			break ;
		}
		else
		{
			v->next_touch_x += v->x_step;
			v->next_touch_y += v->y_step;
		}
	}
}
