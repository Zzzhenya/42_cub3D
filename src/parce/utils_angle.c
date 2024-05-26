
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_angle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:11:28 by ohladkov          #+#    #+#             */
/*   Updated: 2024/05/25 21:10:44 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

float	degrees_to_radians(int degrees)
{
	return ((degrees * (float)((float)PI / 180.0)));
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
