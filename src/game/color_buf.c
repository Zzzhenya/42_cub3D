/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:01:31 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/05 18:36:46 by ohladkov         ###   ########.fr       */
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
	t_txr		*tmp;

	if (ray->side < 0 || ray->side > 3)
	{
        perror("Error\nInvalid ray side index");
        return ;
    }
	tmp = data->elem->txr[ray->side];
	y = line->y_top;
	if (ray->vert_hit)
		texture_offset_x = (int)ray->wall_hit_y % TILE_SIZE;
	else
		texture_offset_x = (int)ray->wall_hit_x % TILE_SIZE;
	while (y < line->y_botm)
	{
		distance_from_top = y + (ray->wall_height / 2) - (H / 2);
		texture_offset_y = distance_from_top * ((float)tmp->height / ray->wall_height);

		// Ensure texture coordinates are within bounds
		if (texture_offset_y >= tmp->height)
			texture_offset_y = tmp->height - 1;
		if (texture_offset_y < 0)
			texture_offset_y = 0;
		if (texture_offset_x >= tmp->width)
			texture_offset_x = tmp->width - 1;
		if (texture_offset_x < 0)
			texture_offset_x = 0;

		// Get the pixel color from the texture buffer
        texture_pixel_color = tmp->addr[(tmp->width * texture_offset_y) + texture_offset_x];

		// Ensure color buffer index is within bounds
        if ((W * y) + line->x0 >= W * H || (W * y) + line->x0 < 0) {
            perror("Error\nColor buffer index out of bounds");
            return ;
        }
        data->color_buf[(W * y) + line->x0] = texture_pixel_color;
		y++;
	}
}

void	set_color_ceiling(t_line *line, t_data *data, t_elem *elem)
{
	int	y;
	int	y_max;

	y = 0;
	y_max = line->y_top;
	line->color = ft_rgb(elem->rgb_c[0], elem->rgb_c[1], elem->rgb_c[2]);
	while (y < y_max)
	{
		data->color_buf[(W * y) + line->x0] = line->color;
		y++;
	}
}

void	set_color_floor(t_line *line, t_data *data, t_elem *elem)
{
	int	y;
	int	y_max;

	y = line->y_botm;
	y_max = H;
	line->color = ft_rgb(elem->rgb_f[0], elem->rgb_f[1], elem->rgb_f[2]);
	while (y < y_max)
	{
		data->color_buf[(W * y) + line->x0] = line->color;
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
