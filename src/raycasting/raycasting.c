/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:00:20 by ohladkov          #+#    #+#             */
/*   Updated: 2024/05/25 21:41:31 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	cast_all_rays(t_data *data, t_player *player, t_ray *ray)
{
	ray->ray_count = 0;
	ray->ray_angle = data->player->pa_rad - (FOV_R / 2);
	while (ray->ray_count < CASTED_RAYS)
	{
		cast_ray(data, player, ray); // count_intersections
		draw_player_dir(data, ray->x, ray->y);
		ray->ray_angle += FOV_R / CASTED_RAYS;
		ray->ray_count++;
	}
}

void	cast_ray(t_data *data, t_player *player, t_ray *ray)
{
	float	x_step;
	float	y_step;
	float	x_intercept;
	float	y_intercept;

	// ---------------------- horisontal ray-grid intersection --------------
	y_intercept = floor(player->py / CELLSIZE) * CELLSIZE;
	x_intercept = player->px + (y_intercept - player->py);

	
	




	// ---------------------- vertical ray-grid intersection ----------------

}

