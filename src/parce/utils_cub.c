/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:11:28 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/02 20:55:46 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	print_err(char *s)
{
	ft_putstr_fd("Error\n", 2);
	if (s)
	{
		ft_putendl_fd(s, 2);
	}
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
/**
 * 	// printf("\t2 x: %f, y: %f, indxx: %i, idx_y: %i\n", x, y, idx_x, idx_y);
	// printf("map->map[(int)floor(y)][(int)floor(x)]: %c | y = %d | x = %d\n", 
	// data->map->map[idx_y][idx_x], idx_y, idx_x);

	// if (!data->map->map[idx_y][idx_x] || data->map->map[idx_y][idx_x] == '1')
	//data->map->map[idx_y][idx_x] && 
*/

int	has_wall_at(t_data *data, float x, float y)
{
	int	idx_x;
	int	idx_y;

	if (x < 0 || x > W || y < 0 || y > H)
		return (1);
	idx_x = (int)floor(x / TILE_SIZE);
	idx_y = (int)floor(y / TILE_SIZE);
	if (!data->map->map[idx_y][idx_x])
		return (2);
	if (data->map->map[idx_y][idx_x] == '1')
		return (1);
	return (0);
}
