/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:00:20 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/05 22:32:16 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	cast_all_rays(t_data *data, t_player *player, t_ray *ray, float scl)
{
	init_struct_ray(ray, player);
	ray->ray_count = 0;
	while (ray->ray_count < CASTED_RAYS)
	{
		cast_ray(data, player, ray);
		draw_player_dir(data, ray->wall_hit_x, ray->wall_hit_y, scl);
		ray->ray_count++;
		ray->ray_angle += ((60 * (PI / 180)) / CASTED_RAYS);
		update_ray_angle(ray);
	}
}

