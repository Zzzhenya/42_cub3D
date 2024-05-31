/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:43:47 by ohladkov          #+#    #+#             */
/*   Updated: 2024/05/31 14:16:50 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

float	get_distance(float px, float py, float hit_x, float hit_y)
{
	float	x;
	float	y;

	x = px - hit_x;
	y = py - hit_y;
	return (sqrt((x * x) + (y * y)));
}

float	normilize_angle(float angle)
{
	angle = fmod(angle, (2.0 * PI));
    if (angle < 0)
    {
		angle += 2.0 * PI;
	}
	return (angle);
}

