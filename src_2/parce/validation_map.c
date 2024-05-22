/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:12:19 by ohladkov          #+#    #+#             */
/*   Updated: 2024/05/22 18:41:16 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_2.h"

int	validate_map(char **map, int rows)
{
	print_arr(map);
	printf("rows: %i\n", rows);
	exit(0);
	// t_map_utils t;
	// t.col = 0;
	// t.row = 0;

	// while (t.row < rows)
	// {
	// 	while (map[t.row][t.col])
	// 	{
	// 		while (map[t.row][t.col] == ' ')
	// 			t.col++;
			
	// 		t.col++;
	// 	}

	// 	t.row++;
	// }

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
