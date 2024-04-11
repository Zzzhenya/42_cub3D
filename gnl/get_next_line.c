/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:48:58 by ohladkov          #+#    #+#             */
/*   Updated: 2024/03/31 10:47:48 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_buf(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

char	*set_line(char *line_buffer)
{
	char			*rem;
	size_t			len;
	unsigned int	i;

	i = 0;
	if (line_buffer == NULL)
		return (NULL);
	while (line_buffer[i] != '\0' && line_buffer[i] != '\n')
		i++;
	if (line_buffer[i] == '\0')
		return (NULL);
	len = ft_strln(line_buffer);
	rem = ft_substring(line_buffer, i + 1, len - i);
	if (*rem == '\0')
		free_buf(&rem);
	line_buffer[i + 1] = '\0';
	return (rem);
}

char	*fill_line_buffer(int fd, char *line, char *buffer)
{
	ssize_t	bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free_buf(&buffer);
			free_buf(&line);
			return (NULL);
		}
		if (bytes_read == 0)
			return (line);
		buffer[bytes_read] = '\0';
		if (!line)
			line = ft_strdupl("");
		temp = line;
		line = ft_strjn(temp, buffer);
		free_buf(&temp);
		if (ft_strchar(buffer, '\n'))
			break ;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*rem;
	char		*buffer;
	char		*line_buf;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		free_buf(&rem);
		return (NULL);
	}
	buffer = (char *)(malloc(sizeof(char) * (100 + 1)));
	if (!buffer)
	{
		free_buf(&rem);
		return (NULL);
	}
	line_buf = fill_line_buffer(fd, rem, buffer);
	free_buf(&buffer);
	if (!line_buf || *line_buf == '\0')
	{
		free(line_buf);
		return (NULL);
	}
	rem = set_line(line_buf);
	return (line_buf);
}
