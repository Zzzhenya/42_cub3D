/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:01:31 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/07 13:07:47 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	normilize_offset(int cur, int target);

int	set_color_wall(t_line *line, t_data *data, t_ray *ray)
{
	int			dist_from_top;
	uint32_t	txr_pxl_color;
	t_txr		*tmp;
	t_line		cur;

	tmp = data->elem->txr[ray->side];
	cur.y_top = line->y_top;
	if (ray->vert_hit)
		cur.x1 = (int)ray->wall_hit_y % TILE_SIZE;
	else
		cur.x1 = (int)ray->wall_hit_x % TILE_SIZE;
	while (cur.y_top < line->y_botm)
	{
		dist_from_top = cur.y_top + (ray->wall_h / 2) - (H / 2);
		cur.y_botm = dist_from_top * ((float)tmp->height / ray->wall_h);
		cur.y_botm = normilize_offset(cur.y_botm, tmp->height);
		cur.x1 = normilize_offset(cur.x1, tmp->width);
		txr_pxl_color = tmp->addr[(tmp->width * cur.y_botm) + cur.x1];
		if ((W * cur.y_top) + line->x0 >= W * H || \
			(W * cur.y_top) + line->x0 < 0)
			return (perror("Error\nColor buffer index out of bounds"), 1);
		data->color_buf[(W * cur.y_top) + line->x0] = txr_pxl_color;
		cur.y_top++;
	}
	return (0);
}

// int	set_color_wall(t_line *line, t_data *data, t_ray *ray)
// {
// 	uint32_t	texture_pixel_color;
// 	int			texture_offset_x;
// 	int			texture_offset_y;
// 	int			distance_from_top;
// 	int			y;
// 	t_txr		*tmp;

// 	if (ray->side < 0 || ray->side > 3)
// 	{
//         perror("Error\nInvalid ray side index");
//         return 1;
//     }
// 	tmp = data->elem->txr[ray->side];
// 	y = line->y_top;
// 	if (ray->vert_hit)
// 		texture_offset_x = (int)ray->wall_hit_y % TILE_SIZE;
// 	else
// 		texture_offset_x = (int)ray->wall_hit_x % TILE_SIZE;
// 	while (y < line->y_botm)
// 	{
// 		distance_from_top = y + (ray->wall_h / 2) - (H / 2);
// 		texture_offset_y = distance_from_top * ((float)tmp->height / ray->wall_h);

// 		// Ensure texture coordinates are within bounds
// 		if (texture_offset_y >= tmp->height)
// 			texture_offset_y = tmp->height - 1;
// 		if (texture_offset_y < 0)
// 			texture_offset_y = 0;
// 		if (texture_offset_x >= tmp->width)
// 			texture_offset_x = tmp->width - 1;
// 		if (texture_offset_x < 0)
// 			texture_offset_x = 0;

// 		// Get the pixel color from the texture buffer
//         texture_pixel_color = tmp->addr[(tmp->width * texture_offset_y) + texture_offset_x];

// 		// Ensure color buffer index is within bounds
//         if ((W * y) + line->x0 >= W * H || (W * y) + line->x0 < 0) {
//             perror("Error\nColor buffer index out of bounds");
//             return 1;
//         }
//         data->color_buf[(W * y) + line->x0] = texture_pixel_color;
// 		y++;
// 	}
// 	return (0);
// }

void	set_color_ceiling(t_line *line, t_data *data, t_elem *elem)
{
	int	y;
	int	y_max;

	y = 0;
	y_max = line->y_top;
	line->color = ft_rgb(elem->rgb_c[0], elem->rgb_c[1], elem->rgb_c[2]);
	while (y < y_max)
	{
		data->color_buf[(W * y) + line->x0] = line->color;
		y++;
	}
}

void	set_color_floor(t_line *line, t_data *data, t_elem *elem)
{
	int	y;
	int	y_max;

	y = line->y_botm;
	y_max = H;
	line->color = ft_rgb(elem->rgb_f[0], elem->rgb_f[1], elem->rgb_f[2]);
	while (y < y_max)
	{
		data->color_buf[(W * y) + line->x0] = line->color;
		y++;
	}
}

void	clear_color_buf(t_data *data, uint32_t color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < W)
	{
		y = 0;
		while (y < H)
		{
			data->color_buf[(W * y) + x] = color;
			y++;
		}
		x++;
	}
}

static int	normilize_offset(int cur, int target)
{
	if (cur >= target)
		return (target - 1);
	if (cur < 0)
		return (0);
	return (cur);
}
