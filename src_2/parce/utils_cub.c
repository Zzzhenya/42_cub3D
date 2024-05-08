/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:11:28 by ohladkov          #+#    #+#             */
/*   Updated: 2024/04/21 16:28:40 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_2.h"

void	malloc_error(void)
{
	perror("malloc");
	exit(EXIT_FAILURE);
}

void	exit_data(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	clean_up_data(data);
	exit(1);
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

float	degrees_to_radians(int degrees)
{
	return (((degrees * PI) / 180.0));
}

int	get_degree(char view)
{
	if (view == 'N')
		return (90.0);
	else if (view == 'E')
		return (0.0);
	else if (view == 'S')
		return (270.0);
	else if (view == 'W')
		return (180.0);
	return (0.0);
}

int	fix_angle(int a)
{
	if (a > 359)
		a -= 360;
	if (a <= 0)
		a += 360;
	return (a);
}
