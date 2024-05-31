/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color_buf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:01:31 by ohladkov          #+#    #+#             */
/*   Updated: 2024/05/31 22:16:37 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	set_color_wall(t_line *line, t_data *data)
{
	int	y;
	int	y_max;

	y = line->y_top;
	y_max = line->y_botm;
	while (y < y_max)
	{
		data->color_buf[(W * y) + line->x0] = line->color;
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