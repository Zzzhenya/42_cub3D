/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:00:20 by ohladkov          #+#    #+#             */
/*   Updated: 2024/04/21 15:48:55 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_2.h"

void	draw_celing(t_data *data, t_ray *ray);
void	draw_wall(t_data *data, t_ray *ray);
void	draw_floor(t_data *data, t_ray *ray);
float	get_sqrt(t_map *player, t_ray *ray);

/**
 * Raycasting logic
 */

/* void	raycasting(t_data *data)
{
	t_ray	ray;

	// ray.ray_angle = data->map->pa - HFOV;
	ray.ray_angle = data->map->pa_rad - (FOV_R / 2);
	ray.ray_count = 0;
	ray.wall = 0;
	while (ray.ray_count < W)
	{
		ray.y = data->map->py;
		ray.x = data->map->px;
		ray.ray_cos = cos(ray.ray_angle); //  * CELLSIZE
		ray.ray_sin = sin(ray.ray_angle); // * CELLSIZE
		// my_print(data, &ray);
		ray.wall = 0;
		// TODO count_intersections
		while (ray.wall == 0)
		{
			ray.x += ray.ray_cos;
			ray.y += ray.ray_sin;
			if (data->map->map[(int)floor(ray.y)][(int)floor(ray.x)] == '1')
				ray.wall = 1;
		}
		ray.distance = get_sqrt(data->map, &ray);
		ray.distance = ray.distance * cos(ray.ray_angle - data->map->pa_rad); // fish eye fix
		ray.wall_height = (int)floor(HALF_H / ray.distance);
		draw_celing(data, &ray);
		draw_wall(data, &ray);
		draw_floor(data, &ray);
		ray.ray_angle += STEP_ANGLE;
		ray.ray_count++;
	}
}
*/

/* void	calc_ray(t_data *data, t_ray *ray)
{
	printf("ray->ray_angle: %f, degrees: %f\n", ray->ray_angle, ray->ray_angle * 180 / PI);
	if (ray->ray_angle > 0 && ray->ray_angle < PI)
	{
		// Ray look north
		write(1, "here1\n", 6);
		ray->x = data->map->px - cos(ray->ray_angle);
		ray->y = data->map->py - sin(ray->ray_angle);
	}
	else if (ray->ray_angle > PI && ray->ray_angle < 2 * PI)
	{
		// Ray look south
		write(1, "here2\n", 6);
		ray->x = data->map->px + cos(ray->ray_angle);
		ray->y = data->map->py - sin(ray->ray_angle);
	}
	else
	{
		// Ray look right or keft
		write(1, "here3\n", 6);
		ray->x = data->map->px + cos(ray->ray_angle);
		ray->y = data->map->py + sin(ray->ray_angle);
	}

	if (ray->ray_angle >= 0 && ray->ray_angle < PI / 2)
	{
		// Ray look north-east
		write(1, "here1\n", 6);
		ray->x = data->map->px + cos(ray->ray_angle);
		ray->y = data->map->py - sin(ray->ray_angle);
	}
	else if (ray->ray_angle >= PI / 2 && ray->ray_angle < PI)
	{
		// Ray look north-west
		write(1, "here2\n", 6);
		ray->x = data->map->px - cos(ray->ray_angle);
		ray->y = data->map->py - sin(ray->ray_angle);
	}
	else if (ray->ray_angle >= PI && ray->ray_angle < 3 * PI / 2)
	{
		// Ray look south-west
		write(1, "here3\n", 6);
		ray->x = data->map->px - cos(ray->ray_angle);
		ray->y = data->map->py + sin(ray->ray_angle);
	}
	else
	{
		// Ray look south-east
		write(1, "here4\n", 6);
		ray->x = data->map->px + cos(ray->ray_angle);
		ray->y = data->map->py + sin(ray->ray_angle);
	}

} */

/* 
void	calc_ray(t_data *data, t_ray *ray)
{
	// (ray_angle == pa_rad + (FOV / 2))
	float px = data->map->px * CELLSIZE;
	float py = data->map->py * CELLSIZE;
	float distance_v = 100000;
	float distance_h = 100000;
	float vector_x = 0;
	float vector_y = 0;
	int	flag = 1;

	// vertical line
	float a_tan = tan(ray->ray_angle);
	float xo = 0.0; //x offset 
	float yo = 0.0; //y offset 
	// int	side = 0;
	if (cos(ray->ray_angle) > 0.001)
	{
		// printf("cos: %f\n", cos(ray->ray_angle));
		write(1, "LEFT\n", 7);
		ray->x = (((int)px >> 6) << 6) + 64;
		ray->y = (px - ray->x) * a_tan + py;
		xo = 64;
		yo  = -xo * a_tan;
		flag = 1;
	}
	else if (cos(ray->ray_angle) < -0.001)
	{
		// printf("cos: %f\n", cos(ray->ray_angle));
		write(1, "RIGHT\n", 7);
		ray->x = (((int)px >> 6) << 6) - 0.0001;
		ray->y = (px - ray->x) * a_tan + py;
		xo = -64;
		yo = -xo * a_tan;
		flag = 1;
	}
	else
	{
		write(1, "UP or DOWN\n", 11);
		ray->y = py;
		ray->x = px;
		flag = 0;
	}
	printf("R_A: %f, ray_y: %f, ray->x: %f, xo = %f, yo: %f\n", ray->ray_angle, ray->y, ray->x, xo, yo);
	printf("px: %f, py: %f, a_tan: %f\n", px, py, a_tan);
	int mx = 0;
	int	my = 0;
	while (flag)
	{
		// mx = (int)(ray->x) >> 6;
		// my = (int)(ray->y) >> 6;
		mx = ray->x / 64;
		my = ray->y / 64;
		if (mx && my && my < data->rows && mx < (int)ft_strlen(data->map->map[my]) && data->map->map[my][mx] == '1')
		{
			// write(1, "HIT THE WALL\n", 13);
			distance_v = cos(ray->ray_angle) * (ray->x - px) - sin(ray->ray_angle) * (ray->y - py);
			flag = 0;
			break ;
		}
		else
		{
			// write(1, "NO WALL\n", 9);
			ray->x += xo;
			ray->y += yo;
			// printf("R_A: %f, ray_y: %f, ray->x: %f, xo = %f, yo: %f\n", ray->ray_angle, ray->y, ray->x, xo, yo);
			// printf("px: %f, py: %f, mx: %d, my: %d, MAP: %c\n", px, py, mx, my, data->map->map[my][mx]);
		}
	}
	
	vector_x = ray->x;
	vector_y = ray->y;

	// horisontal
	flag = 1;
	a_tan = 1.0 / a_tan;
	if (sin(ray->ray_angle) > 0.001)
	{
		write(1, "UP\n", 3);
		ray->y = (((int)py >> 6) << 6) - 0.0001;
		ray->x = (py - ray->y) * a_tan + px;
		yo = -64;
		xo = -yo * a_tan;
		flag = 1;
	}
	else if (sin(ray->ray_angle < -0.001))
	{
		write(1, "DOWN\n", 3);
		ray->y = (((int)py >> 6) << 6) + 64;
		ray->x = (py - ray->y) * a_tan + px;
		yo = 64;
		xo = -yo * a_tan;
		flag = 1;
	}
	else
	{
		write(1, "L or R\n", 7);
		ray->y = py;
		ray->x = px;
		flag = 0;
	}
	while (flag == 1)
	{
		// mx = (int)(ray->x) >> 6;
		// my = (int)(ray->y) >> 6;
		mx = ray->x / 64;
		my = ray->y / 64;
		if (mx && my && my < data->rows && mx < (int)ft_strlen(data->map->map[my]) && data->map->map[my][mx] == '1')
		{
			// write(1, "HIT THE WALL\n", 13);
			distance_h = cos(ray->ray_angle) * (ray->x - px) - sin(ray->ray_angle) * (ray->y - py);
			flag = 0;
			break ;
		}
		else
		{
			// write(1, "NO WALL\n", 9);
			ray->x += xo;
			ray->y += yo;
			// printf("R_A: %f, ray_y: %f, ray->x: %f, xo = %f, yo: %f\n", ray->ray_angle, ray->y, ray->x, xo, yo);
			// printf("px: %f, py: %f, mx: %d, my: %d, MAP: %c\n", px, py, mx, my, data->map->map[my][mx]);
		}
	}
	if (distance_v < distance_h) // horisontal hit first
	{
		ray->y = vector_y;
		ray->x = vector_x;
		distance_h = distance_v;
	}
	printf("R_A: %f, ray_y: %f, ray->x: %f, xo = %f, yo: %f\n", ray->ray_angle, ray->y, ray->x, xo, yo);
	printf("px: %f, py: %f, mx: %d, my: %d, MAP: %c\n", px, py, mx, my, data->map->map[my][mx]);
	printf("dist_h: %f, dist_v: %f\n", distance_h, distance_v);


	//  place to cast walls 
	// exit(1);
}
 */

/*
void	calc_ray(t_data *data, t_ray *ray)
{
	float px = data->map->px * 64;
	float py = data->map->py * 64;
	float distance_v = 100000;
	float distance_h = 100000;
	float vector_x = 0;
	float vector_y = 0;
	int	flag = 1;
	int mx = -1;
	int	my = -1;

	// Finding horizontal intersection
	float a_tan = tan(ray->ray_angle);
	// printf("a_tan: %f\n", a_tan);
	float xo = 0; //x offset
	float yo = 0; //y offset 
	// int	side = 0;
	if (sin(ray->ray_angle) > 0.001)
	{
		write(1, "UP\n", 3);
		ray->y = floor(py / 64) * 64 - 1; // / CELLSIZE get grid
		ray->x = (py - ray->y) / a_tan + px; //  / CELLSIZE get grid
		yo = -64;
		xo = yo / a_tan;
		flag = 1;
	}
	else if (sin(ray->ray_angle) < -0.001)
	{
		write(1, "DOWN\n", 3);
		ray->y = floor(py / 64) * 64 + 64;
		ray->x = (py - ray->y) * a_tan + px;
		yo = 64;
		xo = yo / a_tan;
		flag = 1;
	}
	if (sin(ray->ray_angle) < 0.001 && sin(ray->ray_angle) > -0.001)
	{
		write(1, "here1\n", 6);
		distance_h = 100000;
		ray->x = px;
		ray->y = py;
	}
	else
	{
		while (flag == 1)
		{
			mx = (int)floor(ray->x / 64);
			my = (int)floor(ray->y / 64);
			if (mx >= 0 && my >= 0 && my < data->rows && mx < (int)ft_strlen(data->map->map[my]) && data->map->map[my][mx] == '1')
			{
				write(1, "HIT THE WALL\n", 13);
				// distance_h = cos(ray->ray_angle) * (ray->x - px) - sin(ray->ray_angle) * (ray->y - py);
				// distance_h = (ray->x - px) * (1 / cos(ray->ray_angle));
				distance_h = get_sqrt(data->map, ray);
				flag = 0;
				xo = 0;
				yo = 0;
				break ;
			}
			else
			{
				write(1, "NO WALL\n", 9);
				ray->x += xo;
				ray->y += yo;
				// printf("R_A: %f, ray_y: %f, ray->x: %f, xo = %f, yo: %f\n", ray->ray_angle, ray->y, ray->x, xo, yo);
				// printf("px: %f, py: %f, mx: %d, my: %d, MAP: %c\n", px, py, mx, my, data->map->map[my][mx]);
			}
		}
	}
	mx = -1;
	mx = -1;
	vector_x = ray->x;
	vector_y = ray->y;
	// Finding vertical intersection
	if (cos(ray->ray_angle) > 0.001)
	{
		write(1, "RIGHT\n", 7);
		ray->x = floor(px / 64) * 64 + 64;
		ray->y = (px - ray->x) * a_tan + py;
		xo = 64;
		yo = xo * a_tan;
		flag = 1;
	}
	else if (cos(ray->ray_angle) < -0.001)
	{
		
		write(1, "LEFT\n", 5);
		ray->x = floor(px / 64) * 64 - 1;
		ray->y = (px - ray->x) * a_tan + py;
		xo = -64;
		yo = xo * a_tan;
		flag = 1;
	}
	printf("cos(angl): %f\n", cos(ray->ray_angle));
	printf("sin(angl): %f\n", sin(ray->ray_angle));
	if (cos(ray->ray_angle) < 0.01 && cos(ray->ray_angle) > -0.01)
	{
		distance_v = 100000;
		write(1, "here2\n", 6);
		ray->x = px;
		ray->y = py;
	}
	else
	{
		
		while (flag)
		{
			mx = (int)floor(ray->x / 64);
			my = (int)floor(ray->y / 64);
			if (mx >= 0 && my >= 0 && my < data->rows && mx < (int)ft_strlen(data->map->map[my]) && data->map->map[my][mx] == '1')
			{
				write(1, "HIT THE WALL\n", 13);
				// distance_v = cos(ray->ray_angle) * (ray->x - px) - sin(ray->ray_angle) * (ray->y - py);
				// distance_v = (ray->x - px) * (1 / sin(ray->ray_angle));
				distance_v = get_sqrt(data->map, ray);
				flag = 0;
				xo = 0;
				yo = 0;
				break ;
			}
			else
			{
				write(1, "NO WALL\n", 9);
				ray->x += xo;
				ray->y += yo;
				printf("xo = %f, yo: %f\n", xo, yo);
				// printf("R_A: %f, ray_y: %f, ray->x: %f, xo = %f, yo: %f\n", ray->ray_angle, ray->y, ray->x, xo, yo);
				printf("px: %f, py: %f, mx: %d, my: %d, MAP: %c\n", px, py, mx, my, data->map->map[my][mx]);
				// return ;
			}
		}
	}
	printf("dist_h: %f, dist_v: %f\n", distance_h, distance_v);

	if (distance_h < distance_v) // horisontal hit first
	{
		ray->y = vector_y;
		ray->x = vector_x;
		distance_v = distance_h;
	}
	// printf("R_A: %f, ray_y: %f, ray->x: %f, xo = %f, yo: %f\n", ray->ray_angle, ray->y, ray->x, xo, yo);
	// printf("px: %f, py: %f, mx: %d, my: %d, MAP: %c\n", px, py, mx, my, data->map->map[my][mx]);
	

	//  place to cast walls 
	// exit(1);
}
*/

/* 
void	calc_ray(t_data *data, t_ray *ray)
{
	float px = data->map->px * CELLSIZE;
	float py = data->map->py * CELLSIZE;
	float distance_v = 100000;
	float distance_h = 100000;
	// float vector_x = 0;
	// float vector_y = 0;

	// Vertical line
	float tan_ray = tan(ray->ray_angle);
	float delta_xv = (ray->ray_angle > PI / 2 && ray->ray_angle < 3 * PI / 2) ? -CELLSIZE : CELLSIZE;
	float delta_yv = delta_xv * tan_ray;
	float x_v = floor(px / CELLSIZE) * CELLSIZE + delta_xv;
	float y_v = py + (px - x_v) * tan_ray;

	// Horizontal line
	float cot_ray = 1.0 / tan_ray;
	float delta_yh = (ray->ray_angle > PI) ? -CELLSIZE : CELLSIZE;
	float delta_xh = delta_yh * cot_ray;
	float y_h = floor(py / CELLSIZE) * CELLSIZE + delta_yh;
	float x_h = px + (py - y_h) * cot_ray;

	// Check for vertical intersection
	if ((ray->ray_angle > 0 && ray->ray_angle < PI) || (ray->ray_angle > 2 * PI && ray->ray_angle < 3 * PI))
	{
		if (ray->ray_angle > 0 && ray->ray_angle < PI)
			x_v -= 0.0001;
		else
			x_v += CELLSIZE;
		while (data->map->map[(int)(y_v / CELLSIZE)][(int)(x_v / CELLSIZE)] != '1')
		{
			x_v += delta_xv;
			y_v += delta_yv;
		}
		distance_v = fabs((x_v - px) / cos(ray->ray_angle));
	}

	// Check for horizontal intersection
	if ((ray->ray_angle > PI / 2 && ray->ray_angle < 3 * PI / 2) || (ray->ray_angle < 0 || ray->ray_angle > 2 * PI))
	{
		if (ray->ray_angle > PI / 2 && ray->ray_angle < 3 * PI / 2)
			y_h -= 0.0001;
		else
			y_h += CELLSIZE;
		while (data->map->map[(int)(y_h / CELLSIZE)][(int)(x_h / CELLSIZE)] != '1')
		{
			x_h += delta_xh;
			y_h += delta_yh;
		}
		distance_h = fabs((y_h - py) / sin(ray->ray_angle));
	}

	// Choose the closer intersection point
	if (distance_v < distance_h)
	{
		ray->x = x_v;
		ray->y = y_v;
		ray->distance = distance_v;
	}
	else
	{
		ray->x = x_h;
		ray->y = y_h;
		ray->distance = distance_h;
	}
}
 */

void	cast_rays(t_data *data, t_ray *ray, t_player *player)
{
	int	ray_count;

	// ray.ray_angle = data->map->pa_rad - (FOV_R / 2);
	data->ray->ray_angle = player->pa_rad;
	// printf("RAY_ANGLE: %f, TAN: %f\n", data->ray->ray_angle, tan(data->ray->ray_angle));
	ray_count = 0;
	// draw_player_dir(data, data->map->px + cos(data->map->pa_rad), data->map->px + sin(data->map->pa_rad));
	while (ray_count < 1)
	{
		// printf("before px = %f, py = %f\n", data->map->px, data->map->py);
		calc_ray(data, data->ray); // count_intersections
		// printf("after ray.x = %f, ray.y = %f\n", data->ray->x, data->ray->y);
		draw_player_dir(data, data->ray->x, data->ray->y);
		// ray.ray_angle += STEP_ANGLE;
		ray_count++;
	}
}

void	draw_celing(t_data *data, t_ray *ray)
{
	t_line	line;

	line.color = ft_rgb(data->elem->rgb_c[0], data->elem->rgb_c[1], data->elem->rgb_c[2]);
	line.x0 = ray->ray_count;
	line.y0 = 0;
	line.x1 = ray->ray_count;
	line.y1 = HALF_H - ray->wall_height;
	draw_line(&line, data);
}

void	draw_wall(t_data *data, t_ray *ray)
{
	t_line	line;

	line.color = 0xff0000;
	line.x0 = ray->ray_count;
	line.y0 = HALF_H - ray->wall_height;
	line.x1 = HALF_H + ray->wall_height;
	line.y1 = H;
	draw_line(&line, data);
}

void	draw_floor(t_data *data, t_ray *ray)
{
	t_line	line;

	line.color = ft_rgb(data->elem->rgb_f[0], data->elem->rgb_f[1], data->elem->rgb_f[2]);
	line.x0 = ray->ray_count;
	line.y0 = HALF_H + ray->wall_height;
	line.x1 = ray->ray_count;
	line.y1 = H;
	draw_line(&line, data);
}

float	get_sqrt(t_map *player, t_ray *ray)
{
	int	x;
	int	y;

	x = player->px - ray->x;
	y = player->py - ray->y;
	return (sqrt((x * x) + (y * y)));
}
