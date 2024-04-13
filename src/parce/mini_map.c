/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:01:31 by ohladkov          #+#    #+#             */
/*   Updated: 2024/04/13 14:15:08 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	draw_rectangle(int row, int col, t_data *data, int color);
void	draw_v_line(int row, int col, t_data *data, int color);
void	draw_g_line(int row, int col, t_data *data, int color);

void	draw_player(t_data *data)
{
	int	map_y;
	int	y;
	int	x;

	map_y = H - ((data->rows + 1) * TILE_SIZE_MINI);
	y = 0;
	while (y <= (TILE_SIZE_MINI / 4))
	{
		x = 0;
		while (x <= (TILE_SIZE_MINI / 4))
		{
			ft_pixel_put(&data->img, (data->map->px + 0.5 * TILE_SIZE_MINI) + x, \
			map_y + (data->map->py + 0.5 * TILE_SIZE_MINI) + y, 0x15f102);
			x++;
		}
		y++;
	}
}

void	draw_g_line(int row, int col, t_data *data, int color)
{
	int	i;

	i = -1;
	while (++i <= TILE_SIZE_MINI)
	{
		ft_pixel_put(&data->img, col + i, row, color);
	}
}

void	draw_v_line(int row, int col, t_data *data, int color)
{
	int	i;

	i = -1;
	while (++i <= TILE_SIZE_MINI)
	{
		ft_pixel_put(&data->img, col, row + i, color);
	}
}

void draw_rectangle(int row, int col, t_data *data, int color)
{
	int i;

	i = -1;
	while (++i <= TILE_SIZE_MINI)
	{
		draw_v_line(row, col + i, data, color);
		// draw_v_line(row + (row * TILE_SIZE_MINI), col + ((col + 1) * TILE_SIZE_MINI) + i, data, color);
	}
}

void	mini_map(t_data *data)
{
	int	col;
	int row;
	int	map_y;

	map_y = H - ((data->rows + 1) * TILE_SIZE_MINI);
	col = 0;
	row = 0;
	while (row < data->rows)
	{
		col = 0;
		while (data->map->map[row][col])
		{
			draw_g_line(map_y + row + (row * TILE_SIZE_MINI), \
			col + ((col + 1) * TILE_SIZE_MINI), data, 0x001500);
			if (data->map->map[row][col] == '1')
			{
				draw_rectangle(map_y + row + (row * TILE_SIZE_MINI), \
				col + ((col + 1) * TILE_SIZE_MINI), data, ft_rgb(135, 206, 250));
			}
			else
			{
				draw_rectangle(map_y + row + (row * TILE_SIZE_MINI), \
				col + ((col + 1) * TILE_SIZE_MINI), data, 0xFFFFFF);
			}
			draw_v_line(map_y + row + (row * TILE_SIZE_MINI), \
			col + ((col + 1) * TILE_SIZE_MINI), data, 0x001500);
			draw_g_line(map_y + row + (row * TILE_SIZE_MINI) + TILE_SIZE_MINI, \
			col + ((col + 1) * TILE_SIZE_MINI), data, 0x001500);
			col++;
		}
		draw_v_line(map_y + row + (row * TILE_SIZE_MINI), \
		col + ((col + 1) * TILE_SIZE_MINI), data, 0x001500);
		row++;
	}
}
