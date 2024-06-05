/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:12:19 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/05 22:30:17 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	flood_fill_all_islands(t_parse *data, int k);
static int	find_player_loc(char **map, int *row, int *col, int *cols);
static int	map_not_rectangle(char **map);
static char	**convert_to_rectangle(char **map, int rows, size_t max);

int	validate_map(char **map, int rows)
{
	int		row; 
	int		col;
	t_parse	data;

	col = -1;
	row = -1;
	if (map_not_rectangle(map))
	{
		map = convert_to_rectangle(map, rows, get_max_len(map));
		if (!map)
			return (print_err("Memory allocation"), 1);
	}
	if (init_parse_struct(&data, rows, map) != 0)
		return (1);
	if (find_player_loc(map, &(row), &(col), &(data.cols)) != 0)
		return (free_map_ret_one(&data, "Player location error."));
	map[row][col] = '0';
	if (check_for_leaks(&data, row, col, 0) != 0)
		return (free_map_ret_one(&data, "Spawning area is incomplete."));
	if (flood_fill_all_islands(&data, 0) != 0)
		return (free_map_ret_one(&data, "Incomplete map."));
	ft_free_arr(data.map);
	return (0);
}

static int	map_not_rectangle(char **map)
{
	int		i;
	size_t	len;

	i = 0;
	len = 0;
	if (map[i])
		len = ft_strlen(map[i]);
	i ++;
	while (map[i])
	{
		if (ft_strlen(map[i]) != len)
			return (1);
		i ++;
	}
	return (0);
}

static char	**convert_to_rectangle(char **map, int rows, size_t max)
{
	char	*temp;
	char	*rest;
	int		i;

	temp = NULL;
	rest = NULL;
	i = 0;
	while (i < rows)
	{
		if (ft_strlen(map[i]) < max)
		{
			rest = malloc(sizeof(char) * (max - ft_strlen(map[i]) + 1));
			if (!rest)
				return (NULL);
			rest[max - ft_strlen(map[i])] = '\0';
			ft_memset(rest, ' ', max - ft_strlen(map[i]));
			temp = ft_strjoin(map[i], rest);
			free (rest);
			free (map[i]);
			map[i] = ft_strdup(temp);
			free (temp);
		}
		i ++;
	}
	return (map);
}

static int	find_player_loc(char **map, int *row, int *col, int *cols)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_isaplayer(map[i][j]))
			{
				if (*row == -1 && *col == -1)
				{
					*row = i;
					*col = j;
				}
				else
					return (1);
			}
			j++;
		}
		*cols = j;
		i++;
	}
	return (0);
}

static int	flood_fill_all_islands(t_parse *data, int k)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			if (data->map[i][j] == '0')
			{
				k += check_for_leaks(data, i, j, k);
				if (k > 0)
					return (1);
			}
			j ++;
		}
		i ++;
	}
	return (0);
}
