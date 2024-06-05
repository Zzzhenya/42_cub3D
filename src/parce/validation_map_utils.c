/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:11:38 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/05 19:41:03 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	init_parse_struct(t_parse *data, int rows, char **map)
{
	data->cols = 0;
	data->rows = rows;
	data->map = copy_arr(map, rows);
	if (!data->map)
		return (1);
	return (0);
}

int	ft_isaplayer(char c)
{
	if (!c)
		return (0);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	else
		return (0);
}

//int	check_for_leaks(char **map, int rows, int cols, int x, int y, int k)
int	check_for_leaks(t_parse *data, int x, int y, int k)
{
	if ((y < 1 || y >= data->cols - 1 || x < 1 || x >= data->rows - 1)
		&& (data->map[x][y] != '1'))
		return (++k);
	if (data->map[x][y] != '0' && data->map[x][y] != ' ')
		return (k);
	data->map[x][y] = 'X';
	k = check_for_leaks(data, x - 1, y, k);
	k = check_for_leaks(data, x + 1, y, k);
	k = check_for_leaks(data, x, y - 1, k);
	k = check_for_leaks(data, x, y + 1, k);
	k = check_for_leaks(data, x - 1, y - 1, k);
	k = check_for_leaks(data, x + 1, y + 1, k);
	k = check_for_leaks(data, x - 1, y + 1, k);
	k = check_for_leaks(data, x + 1, y - 1, k);
	return (k);
}

size_t	get_max_len(char **map)
{
	size_t	curr;
	size_t	max;
	int		i;

	curr = 0;
	max = 0;
	i = 0;
	if (map[i])
		max = ft_strlen(map[i]);
	i++;
	while (map[i])
	{
		curr = ft_strlen(map[i]);
		if (curr > max)
			max = curr;
		i++;
	}
	return (max);
}

char	**copy_arr(char **map, int rows)
{
	char	**new;
	int		i;

	i = 0;
	new = NULL;
	new = (char **)malloc(sizeof(char *) * (rows + 1));
	if (!new)
	{
		print_err("Memory allocation error.");
		return (NULL);
	}
	while (i < rows)
	{
		new[i] = ft_strdup(map[i]);
		i ++;
	}
	new[i] = NULL;
	return (new);
}
