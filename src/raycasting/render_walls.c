/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_strip_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:00:20 by ohladkov          #+#    #+#             */
/*   Updated: 2024/05/30 16:36:02 by ohladkov         ###   ########.fr       */
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
		ray->ray_angle += ((60 * ((float)PI / 180.0)) / W);
		update_ray_angle(ray);
	}
}

void	render_strip_wall(t_data *data, t_ray *ray)
{
	t_line	line;
	float	wall_strip_height;
	float	correct_wall_dist;

	correct_wall_dist = ray->distance * cos(ray->ray_angle - data->player->pa_rad);
	wall_strip_height = (TILE_SIZE / correct_wall_dist) * distance_proj_plane();
	line.x0 = ray->ray_count * WALL_STRIP_WIDTH;
	line.y0 = ((float)H / 2) - round(wall_strip_height / 2);
	line.y1 = round(wall_strip_height);
	if (line.y1 > H)
		line.y1 = H;
	line.color = ft_rgb(95, 87, 79);
	// printf("wall_strip_height: %f, H: %f, y0: %i, y1: %i\n", wall_strip_height, (float)H, line.y0, line.y1);
	draw_line(&line, data);
}
