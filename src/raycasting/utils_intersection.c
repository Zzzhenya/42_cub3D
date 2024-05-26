/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:43:47 by ohladkov          #+#    #+#             */
/*   Updated: 2024/05/26 21:25:44 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/* 

ray.x += ray_cos;
ray.y += ray_sin;

ray_cos = cos(degree_to_radians(pa)) / TILE_SIZE;
ray_sin = sin(degree_to_radians(pa)) / TILE_SIZE;

Repeat step 2 until we reach the limit or we hit a wall.

distance = sqrt(powf(x - pl.x - 0.5, 2.) + powf(y - pl.y - 0.5, 2.));

5. Fix fisheye
distance = distance * cos(degree_to_radians(ray_angle - g->ray.angle))

This algorith is repeated window_width times, i.e. in every iteration we increment 
the angle until we have been through all the field of view. This distance is really 
helpful to calculate the height of the wall height:

wall_height = (window_height / (1.5 * distance));

*/
