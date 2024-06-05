/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:11:38 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/05 19:22:11 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
