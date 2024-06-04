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

int ft_isaplayer(char c)
{
	if (!c)
		return (0);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	else
		return (0);
}
/*
void	fill(char **map, int row, int col, int rows, int cols)
{
	if (map[row][col] == '1')
		return;
	if (row <= 0 || col <= 0 || row >= rows || col >= cols)
		return;
	map[row][col] = 'X';
	fill(map, row, col + 1, rows, cols) ;
	fill(map, row + 1, col, rows, cols);
	//fill(map, row, col - 1 ,rows, cols);
	//fill(map, row - 1, col, rows, cols);
}*/

int	check_for_leaks(char **map, int rows, int cols, int x, int y, int k)
{
	if ((y < 1 || y >= cols - 1 || x < 1 || x >= rows - 1) && map[x][y] != '1')
	{
		return (++k);
	}
	if (map[x][y] != '0')
		return (k);
	map[x][y] = 'X';
	k = check_for_leaks(map, rows, cols, x - 1, y, k);
	k = check_for_leaks(map, rows, cols, x + 1, y, k);
	k = check_for_leaks(map, rows, cols, x, y - 1, k);
	k = check_for_leaks(map, rows, cols, x, y + 1, k);
	return (k);
}

// char **convert_to_rectangle(char **map, int rows)
// {
// 	char **new;
// 	size_t max = 0;	
// 	size_t len = 0;
// 	int i = 0;

// 	while (i < rows)
// 	{
// 		len = ft_strlen(map[i]);
// 		if (len > max)
// 			max = len;
// 		i ++;
// 	}


// }

/**
 * return valu: 0 - valid map, otherwise not 0
*/
int	validate_map(char **map, int rows)
{
	//(void)map;
	int cols = 0;
	print_arr(map);
	printf("rows: %i\n", rows);
	// map = convert_to_rectangle(map, rows);
	int i = 0;
	int j = 0;
	int row = -1; int col = -1;
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
				if (row == -1 && col == -1)
				{
					row = i;
					col = j;
					printf("ROW: %d, COL: %d\n", row, col);
				}
				else
					return (1);
			}
			j ++;
		}
		cols = j;
		i ++;
	}
	map[row][col] = '0';
	if (check_for_leaks(map, rows, cols,row, col, 0) != 0)
	{
		print_arr(map);
		print_err("Map is not complete");
	}
	// Change the player to X
	//map[row][col] = 'X';
	// fill with X
	//fill(map, row, col, rows, cols);
	// Check for holes in the first row
	/*
	while (map[i][j] && ft_isspace(map[i][j]))
		j ++;
	while (map[i][j] && map[i][j] == '1')
		j ++;
	if (map[i][j] && (map[i][j] == '0' || ft_isspace(map[i][j])))
	{
		print_err("First row has a hole");
		return (1);
	}*/
	/* Check whether the map only has 
		leading and trailing spaces in lines, 
		1, 0 and one of N, S, E, W
	*/
	/*
		Find the location of N,S,E or W and check it is enclosed by 1's
	*/
	/*
		Check the entire map's 0's are enclosed by 1's
	*/
	
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
