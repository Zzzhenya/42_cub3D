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

typedef struct s_bres
{
	t_line		*line; 
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			e2;
}				t_bres;

void	set_bres_struct(t_bres *bres, t_line *line)
{
	bres->line = line;
	bres->dx = abs(bres->line->x1 - bres->line->x0);
	bres->dy = abs(bres->line->y_botm - bres->line->y_top);
	if (bres->line->x0 < bres->line->x1)
		bres->sx = 1;
	else
		bres->sx = -1;
	if (bres->line->y_top < bres->line->y_botm)
		bres->sy = 1;
	else
		bres->sy = -1;
	if (bres->dx > bres->dy)
		bres->err = bres->dx / 2;
	else
		bres->err = -bres->dy / 2;
	bres->e2 = 0;
}

// Function to draw a line using Bresenham's line algorithm
void	draw_line(t_line *line, t_data *data) 
{
	t_bres bres;

	set_bres_struct(&bres, line);
	while (1)
	{
		ft_pixel_put(&data->img, bres.line->x0, bres.line->y_top, bres.line->color);
		if (bres.line->x0 == bres.line->x1 && bres.line->y_top == bres.line->y_botm)
			break ;
		bres.e2 = bres.err;
		if (bres.e2 > -bres.dx)
		{
			bres.err -= bres.dy;
			bres.line->x0 += bres.sx;
		}
		if (bres.e2 < bres.dy)
		{
			bres.err += bres.dx;
			bres.line->y_top += bres.sy;
		}
	}
}
