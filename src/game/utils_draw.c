/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:01:31 by ohladkov          #+#    #+#             */
/*   Updated: 2024/05/31 22:14:02 by ohladkov         ###   ########.fr       */
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

int	ft_rgba(int r, int g, int b, int a)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

// Copy the color buffer to the image data
void	ft_put_pixel_buf(t_data *data, t_image *img)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < H)
	{
		x = 0;
		while (x < W)
		{
			int pixel_index = y * img->line_length + x * (img->bpp / 8);
			*((uint32_t *)(img->addr + pixel_index)) = data->color_buf[y * W + x];
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
