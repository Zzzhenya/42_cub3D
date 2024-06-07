/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:00:20 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/07 11:48:04 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	render_3d_walls(t_data *data, t_player *player, t_ray *ray)
{
	init_struct_ray(ray, player);
	ray->ray_count = 0;
	while (ray->ray_count < W)
	{
		cast_ray(data, player, ray);
		render_strip_wall(data, ray);
		ray->ray_count++;
		ray->angle += ((60 * (PI / 180)) / W);
		update_angle(ray);
	}
}

void	render_strip_wall(t_data *data, t_ray *ray)
{
	t_line	line;
	float	distance_proj_plane;
	float	correct_wall_dist;

	correct_wall_dist = ray->distance * \
		cos(ray->angle - data->player->pa_rad);
	distance_proj_plane = (W / 2) / tan((60 * (PI / 180.0)) / 2);
	ray->wall_h = (TILE_SIZE / correct_wall_dist) * distance_proj_plane;
	line.x0 = ray->ray_count;
	line.y_top = ((int)H / 2) - (ray->wall_h / 2);
	if (line.y_top < 0)
		line.y_top = 0;
	line.y_botm = line.y_top + ray->wall_h;
	if (line.y_botm > H)
		line.y_botm = H;
	set_color_ceiling(&line, data, data->elem);
	set_color_wall(&line, data, data->ray);
	set_color_floor(&line, data, data->elem);
}
