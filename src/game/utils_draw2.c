/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_draw2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:01:31 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/07 15:29:15 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
	Function to initiate the bresenham line algorithm struct
*/
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

/* 
	Function to draw a line using Bresenham's line algorithm
*/
void	draw_line(t_line *line, t_data *data)
{
	t_bres	bres;

	set_bres_struct(&bres, line);
	while (1)
	{
		ft_pixel_put(&data->img, bres.line->x0, bres.line->y_top, \
		bres.line->color);
		if (bres.line->x0 == bres.line->x1 && \
			bres.line->y_top == bres.line->y_botm)
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
