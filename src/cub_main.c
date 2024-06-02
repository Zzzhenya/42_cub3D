/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:10:55 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/02 19:01:24 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	main(int ac, char **av)
{
	t_data		*data;

	if (ac != 2)
		return (print_error("Run program with any map .cub"));
	if (check_filename(av[1], ".cub") != 0)
		return (1);
	data = initialize_data();
	if (read_file(av[1], data) != 0)
		return (clean_up_data(data), 1);
	if (validate_file_content(av[1], data) != 0)
		return (clean_up_data(data), 1);
	window_init(data);
	game_init(data);
	display_controls();
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &keypress, data);
	mlx_hook(data->win_ptr, DestroyNotify, StructureNotifyMask, &cross_exit, \
	data);
	// mlx_hook(data->win_ptr, 6, 1L << 6, mouse_move, data);
	game(data);
	mlx_loop(data->mlx_ptr);
	return (0);
}


t_data *initialize_data(void)
{
	t_data *data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data) {
		malloc_error();
	}
	data->elem = (t_elem *)ft_calloc(1, sizeof(t_elem));
	data->map = (t_map *)ft_calloc(1, sizeof(t_map));
	data->ray = (t_ray *)ft_calloc(1, sizeof(t_ray));
	data->player = (t_player *)ft_calloc(1, sizeof(t_player));
	if (!data->elem || !data->map || !data->ray || !data->player)
		malloc_error();
	data_init(data);
	return data;
}


void	window_init(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		malloc_error();
	data->name = "Cub3D";
	data->win_ptr = mlx_new_window(data->mlx_ptr, W, H, data->name);
	if (data->win_ptr == NULL)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		malloc_error();
	}
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, W, H);
	if (data->img.mlx_img == NULL)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		malloc_error();
	}
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, \
		&data->img.bpp, &data->img.line_length, &data->img.endian);
}

void	data_init(t_data *data)
{
	int	i;

	data->map->map = NULL;
	data->map->px = -1;
	data->map->py = -1;
	data->map->view = 0;
	data->color_buf = NULL;
	data->texture_buf = NULL;
	data->elem->ea = NULL;
	data->elem->we = NULL;
	data->elem->so = NULL;
	data->elem->no = NULL;
	i = 0;
	while (i < 3)
	{
		data->elem->rgb_c[i] = -1;
		data->elem->rgb_f[i] = -1;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		data->elem->txr[i] = (t_txr *)ft_calloc(1, sizeof(t_txr));
		i++;
	}
}