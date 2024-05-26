/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:11:08 by ohladkov          #+#    #+#             */
/*   Updated: 2024/05/26 17:21:42 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	init_struct_ray(t_ray *ray, t_player *player)
{
	ray->ray_angle = player->pa_rad - (FOV_R / 2);
	ray->vert_hit = 0;
	ray->wall_hit_x = 0;
	ray->wall_hit_y = 0;
	update_ray(ray);
}

void	update_ray(t_ray *ray)
{
	if (ray->ray_angle > 0 && ray->ray_angle < (float)PI)
		ray->down = 1;
	else
		ray->down = 0;
	if (ray->down)
		ray->up = 0;
	else
		ray->up = 1;
	if ((ray->ray_angle < (float)(0.5 * PI)) || (ray->ray_angle > (float)(1.5 * PI)))
		ray->right = 1;
	else
		ray->right = 0;
	if (ray->right)
		ray->left = 0;
	else
		ray->left = 1;
}
