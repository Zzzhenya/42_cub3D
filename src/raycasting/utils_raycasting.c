/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:43:47 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/02 13:11:08 by ohladkov         ###   ########.fr       */
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


/**
 * uint32_t get_texture_pixel(t_data *data, int x, int y) {
    if (x < 0 || x >= data->img_width || y < 0 || y >= data->img_height) {
        return 0; // Return a default color or handle error
    }

    int pixel_index = y * data->size_line + x * (data->bits_per_pixel / 8);
    return *(uint32_t *)(data->img_data + pixel_index);
}
*/