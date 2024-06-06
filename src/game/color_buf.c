/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:01:31 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/05 22:06:35 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	normilize_offset(int *cur, int target);

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
		normilize_offset(&cur.y_botm, &tmp->height);
		normilize_offset(&cur.x1, &tmp->width);
		txr_pxl_color = tmp->addr[(tmp->width * cur.y_botm) + cur.x0];
		if ((W * cur.y_top) + line->x0 >= W * H || \
			(W * cur.y_top) + line->x1 < 0)
			return (perror("Error\nColor buffer index out of bounds"), 1);
		data->color_buf[(W * cur.y_top) + line->x0] = txr_pxl_color;
		cur.y_top++;
	}
	return (0);
}

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

static void	normilize_offset(int *cur, int target)
{
	if (cur >= target)
		*cur = target - 1;
	if (cur < 0)
		*cur = 0;
}
