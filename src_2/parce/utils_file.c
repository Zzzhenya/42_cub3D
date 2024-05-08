/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:11:34 by ohladkov          #+#    #+#             */
/*   Updated: 2024/04/21 15:49:42 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_2.h"

// return 0 to indicate valid filename and successful open, otherwise non-zero value
int	check_filename(char *str, char *extention)
{
	char	*name;
	int		i;
	int		fd;

	// // for case ./path_to_texture.xpm ??
	// if (ft_strncmp(extention, ".xpm", 4) == 0)
	// {
	// 	if (ft_strchr(str, '.') == ft_strrchr(str, '.'))
	// 		return (print_error("Invalid file name or extantion"));
	// }
	name = ft_strrchr(str, '.');
	if (name)
		i = ft_strlen(str) - ft_strlen(name);
	else
		return (print_error("Invalid file name or extantion"));
	fd = open(str, O_WRONLY);
	if (fd == -1 || i <= 0 || ft_strncmp(str + i, extention, i) != 0)
	{
		if (fd != -1)
			close(fd);
		return (print_error("Invalid file name or extantion"));
	}
	close(fd);
	return (0);
}

// return amount n-lines in a file
int	file_line(char *file, t_data *data)
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
		return (print_error("Invalid information about textures and colors"), -1);
	return (0);
}

