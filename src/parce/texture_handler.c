/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:11:21 by ohladkov          #+#    #+#             */
/*   Updated: 2024/04/07 18:08:35 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	fill_struct_elem(t_data *data, char **s)
{
	if (ft_strncmp(*s, "NO", 2) == 0)
		return (copy_texture(data, s, &data->elem->no));
	else if (ft_strncmp(*s, "WE", 2) == 0)
		return (copy_texture(data, s, &data->elem->we));
	else if (ft_strncmp(*s, "SO", 2) == 0)
		return (copy_texture(data, s, &data->elem->so));
	else if (ft_strncmp(*s, "EA", 2) == 0)
		return (copy_texture(data, s, &data->elem->ea));
	else if (ft_strncmp(*s, "C", 1) == 0)
		return (copy_c_color(data, s));
	else if (ft_strncmp(*s, "F", 1) == 0)
		return (copy_f_color(data, s));
	else
		return (print_error("Invalid identifier"));
}

int	copy_texture(t_data *data, char **s, char **texture)
{
	char *set;

	(void)data;
	if (*texture)
		return (print_error("Duplicate texture detected"));
	set = " \t\n\r\f\v";
	*texture = ft_strtrim(*s + 2, set);
	// printf("%s\n", *texture); // rm
	if (check_filename(*texture, ".xpm") != 0)
		return (1);
	return (0);
}

int	copy_c_color(t_data *data, char **s)
{
	char	*tmp;
	char	**arr;
	int		j;

	*s = *s + 1;
	if (data->elem->rgb_c[0] != -1)
		return (print_error("Duplicate ceiling color detected"));
	if (count_elem(*s, ',') != 2)
		return (print_error("Invalid color's information"));
	arr = ft_split(*s, ',');
	j = -1;
	while (++j < 3)
	{
		tmp = ft_strtrim(arr[j], " \t\n\r\f\v");
		if (!tmp)
			return (ft_free_arr(arr), print_error("Invalid color's information"));
		data->elem->rgb_c[j] = ft_atoi(tmp);
		// printf("%i\n", data->elem->rgb_c[j]); // rm
		free(tmp);
		if (data->elem->rgb_c[j] < 0 || data->elem->rgb_c[j] > 255)
			return (ft_free_arr(arr), print_error("Invalid color's information"));
	}
	ft_free_arr(arr);
	return (0);
}

int	copy_f_color(t_data *data, char **s)
{
	char	*tmp;
	char	**arr;
	int		j;

	*s = *s + 1;
	if (data->elem->rgb_f[0] != -1)
		return (print_error("Duplicate ceiling color detected"));
	if (count_elem(*s, ',') != 2)
		return (print_error("Invalid color's information"));
	arr = ft_split(*s, ',');
	j = -1;
	while (++j < 3)
	{
		tmp = ft_strtrim(arr[j], " \t\n\r\f\v");
		if (!tmp)
			return (ft_free_arr(arr), print_error("Invalid color's information"));
		data->elem->rgb_f[j] = ft_atoi(tmp);
		// printf("%i\n", data->elem->rgb_f[j]); // rm
		free(tmp);
		if (data->elem->rgb_f[j] < 0 || data->elem->rgb_f[j] > 255)
			return (ft_free_arr(arr), print_error("Invalid color's information"));
	}
	ft_free_arr(arr);
	return (0);
}
