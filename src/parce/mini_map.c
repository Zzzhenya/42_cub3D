/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:01:31 by ohladkov          #+#    #+#             */
/*   Updated: 2024/04/09 20:47:13 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// void 	draw_mini_map(t_data *data, int x, int y)
// {
// 	int i = 0;
// 	while (i < data->)
// 	{
// 		if (data->map->map[y][i] == '1')	
// 			ft_pixel_put(&data->img, x, y + i, 255);
// 		else
// 			ft_pixel_put(&data->img, x, y, 0);
// 	}
// 	i++;
// }

void draw_square(int y, int x, t_data *data, int color)
{
	int i = 0;
	int j = 0;
	while (i < 64)
	{
		j = 0;
		while (j < 64)
		{
			ft_pixel_put(&data->img, (i) + (y), j + (x), color);
			j++;
		}
		i++;
	}
}


void	mini_map(t_data *data)
{
	int	y = 0;
	int x = 0;
	
	while (data->map->map[y][x])
	{
		x = 0;
		while (data->map->map[y][x])
		{
			if (data->map->map[y][x] == '1')
				draw_square(y * 64, x * 64, data, 100);
			else
				draw_square(y * 64, x * 64, data, 0);
			x++;
		}
		y++;
	}
/* 	while (y < data->rows)
	{
		x = 0;
		while (x < ft_strlen(data->map->map[y]))
		{
			if (data->map->map[y][x] == '1')
				draw_mini_map(data, )
			draw_mini_map(data, x, y);
			x++;
		}
		y++;
		
	} */
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->img.mlx_img, 0, 0);
}

/*

*/

/**
ft_pixel_put(&data->img, x, y, \
	ft_rgb(data->elem->rgb_c[0], data->elem->rgb_c[1], data->elem->rgb_c[2]));
 */