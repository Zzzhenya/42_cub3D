/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:11:03 by ohladkov          #+#    #+#             */
/*   Updated: 2024/05/26 11:36:32 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// allocate memory for 2D array in struct t_map
int	read_file(char *file, t_data *data)
{
	data->fd = open(file, O_RDONLY);
	if (data->fd == -1)
		return (perror("Error opening file"), 1);
	data->lines = file_line(file, data);
	close (data->fd);
	data->fd = -1;
	if (data->lines == 0)
		return (print_error("File is empty"), 3);
	else
	{
		data->arr_file = (char **)ft_calloc(data->lines + 1, sizeof(char *));
		if (!data->arr_file)
			return (print_error(NULL), perror("Malloc"), 1);
	}
	return (0);
}

int	game_map_dup(t_data *data, char **arr)
{
	int	i;
	int	j;

	i = 1;
	while (arr[i + data->offset])
	{
		if (!is_whitespace_str(arr[i + data->offset]))
			break ;
		i++;
	}
	j = 0;
	data->map->map = (char **)ft_calloc(data->lines - (i + data->offset - 1) \
	+ 1, sizeof(char *));
	if (!data->map->map)
		return (print_error(NULL), perror("Malloc"), 1);
	while (arr[i + data->offset + j])
	{
		if (is_whitespace_str(arr[i + data->offset + j]) && arr[i + data->offset + j + 1]\
		 && !is_whitespace_str(arr[i + data->offset + j + 1]))
			return (print_error("Map include empty lines"), 4);
		if (!is_whitespace_str(arr[i + data->offset + j]))
			data->map->map[j] = ft_strdup(arr[i + data->offset + j]);
		j++;
	}
	return (0);
}

int	validate_file_content(char *file, t_data *data)
{
	if (copy_file(file, data) != 0)
		return (print_error("Invalid file"));
	if (parce_file(data) != 0)
		return (2);
	if (game_map_dup(data, data->arr_file) != 0)
		return (3);
	data->rows = ft_arrsize(data->map->map);
	if (validate_player(data, data->map->map, data->rows) != 0)
		return (1);
	int i = validate_map(data->map->map, data->rows);
	if (i != 0)
		return (print_error("Invalid map"), printf("%i\n", i), 2);
	return (0);
}

// read from file and set an 2D array into an arr_file
int	copy_file(char *file, t_data *data)
{
	char	*str;
	char	*tmp;
	int		i;
	size_t	len;

	i = 0;
	data->fd = open(file, O_RDONLY);
	while (1)
	{
		str = get_next_line(data->fd);
		if (!str)
			break ;
		len = ft_strlen(str);
		if (len)
			str[len] = '\0';
		data->arr_file[i] = ft_strdup(str);
		data->arr_file[i][len - 1] = '\0'; // added
		i++;
		tmp = str;
		ft_free(&str);
	}
	ft_free(&str);
	data->arr_file[i] = NULL;
	close(data->fd);
	data->fd = -1;
	return (0);
}

// coping only texture and color + validating if struct elem is filled
int	parce_file(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = 6;
	while (data->arr_file[++i])
	{
		if (!is_whitespace_str(data->arr_file[i]))
		{
			j--;
			if (copy_data(data, data->arr_file[i]) != 0)
				return (1);
		}
		if (j == 0)
		{
			data->offset = i;
			return (validate_elem(data->elem));
		}
	}
	return (0);
}

// copy valid data from file to struct elem (textures and colors)
int	copy_data(t_data *data, char *s)
{
	char	*tmp;

	tmp = s;
	while (*s != '\0')
	{
		while (is_whitespace(*s))
			s++;
		if (strchr("WNSECF", *s) == NULL)
			return (print_error("Invalid type of elements"));
		if (fill_struct_elem(data, &s) != 0)
			return (1);
		s += ft_strlen(s);
	}
	return (0);
}
