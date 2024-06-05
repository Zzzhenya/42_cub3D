/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:12:19 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/03 15:08:27 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

typedef struct s_parse
{
	int 	rows;
	int 	cols;
	char 	**map;
}	t_parse;

int ft_isaplayer(char c)
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

int	map_not_rectangle(char **map)
{
	int i;
	size_t len;

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
	i ++;
	while (map[i])
	{
		curr = ft_strlen(map[i]);
		if (curr > max)
			max = curr;
		i ++;
	}
	return (max);
}

char	**convert_to_rectangle(char **map, int rows, size_t max)
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

int	find_player_loc(char **map, int *row, int *col, int *cols)
{
	int i;
	int j;

	i = 0;
	j = 0;
	// Already handled in the file parser
	if (!map || !map[i] || !map[i][j])
	{
		print_err("Empty map");
		return (1);
	}
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
				// When there is more than one player
				// Already handled in a previous parsing function - I thinks
			}
			j ++;
		}
		*cols = j;
		i ++;
	}
	return (0);
}

/**
 * return valu: 0 - valid map, otherwise not 0
 * 
		// Check for stray 0's

	// Check for holes in the first row
	while (map[i][j] && ft_isspace(map[i][j]))
		j ++;
	while (map[i][j] && map[i][j] == '1')
		j ++;
	if (map[i][j] && (map[i][j] == '0' || ft_isspace(map[i][j])))
	{
		print_err("First row has a hole");
		return (1);
	}
	Check whether the map only has 
		leading and trailing spaces in lines, 
		1, 0 and one of N, S, E, W
		Find the location of N,S,E or W and check it is enclosed by 1's

		Check the entire map's 0's are enclosed by 1's
*/

void	init_struct(t_parse *data, int rows, char **map)
{
	data->cols = 0;
	data->rows = rows;
	data->map = map;
	// get a copy of the map 
}

int	flood_fill_all_islands(t_parse *data, int k)
{
	int i = 0;
	int j = 0;

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

int	validate_map(char **map, int rows)
{
	int 	row; 
	int 	col;
	t_parse	data;

	col = -1;
	row = -1;
	// print_arr(map);
	// printf("rows: %i\n", rows);
	if (map_not_rectangle(map))
	{
		map = convert_to_rectangle(map, rows, get_max_len(map));
		if (!map)
		{
			print_err("Memory allocation error");
			return (1);
		}
	}
	init_struct(&data, rows, map);
	if (find_player_loc(map, &(row), &(col), &(data.cols)) != 0)
	{
		print_err("Player location error");
		return (1);
	}
	map[row][col] = '0';
	if (check_for_leaks(&data, row, col, 0) != 0)
	{
		print_err("Spawning area is incomplete");
		return (1);
	}
	if (flood_fill_all_islands(&data, 0) != 0)
	{
		print_err("Incomplete map");
		return (1);
	}
	print_arr(map);
	return (0);
}

/*
Ignore leading whitespaces
while (*data.cur_row == ' ')
	data.cur_row++;
Rule 1: Ignore leading whitespaces
Rule 2: Only accept '1's and ' 's in the 0th and final rows
Rule 3: First and final character should always be '1'
Rule 5: Ensure current character is '1' if it extends beyond the top row
Rule 6: Ensure current character is '1' if it extends beyond the bottom row

Ignore all leading whitespaces.
If the current row is the 0th row or the final row, only accept '1's and ' 's.
else, The first and final character should always be a '1'.
In the case of any non leading whitespaces, the only acceptable characters adjacent to the space are '1's or ' 's.
If strlen(cur_row) > strlen(row_on_top) && current col > strlen(row_on_top), current character should be '1'
If strlen(cur_row) > strlen(row_on_bottom) && current col > strlen(row_on_btm), current character should be '1'
*/
