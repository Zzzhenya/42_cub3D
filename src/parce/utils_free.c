/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:11:38 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/02 18:57:27 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	print_error(char *s)
{
	ft_putstr_fd("Error\n", 2);
	if (s)
	{
		ft_putendl_fd(s, 2);
	}
	return (1);
}

void	ft_free(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

void	ft_free_arr(char **arr)
{
	char	**temp;
	int		i;

	i = 0;
	if (arr != NULL)
	{
		temp = arr;
		while (temp[i])
		{
			if (temp[i])
			{
				ft_free(&temp[i]);
			}
			i++;
		}
		free(temp);
		temp = NULL;
	}
}

void	free_arr_int(int **arr, int size)
{
	int	i;

	if (!arr || size == 0)
		return ;
	i = 0;
	while (i < size)
	{
		if (arr[i] != 0)
			free(arr[i]);
		i++;
	}
	free(arr);
}

void	clean_up_data(t_data *data)
{
	if (data->arr_file)
		ft_free_arr(data->arr_file);
	if (data->map->map)
		ft_free_arr(data->map->map);
	if (data->color_buf)
		free(data->color_buf);
	if (data->texture_buf)
		free(data->texture_buf);
	if (data->elem)
		free_elem(data, data->elem);
	if (data)
	{
        free(data->elem);
        free(data->map);
        free(data->ray);
        free(data->player);
        free(data);
    }
}

void	free_elem(t_data *data, t_elem *elem)
{
	if (!data || !elem)
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
