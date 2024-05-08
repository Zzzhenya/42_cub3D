/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:10:55 by ohladkov          #+#    #+#             */
/*   Updated: 2024/04/21 15:48:08 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_2.h"

void	window_init(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		malloc_error();
	data->name = "Cub3D";
	data->win_ptr = mlx_new_window(data->mlx_ptr, W, H, \
	data->name);
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
	game_init(data);
}

void	data_init(t_data *data)
{
	int	i;

	data->map->map = NULL;
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
	data->map->px = -1;
	data->map->py = -1;
	data->map->view = 0;
}

int	main(int ac, char **av)
{
	t_data		*data;
	t_map		map;
	t_elem		elem;
	t_ray		ray;
	t_player	player;

	if (ac != 2)
		return (write(2, "Error\n", 6));
	if (check_filename(av[1], ".cub") != 0)
		return (1);
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		malloc_error();
	data->elem = &elem;
	data->map = &map;
	data->ray = &ray;
	data->player = &player;
	data_init(data);
	if (read_file(av[1], data) != 0)
		return (clean_up_data(data), 1);
	if (validate_file_contents(av[1], data) != 0)
		return (clean_up_data(data), 1);
	window_init(data);
	display_controls();
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &keypress, data);
	mlx_hook(data->win_ptr, DestroyNotify, StructureNotifyMask, &cross, \
	data);
	game(data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
