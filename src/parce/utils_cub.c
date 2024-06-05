/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:11:28 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/05 19:07:08 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	print_err(char *s)
{
	ft_putstr_fd("Error\n", 2);
	if (s)
		ft_putendl_fd(s, 2);
	return (1);
}

void	malloc_error(void)
{
	perror("malloc");
	exit(EXIT_FAILURE);
}

void	display_controls(void)
{
	printf("Controls in Cub3D:\n");
	printf("\tW: move forward\n");
	printf("\tS: move backward\n");
	printf("\tA: move left\n");
	printf("\tD: move right\n");
	printf("\tleft arrow: rotate left\n");
	printf("\tright arrow: rotate right\n");
}

int	has_wall_at(t_data *data, float x, float y)
{
	int	idx_x;
	int	idx_y;
	int	row_length;

	idx_y = (int)floor(y / TILE_SIZE);
	if (idx_y < 0 || idx_y >= data->rows)
		return (1);
	row_length = (int)ft_strlen(data->map->map[idx_y]);
	idx_x = (int)floor(x / TILE_SIZE);
	if (idx_x < 0 || idx_x >= row_length)
		return (1);
	if (data->map->map[idx_y][idx_x] == '1' \
	|| data->map->map[idx_y][idx_x] == ' ')
		return (1);
	return (0);
}
