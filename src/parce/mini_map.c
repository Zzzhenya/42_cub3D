/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:01:31 by ohladkov          #+#    #+#             */
/*   Updated: 2024/04/18 15:23:55 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	draw_rectangle(int row, int col, t_data *data, int color);
void	draw_v_line(int row, int col, t_data *data, int color);
void	draw_g_line(int row, int col, t_data *data, int color);

void	my_print(t_data *data)
{
	printf("px:%f, py:%f, char:%c\n", data->map->px, data->map->py, data->map->view); //rm
	printf("pa:%f pdx:%f pdy:%f\n", data->map->pa, data->map->pdx, data->map->pdy);
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
			col + ((col) * TILE_SIZE_MINI), data, 0x001500);
			if (data->map->map[row][col] == '1')
			{
				draw_rectangle(map_y + row + (row * TILE_SIZE_MINI), \
				col + ((col) * TILE_SIZE_MINI), data, ft_rgb(135, 206, 250));
			}
			else
			{
				draw_rectangle(map_y + row + (row * TILE_SIZE_MINI), \
				col + ((col) * TILE_SIZE_MINI), data, 0xFFFFFF);
			}
			draw_v_line(map_y + row + (row * TILE_SIZE_MINI), \
			col + ((col) * TILE_SIZE_MINI), data, 0x001500);
			draw_g_line(map_y + row + (row * TILE_SIZE_MINI) + TILE_SIZE_MINI, \
			col + ((col) * TILE_SIZE_MINI), data, 0x001500);
			col++;
		}
		draw_v_line(map_y + row + (row * TILE_SIZE_MINI), \
		col + ((col) * TILE_SIZE_MINI), data, 0x001500);
		row++;
	}
}


void	draw_line(t_data *data, t_line *line, int color)
{
	int	y;
	int	y_max;

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
	if (y >= 0)
	{
		while (y < y_max)
		{
			ft_pixel_put(&data->img, line->x0, y, color);
			y++;
		}
	}
}

void	draw_player(t_data *data)
{
	t_line	line;
	int	map_y;
	int	map_x;
	int	y;
	int	x;

	map_y = H - ((data->rows + 1.0) * TILE_SIZE_MINI) + ((data->map->py) * TILE_SIZE_MINI);
	map_x = ((data->map->px) * TILE_SIZE_MINI);
	printf("map_y: %d, map_x: %d\n", map_y, map_x);
	y = -(PLAYER_SIZE / 2) + 1;
	while (y < (PLAYER_SIZE / 2))
	{
		x = -(PLAYER_SIZE / 2) + 1;
		while (x < (PLAYER_SIZE / 2))
		{
			ft_pixel_put(&data->img, map_x + x, map_y + y, 0x15f102);
			x++;
		}
		y++;
	}
	line.x0 = map_x;
	line.x1 = map_x + (data->map->pdx * 5);
	line.y0 = map_y;
	line.y1 = map_y + (data->map->pdy * 5);
	line.color = 0x000000;
	draw_line_other(&line, data);
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
	}
}


// Function to draw a line using Bresenham's line algorithm
void draw_line_other(t_line *line, t_data* data) 
{
	//int x0, int y0, int x1, int y1, int color,
    int dx = abs(line->x1 - line->x0);
    int dy = abs(line->y1 - line->y0);
    int sx = line->x0 < line->x1 ? 1 : -1;
    int sy = line->y0 < line->y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (1) {
        // Draw pixel at (x0, y0)
		ft_pixel_put(&data->img, line->x0, line->y0, line->color);
		if (line->x0 == line->x1 && line->y0 == line->y1)
            break;
        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            line->x0 += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            line->y0 += sy;
        }
    }
}
