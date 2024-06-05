/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_duplication.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:10:11 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/05 19:15:16 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	duplicate_str(char **arr, t_map *map, int ofs, int j)
{
	if (is_whitespace_str(arr[ofs + j]) && arr[ofs + j + 1] \
	&& !is_whitespace_str(arr[ofs + j + 1]))
		return (print_err("Map include empty lines"), 4);
	if (!is_whitespace_str(arr[ofs + j]))
		map->map[j] = ft_strdup(arr[ofs + j]);
	return (0);
}

int	game_map_dup(t_data *data, char **arr)
{
	int	i;
	int	j;
	int	ofs;

	i = 1;
	while (arr[i + data->offset])
	{
		if (!is_whitespace_str(arr[i + data->offset]))
			break ;
		i++;
	}
	ofs = i + data->offset;
	data->map->map = (char **)ft_calloc(data->lines - (ofs - 1) + 1, \
	sizeof(char *));
	if (!data->map->map)
		return (print_err(NULL), perror("Malloc"), 1);
	j = 0;
	while (arr[ofs + j])
	{
		if (duplicate_str(arr, data->map, ofs, j) != 0)
			return (4);
		j++;
	}
	return (0);
}
