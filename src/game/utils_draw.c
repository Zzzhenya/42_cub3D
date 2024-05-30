/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:01:31 by ohladkov          #+#    #+#             */
/*   Updated: 2024/05/30 19:56:37 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// void	draw_line(t_line *line, t_data *data)
// {
// 	int	y;
// 	int	y_max;

// 	if (line->y0 < line->y1)
// 	{
// 		y = line->y0;
// 		y_max = line->y1;
// 	}
// 	else
// 	{
// 		y = line->y1;
// 		y_max = line->y0;
// 	}
// 	if (y >= 0)
// 	{
// 		while (y < y_max)
// 		{
// 			ft_pixel_put(&data->img, line->x0, y, line->color);
// 			y++;
// 		}
// 	}
// }

void	draw_line(t_line *line, t_data *data)
{
	int	y;
	int	y_max;

	// printf("xo: %i, yo:  %i, y1: %i\n", line->x0, line->y0, line->y1);
	if (line->y0 < line->y1)
	{
		y = line->y0;
		y_max = line->y1;
	}
	else
	{
		y = line->y1;
		y_max = line->y0;
	}
	if (y < 0)
		y = 0;
	if (y >= 0)
	{
		while (y < y_max)
		{
			ft_pixel_put(&data->img, line->x0, y, line->color);
			y++;
		}
	}
}
