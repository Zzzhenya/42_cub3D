/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:11:28 by ohladkov          #+#    #+#             */
/*   Updated: 2024/05/25 21:10:44 by ohladkov         ###   ########.fr       */
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

float	degrees_to_radians(int degrees)
{
	return ((degrees * (PI / 180.0)));
}

int	get_degree(char view)
{
	if (view == 'N')
		return (270.0);
	else if (view == 'E')
		return (0.0);
	else if (view == 'S')
		return (90.0);
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
