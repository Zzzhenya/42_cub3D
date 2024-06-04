/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:10:55 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/02 21:14:27 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (print_err("Run program with any map .cub"));
	if (check_filename(av[1], ".cub") != 0)
		return (1);
	data = initialize_data();
	if (!data)
		malloc_error();
	if (read_file(av[1], data) != 0)
		return (clean_up_data(data), 1);
	if (validate_file_content(av[1], data) != 0)
		return (clean_up_data(data), 1);
	// window_init(data);
	// if (game_init(data) != 0)
	// 	return (cross_exit(data), 1);
	// display_controls();
	// mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &keypress, data);
	// mlx_hook(data->win_ptr, DestroyNotify, StructureNotifyMask, &cross_exit, \
	// data);
	// // mlx_hook(data->win_ptr, 6, 1L << 6, mouse_move, data);
	// game(data);
	// mlx_loop(data->mlx_ptr);
	return (0);
}

t_data	*initialize_data(void)
{
	t_data	*data;

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		malloc_error();
	data->elem = (t_elem *)ft_calloc(1, sizeof(t_elem));
	data->map = (t_map *)ft_calloc(1, sizeof(t_map));
	data->ray = (t_ray *)ft_calloc(1, sizeof(t_ray));
	data->player = (t_player *)ft_calloc(1, sizeof(t_player));
	if (!data->elem || !data->map || !data->ray || !data->player)
		malloc_error();
	data_init(data);
	return (data);
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

	data->map->px = -1;
	data->map->py = -1;
	data->map->view = 0;
	i = 0;
	while (i < 3)
	{
		data->elem->rgb_c[i] = -1;
		data->elem->rgb_f[i] = -1;
		i++;
	}
}

int	game_init(t_data *data)
{
	if (set_textures(data, data->elem) != 0)
		return (1);
	data->player->pa_rad = degrees_to_radians(get_degree(data->map->view));
	data->player->px = data->map->px * TILE_SIZE + TILE_SIZE / 2;
	data->player->py = data->map->py * TILE_SIZE + TILE_SIZE / 2;
	data->player->rotation_speed = (2 * ((float)PI / 180.0));
	init_struct_ray(data->ray, data->player);
	data->color_buf = (u_int32_t *)malloc(sizeof(u_int32_t) * \
	(u_int32_t)W * (u_int32_t)H);
	if (!data->color_buf)
		return (perror("Error\nColor_buf malloc"), 1);
	return (0);
}
