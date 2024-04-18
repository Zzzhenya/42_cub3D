/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:11:08 by ohladkov          #+#    #+#             */
/*   Updated: 2024/04/18 17:13:17 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void game_init(t_data *data)
{
	data->map->pa = get_degree(data->map->view);
	data->map->pdy = -sin(degrees_to_radians((data->map->pa)));
	data->map->pdx = cos(degrees_to_radians((data->map->pa)));
	data->ray->increment_angle = 2 * HFOV / W;
}

void	game(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	my_print(data);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	while (x < W)
	{
		y = 0;
		while (y < H)
		{
			draw_game(x, y, data);
			y++;
		}
		x++;
	}
	mini_map(data);
	draw_player(data);
	// draw_rays_2d(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->img.mlx_img, 0, 0);
}

void	draw_game(int x, int y, t_data *data)
{
    ft_pixel_put(&data->img, x, y, ft_rgb(235, 206, 250));
}

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

