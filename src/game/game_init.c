/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:11:08 by ohladkov          #+#    #+#             */
/*   Updated: 2024/05/31 22:32:28 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	game_init(t_data *data)
{
	data->player->pa_rad = degrees_to_radians(get_degree(data->map->view));
	data->player->px = data->map->px * TILE_SIZE + TILE_SIZE / 2;
	data->player->py = data->map->py * TILE_SIZE + TILE_SIZE / 2;
	data->player->rotation_speed = (2 * ((float)PI / 180.0));
	init_struct_ray(data->ray, data->player);
	data->color_buf = (u_int32_t *)malloc(sizeof(u_int32_t) * (u_int32_t)W * (u_int32_t)H);
	if (!data->color_buf)
	{
		print_error("malloc error");
		cross_exit(data);
	}
	init_texture_buf(data);
}

void	init_texture_buf(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	data->texture_buf = (u_int32_t *)malloc(sizeof(u_int32_t) * (u_int32_t)TEXTURE_W * (u_int32_t)TEXTURE_H);
	if (!data->texture_buf)
	{
		print_error("malloc error");
		cross_exit(data);
	}
	while (x < TEXTURE_H)
	{
		y = 0;
		while (y < TEXTURE_W)
		{
			if (x % 8 && y % 8)
				data->texture_buf[(TEXTURE_W * y) + x] = 0xFF0000FF;
			else
				data->texture_buf[(TEXTURE_W * y) + x] = 0xFF000000;
			y++;
		}
		x++;
	}
}

void	clear_color_buf(t_data *data, uint32_t color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < W)
	{
		y = 0;
		while (y < H)
		{
			data->color_buf[(W * y) + x] = color;
			y++;
		}
		x++;
	}
}

void	game(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	// mlx_clear_window(data->mlx_ptr, data->win_ptr);
	// clear_color_buf(data, 0xFFFFFFFF);
	render_3d_walls(data, data->player, data->ray);
	ft_put_pixel_buf(data, &data->img);
	mini_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->img.mlx_img, 0, 0);
}

