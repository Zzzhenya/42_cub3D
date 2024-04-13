/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_player.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:12:23 by ohladkov          #+#    #+#             */
/*   Updated: 2024/04/12 19:51:37 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// function set a players's positon && point of view && check if only one player
int validate_player(t_data *data, char **map, int rows)
{
	int	row;
	int	col;

	if (!*map || !map || rows == 0)
		return (print_error("Missing a game map"));
	row = 0;
	while (row < rows)
	{
		col = 0;
		while (map[row][col] != '\0')
		{
			if (ft_strchr("SNEW", map[row][col]))
			{
				if (data->map->view == 0)
					data->map->view = map[row][col];
				else
					return (print_error("Multiple players"));
				// data->map->px = col + 1;
				// data->map->py = row + 1; // ch
				data->map->px = col;
				data->map->py = row;
			}
			col++;
		}
		row++;
	}
	if (data->map->view == 0)
		return (print_error("Missing a player"));
	return (0);
}
