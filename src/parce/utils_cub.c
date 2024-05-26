/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:11:28 by ohladkov          #+#    #+#             */
/*   Updated: 2024/05/26 16:48:38 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
	printf("\tA: rotate left\n");
	printf("\tD: rotate right\n");
	printf("\tleft arrow: rotate left\n");
	printf("\tright arrow: rotate right\n");
}

int	has_wall_at(t_data *data, float x, float y)
{
	int	idx_x;
	int	idx_y;
// x > W  || y > H
	if (x < 0 || x > (15 * CELLSIZE) || y < 0 || y > (CELLSIZE * data->rows))
	{
		return (print_error("has_wall_at"), 1);
	}
	idx_x = (int)floor(x / CELLSIZE);
	idx_y = (int)floor(y / CELLSIZE);
	printf("map->map[(int)floor(y)][(int)floor(x)]: %c | y = %d | x = %d\n", 
	data->map->map[idx_y][idx_x], idx_y, idx_x);
	if (data->map->map[idx_y][idx_x] && data->map->map[idx_y][idx_x] == '1')
		return (1);
	return (0);
}
