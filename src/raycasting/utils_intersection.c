/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:43:47 by ohladkov          #+#    #+#             */
/*   Updated: 2024/05/25 14:37:51 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/* 

ray.x += ray_cos;
ray.y += ray_sin;

ray_cos = cos(degree_to_radians(pa)) / CELLSIZE;
ray_sin = sin(degree_to_radians(pa)) / CELLSIZE;

Repeat step 2 until we reach the limit or we hit a wall.

distance = sqrt(powf(x - pl.x - 0.5, 2.) + powf(y - pl.y - 0.5, 2.));

5. Fix fisheye
distance = distance * cos(degree_to_radians(ray_angle - g->ray.angle))

This algorith is repeated window_width times, i.e. in every iteration we increment 
the angle until we have been through all the field of view. This distance is really 
helpful to calculate the height of the wall height:

wall_height = (window_height / (1.5 * distance));

*/

/* 

void	draw_rays_2d(t_data *data)
{
	float	ra; // ray  angle
	int	r = -1;
	float	a_tan;
	int	ry;
	int	rx;
	float	yo; //y offset 
	float	xo; //x offset 
	int	dof;
	int	map_x;
	int	map_y;
	int	map_p; // map position
	t_line	line;

	ra = fix_angle(data->map->pa);
	while (++r < 1)
	{
		dof = 0;
		// check vertical intersection

		a_tan = tan(degrees_to_radians(ra));
		// looking left
		if (cos(degrees_to_radians(ra)) > 0.001)
		{
			rx = (((int)data->map->px >> 6) << 6) + 64;
			ry = (data->map->px - rx) * a_tan + data->map->py;
			xo = CELLSIZE;
			yo = -(xo * a_tan);
		}
		else if (cos(degrees_to_radians(ra)) < -0.001) // looking right
		{
			rx = (((int)data->map->px >> 6) << 6) - 0.0001;
			ry = (data->map->px - rx) * a_tan + data->map->py;
			xo = -CELLSIZE;
			yo = -(xo * a_tan);
		}
		else // //looking up or down. no hit 
		{
			rx = data->map->px;
			ry = data->map->py;
			dof = 8;
		}
		while (dof < 8)
		{
			map_x = (int)(rx) >> 6;
			map_y = (int)(ry) >> 6;
			map_p = map_y * 64 + map_x;
			if (map_p > 0 && data->map->map[map_p][map_p] == '1') // hit the wall
			{
				dof = 8; //....if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=8; disV=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit         
   
			}
			else //check next horizontal
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
			line.x0 = data->map->px;
			line.x1 = rx;
			line.y0 = data->map->py;
			line.y1 = ry;
			line.color = 0x000000;
			draw_line(&line, data);
		}
	}
}
 */
