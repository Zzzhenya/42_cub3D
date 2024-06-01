/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:01:31 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/01 12:59:05 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	set_color_wall(t_line *line, t_data *data, t_ray *ray)
{
	uint32_t	texture_pixel_color;
	int			texture_offset_x;
	int			texture_offset_y;
	int			distance_from_top;
	int			y;

	y = line->y_top;
	if (ray->vert_hit)
		texture_offset_x = (int)ray->wall_hit_y % TILE_SIZE;
	else
		texture_offset_x = (int)ray->wall_hit_x % TILE_SIZE;
	while (y < line->y_botm)
	{
		distance_from_top = y + (ray->wall_height / 2) - (H / 2);
		texture_offset_y = distance_from_top * ((float)TEXTURE_H / ray->wall_height);
		texture_pixel_color = data->texture_buf[(TEXTURE_W * texture_offset_y) + texture_offset_x];
		data->color_buf[(W * y) + line->x0] = texture_pixel_color;
		y++;
	}
}

void	set_color_ceiling(t_line *line, t_data *data)
{
	int	y;
	int	y_max;

	y = 0;
	y_max = line->y_top;
	while (y < y_max)
	{
		data->color_buf[(W * y) + line->x0] = 0xFF124565;
		y++;
	}
}

void	set_color_floor(t_line *line, t_data *data)
{
	int	y;
	int	y_max;

	y = line->y_botm;
	y_max = H;
	while (y < y_max)
	{
		data->color_buf[(W * y) + line->x0] = 0xFF777777;
		y++;
	}
}

void	clear_color_buf(t_data *data, uint32_t color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < W)
	{
		y = 0;
		while (y < H)
		{
			data->color_buf[(W * y) + x] = color;
			y++;
		}
		x++;
	}
}
