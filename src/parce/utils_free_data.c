/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:11:38 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/05 19:40:06 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	clean_up_data(t_data *data)
{
	if (data->arr_file)
		ft_free_arr(data->arr_file);
	if (data->map->map)
		ft_free_arr(data->map->map);
	if (data->color_buf)
		free(data->color_buf);
	if (data->elem)
	{
		free_elem(data->elem);
		free(data->elem);
		data->elem = NULL;
	}
	if (data)
	{
		free(data->map);
		free(data->ray);
		free(data->player);
		free(data);
	}
}

void	free_elem(t_elem *elem)
{
	if (!elem)
		return ;
	ft_free(&elem->ea);
	ft_free(&elem->we);
	ft_free(&elem->no);
	ft_free(&elem->so);
}

void	free_texture(t_data *data, t_elem *elem)
{
	int	i;

	if (!data || !elem)
		return ;
	i = 0;
	while (i < 4)
	{
		if (elem->txr[i])
		{
			if (elem->txr[i]->img)
			{
				mlx_destroy_image(data->mlx_ptr, elem->txr[i]->img);
				elem->txr[i]->img = NULL;
			}
			free(elem->txr[i]);
			elem->txr[i] = NULL;
		}
		i++;
	}
}

int	free_map_ret_one(t_parse *data, char *msg)
{
	ft_free_arr(data->map);
	print_err(msg);
	return (1);
}
