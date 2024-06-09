/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:11:34 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/02 20:54:32 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/**
 * return 0 to indicate valid filename and was successful opened, 
 * otherwise non-zero value
 * */
int	check_filename(char *str, char *extention)
{
	char	*name;
	int		i;
	int		fd;

	name = ft_strrchr(str, '.');
	if (name)
		i = ft_strlen(str) - ft_strlen(name);
	else
		return (print_err("Invalid file name or extantion"));
	fd = open(str, O_WRONLY);
	if (fd == -1 || i <= 0 || ft_strncmp(str + i, extention, i) != 0)
	{
		if (fd != -1)
			close(fd);
		return (print_err("Invalid file name or extantion"));
	}
	close(fd);
	return (0);
}

// return amount n-lines in a file
int	count_file_lines(char *file, t_data *data)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	(void)file;
	str = get_next_line(data->fd);
	tmp = NULL;
	while (str)
	{
		++i;
		tmp = str;
		free(tmp);
		str = get_next_line(data->fd);
	}
	free(str);
	str = NULL;
	return (i);
}

int	validate_elem(t_elem *elem)
{
	int	i;

	i = 0;
	if (elem->ea != NULL)
		i++;
	if (elem->we != NULL)
		i++;
	if (elem->no != NULL)
		i++;
	if (elem->so != NULL)
		i++;
	if (elem->rgb_c[0] != -1 && elem->rgb_c[1] != -1 && elem->rgb_c[2] != -1)
		i += 3;
	if (elem->rgb_f[0] != -1 && elem->rgb_f[1] != -1 && elem->rgb_f[2] != -1)
		i += 3;
	if (i != 10)
		return (print_err("Missing information about textures and colors"), 1);
	return (0);
}

int	get_max_strlen(char **map, int rows)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (j < rows && map[j])
	{
		len = ft_strlen(map[j]);
		if (len > i)
			i = len;
		j++;
	}
	return (i);
}
