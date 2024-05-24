/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:01:31 by ohladkov          #+#    #+#             */
/*   Updated: 2024/05/24 18:39:40 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_2.h"

void	draw_rectangle(int row, int col, t_data *data, int color);
void	draw_v_line(int row, int col, t_data *data, int color);
void	draw_g_line(int row, int col, t_data *data, int color);

void	my_print(t_data *data, t_ray *ray)
{
	printf("px:%f, py:%f, char:%c\n", data->player->px, data->player->py, data->map->view); //rm
	printf("pa:%f pdx:%f pdy:%f\n", data->player->pa, data->player->pdx, data->player->pdy);
	if (ray)
	{
		// printf("distance: %f, ray_angle: %i, cos: %f, sin: %f, count: %i, wall_hight: %i, x: %f, y: %f\n",\
		//  ray->distance, ray->ray_angle, ray->ray_cos, ray->ray_sin, ray->ray_count, ray->wall_height, ray->x, ray->y);
		printf("positon in map (wall): %i, ray->y: %i, ray->x: %i\n", ray->wall, (int)floor(ray->y), (int)floor(ray->x));
	}
}

void	mini_map(t_data *data)
{
	int	col;
	int row;
	int	map_y;
	// int	tile_x;
	// int	tile_y;

	// map_y = H - ((data->rows + 1) * CELLSIZE);
	map_y = 0;
	col = 0;
	row = 0;

	while (row < data->rows)
	{
		col = 0;
		while (data->map->map[row][col])
		{
			// tile_y = row * CELLSIZE;
			// tile_x = col * CELLSIZE;
			// draw_g_line(map_y + row + (row * CELLSIZE), \
			// col + (col * CELLSIZE), data, 0x001500);
			if (data->map->map[row][col] == '1')
			{
				draw_rectangle(map_y + row + (row * CELLSIZE), \
				col + (col * CELLSIZE), data, ft_rgb(135, 206, 250));
			}
			else
			{
				draw_rectangle(map_y + row + (row * CELLSIZE), \
				col + ((col) * CELLSIZE), data, 0xFFFFFF);
			}
			// draw_v_line(map_y + row + (row * CELLSIZE), \
			// col + ((col) * CELLSIZE), data, 0x001500);
			// draw_g_line(map_y + row + (row * CELLSIZE) + CELLSIZE, \
			// col + ((col) * CELLSIZE), data, 0x001500);
			col++;
		}
		// draw_v_line(map_y + row + (row * CELLSIZE), \
		// col + ((col) * CELLSIZE), data, 0x001500);
		row++;
	}
}

 
void	draw_player(t_data *data)
{
	float	map_y;
	float	map_x;
	int		y;
	int		x;

	// map_y = H - ((data->rows + 1.0) * CELLSIZE) + ((data->map->py) * CELLSIZE);
	map_y = data->player->py;
	map_x = data->player->px;
	// ft_pixel_put(&data->img, map_x, map_y, 0x00ff00);
	y = -(PLAYER_SIZE / 2);
	while (y < (PLAYER_SIZE / 2))
	{
		x = -(PLAYER_SIZE / 2);
		while (x < (PLAYER_SIZE / 2))
		{
			ft_pixel_put(&data->img, map_x + x, map_y + y, 0x15f102);
			x++;
		}
		y++;
	}
}

void	draw_player_dir(t_data *data, float target_x, float target_y)
{
	t_line		line;
	float		map_y;
	float		map_x;

	map_y = data->player->py;
	map_x = data->player->px;
	line.x0 = map_x;
	line.x1 = floor(target_x);
	line.y0 = map_y;
	line.y1 = floor(target_y);
	line.color = 0xff0000;
	draw_line_other(&line, data);
}

void	draw_line(t_line *line, t_data *data)
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
			ft_pixel_put(&data->img, line->x0, y, line->color);
			y++;
		}
	}
}

void	draw_g_line(int row, int col, t_data *data, int color)
{
	int	i;

	i = -1;
	while (++i < CELLSIZE)
	{
		ft_pixel_put(&data->img, col + i, row, color);
	}
}

void	draw_v_line(int row, int col, t_data *data, int color)
{
	int	i;

	i = 0;
	while (i < CELLSIZE)
	{
		ft_pixel_put(&data->img, col, row + i, color);
		i++;
	}
}

void draw_rectangle(int row, int col, t_data *data, int color)
{
	int i;

	i = 0;
	while (i < CELLSIZE)
	{
		draw_v_line(row, col + i, data, color);
		i++;
	}
}


// Function to draw a line using Bresenham's line algorithm
void draw_line_other(t_line *line, t_data *data) 
{
	int dx = abs(line->x1 - line->x0);
	int dy = abs(line->y1 - line->y0);
	int sx = line->x0 < line->x1 ? 1 : -1;
	int sy = line->y0 < line->y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;

	while (1) {
		ft_pixel_put(&data->img, line->x0, line->y0, line->color);
		if (line->x0 == line->x1 && line->y0 == line->y1)
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
			line->y0 += sy;
		}
	}
}
