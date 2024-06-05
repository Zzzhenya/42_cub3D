/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:01:31 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/05 19:03:37 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	draw_rectangle(int row, int col, t_data *data, float scl);
static void	draw_player(t_data *data, int map_y, int map_x, float scale_map);
static void	draw_mini_map(t_data *data, int map_y, int map_x, float scale_map);

void	mini_map(t_data *data)
{
	int		offset_x;
	int		offset_y;
	float	scale_map;

	scale_map = 0.4;
	if (TILE_SIZE > 32)
		scale_map = 0.15;
	if (data->cols > 40 || data->rows > 30)
	{
		scale_map = 0.1;
		if (data->cols > 100 || data->rows > 100)
			return ;
	}
	offset_x = TILE_SIZE * scale_map;
	offset_y = H - (data->rows * TILE_SIZE * scale_map) - TILE_SIZE;
	draw_mini_map(data, offset_y, offset_x, scale_map);
	draw_player(data, offset_y, offset_x, scale_map);
	cast_all_rays(data, data->player, data->ray, scale_map);
}

static void	draw_mini_map(t_data *data, int map_y, int map_x, float scale_map)
{
	int	col;
	int	row;
	int	tile_x;
	int	tile_y;

	row = 0;
	while (row < data->rows)
	{
		col = 0;
		while (data->map->map[row][col])
		{
			tile_y = row * TILE_SIZE * scale_map;
			tile_x = col * TILE_SIZE * scale_map;
			if (data->map->map[row][col] == '1')
				draw_rectangle(map_y + tile_y, map_x + tile_x, data, scale_map);
			col++;
		}
		row++;
	}
}

static void	draw_player(t_data *data, int map_y, int map_x, float scale_map)
{
	int	y;
	int	x;

	map_y += data->player->py * scale_map;
	map_x += data->player->px * scale_map;
	y = -(PLAYER_SIZE * scale_map / 2);
	while (y < (PLAYER_SIZE * scale_map / 2))
	{
		x = -(PLAYER_SIZE * scale_map / 2);
		while (x < (PLAYER_SIZE * scale_map / 2))
		{
			ft_pixel_put(&data->img, map_x + x, map_y + y, 0x15f102);
			x++;
		}
		y++;
	}
}

void	draw_player_dir(t_data *data, float trgt_x, float trgt_y, float scl)
{
	t_line	line;
	float	map_y;
	float	map_x;
	int		offset_x;
	int		offset_y;

	offset_x = TILE_SIZE * scl;
	offset_y = H - (data->rows * TILE_SIZE * scl) - TILE_SIZE;
	map_y = data->player->py * scl;
	map_x = data->player->px * scl;
	line.x0 = offset_x + map_x;
	line.x1 = offset_x + floor(trgt_x) * scl;
	line.y_top = offset_y + map_y;
	line.y_botm = offset_y + floor(trgt_y) * scl;
	line.color = 0x0DFF0000;
	draw_line(&line, data);
}

static void	draw_rectangle(int row, int col, t_data *data, float scl)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE * scl)
	{
		j = 0;
		while (j < TILE_SIZE * scl)
		{
			ft_pixel_put(&data->img, col + i, row + j, 0xeff8fd);
			j++;
		}
		i++;
	}
}
