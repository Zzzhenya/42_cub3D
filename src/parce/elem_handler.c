/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:11:21 by ohladkov          #+#    #+#             */
/*   Updated: 2024/06/07 21:57:42 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	fill_struct_elem(t_data *data, char **s)
{
	if (ft_strncmp(*s, "NO", 2) == 0)
		return (copy_texture(data->elem, s, &data->elem->no));
	else if (ft_strncmp(*s, "WE", 2) == 0)
		return (copy_texture(data->elem, s, &data->elem->we));
	else if (ft_strncmp(*s, "SO", 2) == 0)
		return (copy_texture(data->elem, s, &data->elem->so));
	else if (ft_strncmp(*s, "EA", 2) == 0)
		return (copy_texture(data->elem, s, &data->elem->ea));
	else if (ft_strncmp(*s, "C", 1) == 0)
		return (copy_c_color(data->elem, s));
	else if (ft_strncmp(*s, "F", 1) == 0)
		return (copy_f_color(data->elem, s));
	else
		return (print_err("Invalid identifier"));
}

int	copy_texture(t_elem *elem, char **s, char **texture)
{
	char	*set;

	(void)elem;
	if (*texture)
		return (print_err("Duplicate texture detected"));
	set = " \t\n\r\f\v";
	*texture = ft_strtrim(*s + 2, set);
	if (check_filename(*texture, ".xpm") != 0)
		return (1);
	return (0);
}

int	copy_c_color(t_elem *elem, char **s)
{
	char	*tmp;
	char	**arr;
	int		j;

	*s = *s + 1;
	if (elem->rgb_c[0] != -1)
		return (print_err("Duplicate ceiling color detected"));
	if (count_elem(*s, ',') != 2)
		return (print_err("Invalid color"));
	arr = ft_split(*s, ',');
	j = -1;
	while (++j < 3 && arr[j])
	{
		tmp = ft_strtrim(arr[j], " \t\n\r\f\v");
		if (!tmp)
			return (ft_free_arr(arr), print_err("Invalid color"));
		if (!ft_isdigit_str(tmp))
			return (free(tmp), ft_free_arr(arr), print_err("Invalid color"));
		elem->rgb_c[j] = ft_atoi(tmp);
		free(tmp);
		if (elem->rgb_c[j] < 0 || elem->rgb_c[j] > 255)
			return (ft_free_arr(arr), print_err("Invalid color"));
	}
	return (ft_free_arr(arr), 0);
}

int	copy_f_color(t_elem *elem, char **s)
{
	char	*tmp;
	char	**arr;
	int		j;

	*s = *s + 1;
	if (elem->rgb_f[0] != -1)
		return (print_err("Duplicate ceiling color detected"));
	if (count_elem(*s, ',') != 2)
		return (print_err("Invalid color"));
	arr = ft_split(*s, ',');
	j = -1;
	while (++j < 3 && arr[j])
	{
		tmp = ft_strtrim(arr[j], " \t\n\r\f\v");
		if (!tmp)
			return (ft_free_arr(arr), print_err("Invalid color"));
		if (!ft_isdigit_str(tmp))
			return (free(tmp), ft_free_arr(arr), print_err("Invalid color"));
		elem->rgb_f[j] = ft_atoi(tmp);
		ft_free(&tmp);
		if (elem->rgb_f[j] < 0 || elem->rgb_f[j] > 255)
			return (ft_free_arr(arr), print_err("Invalid color"));
	}
	ft_free_arr(arr);
	return (0);
}
