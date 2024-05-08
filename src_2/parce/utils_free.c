/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:11:38 by ohladkov          #+#    #+#             */
/*   Updated: 2024/04/21 15:49:46 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_2.h"

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

void	free_elem(t_elem *elem)
{
	ft_free(&elem->ea);
	ft_free(&elem->we);
	ft_free(&elem->no);
	ft_free(&elem->so);
}

void	clean_up_data(t_data *data)
{
	if (data->arr_file)
		ft_free_arr(data->arr_file);
	if (data->map->map)
		ft_free_arr(data->map->map);
	free_elem(data->elem);
	free(data);
}
