/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:20:20 by ohladkov          #+#    #+#             */
/*   Updated: 2023/05/31 18:23:52 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0)
	{
		while ((src[i] != '\0') && (i < (size - 1)))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}
/*
#include <bsd/string.h>
int	main(void)
{
	char	dst[10];
	char	src[5] = "12345";
	size_t	res;

	res = strlcpy(dst, src, 0);
//	strlcpy(dst, src, 0);
	printf("%zu\n", res);
	write(1, dst, 5);
}*/
