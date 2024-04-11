/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:12:19 by ohladkov          #+#    #+#             */
/*   Updated: 2024/04/07 18:08:56 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	init_data(t_map_utils *data);
static char	*get_row(int i, char **map, int row, char c);
// static int	get_row_len(char *str);
static int	chech_elems(t_map_utils *data, int rows);

int	validate_map(char **map, int rows)
{
	t_map_utils	data;

	init_data(&data);
	while (data.row < rows)
	{
		data.cur_row = map[data.row];
		data.row_on_top = get_row((data.row > 0), map, data.row, '-');
		data.row_on_btm = get_row((data.row < rows - 1), map, data.row, '+');
		while (*data.cur_row == ' ')
			data.cur_row++;
		data.cur_row_len = ft_strlen(data.cur_row) - 1;
		data.top_row_len = ft_strlen(data.row_on_top);
		data.btm_row_len = ft_strlen(data.row_on_btm);
		while (data.col < data.cur_row_len) // data.col < data.cur_row_len
		{
			// printf("cur_row_len = %i\n", data.cur_row_len);
			data.cur_char = data.cur_row[data.col];
			int n = chech_elems(&data, rows);
			if (n != 0)
				return (n);
			data.col++;
		}
		data.row++;
	}
	return (0);
}

static void	init_data(t_map_utils *data)
{
	data->row = 0;
	data->col = 0;
	data->cur_char = 0;
	data->cur_row = NULL;
	data->row_on_top = NULL;
	data->row_on_btm = NULL;
	data->cur_row_len = 0;
	data->top_row_len = 0;
	data->btm_row_len = 0;
}

static char	*get_row(int i, char **map, int row, char c)
{
	if (i)
	{
		if (c == '-')
			return (map[row - 1]);
		else if (c == '+')
			return (map[row + 1]);
	}
	return (NULL);
}

// static int	get_row_len(char *str)
// {
// 	if (str)
// 		return (ft_strlen(str));
// 	else
// 		return (0);
// }

static int	chech_elems(t_map_utils *data, int rows)
{
	if (data->cur_char == ' ')
		return (0);
	if (data->row == 0 || data->row == rows - 1)
		if (data->cur_char != '1' && data->cur_char != ' ')
		{
			// printf("data->row: %i, rows - 1: %i, data->cur_char : %c\n", data->row, rows - 1, data->cur_char);
			return (2);
		}
	if (data->col == 0 || data->col == data->cur_row_len)//- 1
		if (data->cur_char != '1')
			return (3);
	if ((data->col > 0 && data->cur_row[data->col - 1] != '1' && !ft_strchr("SNEW", data->cur_row[data->col - 1])) || 
		(data->col < data->cur_row_len - 1 && data->cur_row[data->col + 1] != '1' && !ft_strchr("SNEW", data->cur_row[data->col + 1])))
		return (4);
	if (data->col >= data->top_row_len && data->cur_char != '1')
		return (5);
	if (data->col >= data->btm_row_len && data->cur_char != '1')
		return (6);
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
