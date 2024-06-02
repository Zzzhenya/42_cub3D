/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:11:08 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/02 21:36:00 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	init_struct_ray(t_ray *ray, t_player *player)
{
	ray->vert_hit = 0;
	ray->wall_hit_x = 0;
	ray->wall_hit_y = 0;
	ray->ray_angle = player->pa_rad - (60 * ((float)PI / 180.0) / 2);
	update_ray_angle(ray);
}

void	update_ray_angle(t_ray *ray)
{
	ray->ray_angle = normilize_angle(ray->ray_angle);
	if (ray->ray_angle > 0 && ray->ray_angle < (float)PI)
		ray->down = 1;
	else
		ray->down = 0;
	if (ray->down)
		ray->up = 0;
	else
		ray->up = 1;
	if ((ray->ray_angle < (float)(0.5f * (float)PI)) || \
	(ray->ray_angle > (float)(1.5f * (float)PI)))
		ray->right = 1;
	else
		ray->right = 0;
	if (ray->right)
		ray->left = 0;
	else
		ray->left = 1;
	if (!ray->vert_hit && ray->up)
		ray->side = 1;
	else if (ray->vert_hit && ray->left)
		ray->side = 2;
	if (!ray->vert_hit && ray->down)
		ray->side = 3;
	else if (ray->vert_hit && ray->right)
		ray->side = 4;
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

