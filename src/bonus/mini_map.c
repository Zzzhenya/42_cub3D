/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:01:31 by ohladkov          #+#    #+#             */
/*   Updated: 2024/05/31 21:31:55 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	draw_rectangle(int row, int col, t_data *data, int color);
void	draw_v_line(int row, int col, t_data *data, int color);
void	draw_g_line(int row, int col, t_data *data, int color);

void	mini_map(t_data *data)
{
	int	scale_x;
	int	scale_y;
	scale_x = TILE_SIZE * MINIMAP_SCALE;
	scale_y = H - (data->rows * TILE_SIZE * MINIMAP_SCALE) - TILE_SIZE;
	draw_mini_map(data, scale_y, scale_x);
	draw_player(data, scale_y, scale_x);
	cast_all_rays(data, data->player, data->ray);
}

void	draw_mini_map(t_data *data, int map_y, int map_x)
{
	int	col;
	int row;
	int	tile_x;
	int	tile_y;

	row = 0;
	while (row < data->rows)
	{
		col = 0;
		while (data->map->map[row][col])
		{
			tile_y = row * TILE_SIZE * MINIMAP_SCALE;
			tile_x = col * TILE_SIZE * MINIMAP_SCALE;
			if (data->map->map[row][col] == '1')
			{
				draw_rectangle(map_y + tile_y, \
				map_x + tile_x, data, ft_rgb(135, 206, 250));
			}
			else if (data->map->map[row][col] != ' ')
			{
				draw_rectangle(map_y + tile_y, \
				map_x + tile_x, data, 0xFFFFFF);
			}
			col++;
		}
		row++;
	}
}

void	draw_player(t_data *data, int map_y, int map_x)
{
	int		y;
	int		x;

	map_y += data->player->py * MINIMAP_SCALE;
	map_x += data->player->px * MINIMAP_SCALE;
	y = -(PLAYER_SIZE * MINIMAP_SCALE / 2);
	while (y < (PLAYER_SIZE * MINIMAP_SCALE / 2))
	{
		x = -(PLAYER_SIZE * MINIMAP_SCALE / 2);
		while (x < (PLAYER_SIZE * MINIMAP_SCALE / 2))
		{
			ft_pixel_put(&data->img, map_x + x, map_y + y, 0x15f102);
			x++;
		}
		y++;
	}
}

void	draw_player_dir(t_data *data, float target_x, float target_y)
{
	t_line	line;
	float	map_y;
	float	map_x;
	int		scale_x;
	int		scale_y;

	scale_x = TILE_SIZE * MINIMAP_SCALE;
	scale_y = H - (data->rows * TILE_SIZE * MINIMAP_SCALE) - TILE_SIZE;
	map_y = data->player->py * MINIMAP_SCALE;
	map_x = data->player->px * MINIMAP_SCALE;
	line.x0 = scale_x + map_x;
	line.x1 = scale_x + floor(target_x) * MINIMAP_SCALE;
	line.y_top = scale_y + map_y;
	line.y_botm = scale_y + floor(target_y) * MINIMAP_SCALE;
	line.color = 0xff0000;
	draw_line_other(&line, data);
}

void	draw_g_line(int row, int col, t_data *data, int color)
{
	int	i;

	i = -1;
	while (++i < TILE_SIZE)
	{
		ft_pixel_put(&data->img, col + i, row, color);
	}
}

void	draw_v_line(int row, int col, t_data *data, int color)
{
	int	i;

	i = 0;
	while (i < TILE_SIZE)
	{
		ft_pixel_put(&data->img, col, row + i, color);
		i++;
	}
}

void draw_rectangle(int row, int col, t_data *data, int color)
{
	int i;

	i = 0;
	while (i < TILE_SIZE)
	{
		draw_v_line(row, col + i, data, color);
		i++;
	}
}

// Function to draw a line using Bresenham's line algorithm
void	draw_line_other(t_line *line, t_data *data) 
{
	int dx = abs(line->x1 - line->x0);
	int dy = abs(line->y_botm - line->y_top);
	int sx = line->x0 < line->x1 ? 1 : -1;
	int sy = line->y_top < line->y_botm ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;

	while (1) {
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
