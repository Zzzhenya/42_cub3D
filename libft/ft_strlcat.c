/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:03:51 by ohladkov          #+#    #+#             */
/*   Updated: 2023/05/13 10:49:28 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	d;
	size_t	len_d;
	size_t	len_s;

	len_d = ft_strlen(dst);
	len_s = ft_strlen(src);
	if (!dst && size == 0)
		return (len_s);
	if (size <= len_d)
		return (len_s + size);
	i = 0;
	d = len_d;
	while ((src[i] != '\0') && d + 1 < size)
	{
		dst[d] = src[i];
		i++;
		d++;
	}
	dst[d] = '\0';
	return (len_d + len_s);
}
/*
#include <bsd/string.h>
int	main(void)
{
	char	dst[0] = '\0';
	char	src[15] = "lorem nc";

//	printf("%zu\n", ft_strlcat(dst, src, 2));

	printf("%zu", strlcat(dst, src, 15));
}*/
