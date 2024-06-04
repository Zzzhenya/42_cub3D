/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:11:08 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/02 20:54:30 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// uint32_t get_texture_pixel(t_txr *texture, int x, int y)
// {
// 	int pixel_pos;

// 	// Calculate the pixel position in the texture data array
// 	 // dividing by 4 because each pixel is 4 bytes (uint32_t)
// 	// pixel_pos = (y * texture->line_length / 4) + x;
// 	printf("texture->line_length: %i\n", texture->line_length);
// 	pixel_pos = y * texture->line_length + x * (texture->bpp / 8);
// 	printf("\t\t%u\n", texture->addr[pixel_pos]);
// 	return ((uint32_t)texture->addr[pixel_pos]);
// }


void	game(t_data *data)
{
	// int	x;
	// int	y;

	// x = 0;
	// y = 0;
	// mlx_clear_window(data->mlx_ptr, data->win_ptr);
	// clear_color_buf(data, 0xFFFFFFFF);
	render_3d_walls(data, data->player, data->ray);
	ft_put_pixel_buf(data, &data->img);
	mini_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->img.mlx_img, 0, 0);
}

int	set_textures(t_data *data, t_elem *elem)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->elem->txr[i] = (t_txr *)ft_calloc(1, sizeof(t_txr));
		if (!data->elem->txr[i])
			return (perror("Error\nTexture malloc"), 1);
		i++;
	}
	elem->txr[0]->img = mlx_xpm_file_to_image(data->mlx_ptr, elem->ea, &elem->txr[0]->width, &elem->txr[0]->height);
	elem->txr[1]->img = mlx_xpm_file_to_image(data->mlx_ptr, elem->no, &elem->txr[1]->width, &elem->txr[1]->height);
	elem->txr[2]->img = mlx_xpm_file_to_image(data->mlx_ptr, elem->we, &elem->txr[2]->width, &elem->txr[2]->height);
	elem->txr[3]->img = mlx_xpm_file_to_image(data->mlx_ptr, elem->so, &elem->txr[3]->width, &elem->txr[3]->height);
	i = 0;
	while (i < 4)
	{
		if (!elem->txr[i]->img)
			return (perror("Error\nFailed loading texture"), 1);
		elem->txr[i]->addr = (uint32_t *)mlx_get_data_addr(elem->txr[i]->img, \
		&elem->txr[i]->bpp, &elem->txr[i]->line_length, &elem->txr[i]->endian);
		// printf("texture %i -> bbp: %i, line_length: %i, endian: %i\n", i, elem->txr[i]->bpp, elem->txr[i]->line_length, elem->txr[i]->endian);
		i++;
	}
	return (0);
}

// void	init_texture_buf(t_data *data)
// {
// 	int	x;
// 	int	y;

// 	x = 0;
// 	data->texture_buf = (u_int32_t *)malloc(sizeof(u_int32_t) * (u_int32_t)TEXTURE_W * (u_int32_t)TEXTURE_H);
// 	if (!data->texture_buf)
// 	{
// 		print_err("malloc error");
// 		cross_exit(data);
// 	}
// 	while (x < TEXTURE_H)
// 	{
// 		y = 0;
// 		while (y < TEXTURE_W)
// 		{
// 			// if (x % 8 && y % 8)
// 			// 	data->texture_buf[(TEXTURE_W * y) + x] = 0xFF0000FF;
// 			// else
// 			// 	data->texture_buf[(TEXTURE_W * y) + x] = 0xFF000000;
// 			data->texture_buf[(TEXTURE_W * y) + x] = get_texture_pixel(data->elem->txr[0], x, y);
// 			y++;
// 		}
// 		x++;
// 	}
// }
