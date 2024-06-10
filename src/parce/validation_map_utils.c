/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:11:38 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/10 20:02:01 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	invalid_map_char(char **map, int rows)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (!ft_strchr("SNEW01 ", map[i][j]))
				return (1);
			j ++;
		}
		i ++;
	}
	return (0);
}

int	init_parse_struct(t_parse *data, int rows, char **map)
{
	data->cols = 0;
	data->rows = rows;
	data->map = copy_arr(map, rows);
	if (!data->map)
		return (1);
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
	if (data->map[x][y] != ' ')
		data->map[x][y] = 'X';
	else
		return (++k);
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
