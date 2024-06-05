/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:01:31 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/05 19:03:10 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	ft_pixel_put(t_image *img, int x, int y, int color)
{
	int	pixel;

	pixel = (img->line_length * y) + (x * (img->bpp / 8));
	*((unsigned int *)(pixel + img->addr)) = color;
}

int	ft_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

// Copy the color buffer to the image data
void	ft_put_pixel_buf(t_data *data, t_image *img)
{
	int	x;
	int	y;
	int	pixel_idx;

	x = 0;
	y = 0;
	while (y < H)
	{
		x = 0;
		while (x < W)
		{
			pixel_idx = y * img->line_length + x * (img->bpp / 8);
			*((uint32_t *)(img->addr + pixel_idx)) = data->color_buf[y * W + x];
			x++;
		}
		y++;
	}
}

void	draw_vert_line(t_line *line, t_data *data)
{
	int	y;
	int	y_max;

	if (line->y_top < line->y_botm)
	{
		y = line->y_top;
		y_max = line->y_botm;
	}
	else
	{
		y = line->y_botm;
		y_max = line->y_top;
	}
	if (y >= 0)
	{
		while (y < y_max)
		{
			ft_pixel_put(&data->img, line->x0, y, line->color);
			y++;
		}
	}
}

// Function to draw a line using Bresenham's line algorithm
void	draw_line(t_line *line, t_data *data) 
{
	int dx = abs(line->x1 - line->x0);
	int dy = abs(line->y_botm - line->y_top);
	int sx = line->x0 < line->x1 ? 1 : -1;
	int sy = line->y_top < line->y_botm ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;

	while (1)
	{
		ft_pixel_put(&data->img, line->x0, line->y_top, line->color);
		if (line->x0 == line->x1 && line->y_top == line->y_botm)
			break ;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			line->x0 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			line->y_top += sy;
		}
	}
}
