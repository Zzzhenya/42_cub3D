/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:11:08 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/05 22:07:47 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	txr_init(t_elem *elem);

void	game(t_data *data)
{
	render_3d_walls(data, data->player, data->ray);
	ft_put_pixel_buf(data, &data->img);
	mini_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->img.mlx_img, 0, 0);
}

int	load_textures(t_data *data, t_elem *elem)
{
	int	i;

	i = -1;
	if (txr_init(elem) != 0)
		return (1);
	elem->txr[NO]->img = mlx_xpm_file_to_image(data->mlx_ptr, elem->no, \
	&elem->txr[0]->width, &elem->txr[1]->height);
	elem->txr[WE]->img = mlx_xpm_file_to_image(data->mlx_ptr, elem->we, \
	&elem->txr[3]->width, &elem->txr[2]->height);
	elem->txr[SO]->img = mlx_xpm_file_to_image(data->mlx_ptr, elem->so, \
	&elem->txr[2]->width, &elem->txr[3]->height);
	elem->txr[EA]->img = mlx_xpm_file_to_image(data->mlx_ptr, elem->ea, \
	&elem->txr[1]->width, &elem->txr[0]->height);
	i = -1;
	while (++i < 4)
	{
		if (!elem->txr[i]->img)
			return (perror("Error\nFailed loading texture"), 1);
		elem->txr[i]->addr = (uint32_t *)mlx_get_data_addr(elem->txr[i]->img, \
		&elem->txr[i]->bpp, &elem->txr[i]->line_length, &elem->txr[i]->endian);
	}
	return (0);
}

static int	txr_init(t_elem *elem)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		elem->txr[i] = (t_txr *)ft_calloc(1, sizeof(t_txr));
		if (!elem->txr[i])
			return (perror("Error\nTexture malloc"), 1);
	}
	return (0);
}
