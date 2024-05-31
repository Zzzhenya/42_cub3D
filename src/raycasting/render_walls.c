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
	float	distance_proj_plane;
	float	correct_wall_dist;
	int		col_intencity;

	correct_wall_dist = ray->distance * cos(ray->ray_angle - data->player->pa_rad);
	distance_proj_plane = (W / 2) / tan((60 * (PI / 180.0)) / 2);
	ray->wall_height = (TILE_SIZE / correct_wall_dist) * distance_proj_plane;
	line.x0 = ray->ray_count * WALL_STRIP_WIDTH;
	line.y_top = ((int)H / 2) - (ray->wall_height / 2);
	if (line.y_top < 0)
		line.y_top = 0;
	line.y_botm = line.y_top + ray->wall_height;
	if (line.y_botm > H)
		line.y_botm = H;
	int alpha = 1.0;
	if (ray->vert_hit)
		col_intencity = 255;
	else
		col_intencity = 180;
	printf("x0: %i, y0: %i, y1: %i\n", line.x0, line.y_top, line.y_botm);
	line.color = ft_rgba(col_intencity, col_intencity, col_intencity, alpha);
	set_color_ceiling(&line, data);
	set_color_wall(&line, data);
	set_color_floor(&line, data);
}
