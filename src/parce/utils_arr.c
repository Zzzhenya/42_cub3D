/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_arr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:11:25 by ohladkov          #+#    #+#             */
/*   Updated: 2024/04/07 18:08:38 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

size_t	ft_arrsize(char	**arr)
{
	size_t	size;

	size = 0;
	while (arr[size])
		size++;
	return (size);
}

size_t	ft_arrlen(char **arr)
{
	size_t	size;
	int		i;

	i = -1;
	size = 0;
	while (arr[++i])
	{
		size += ft_strlen(arr[i]);
	}
	return (size);
}

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}
