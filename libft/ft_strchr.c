/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:29:13 by ohladkov          #+#    #+#             */
/*   Updated: 2023/05/28 11:19:24 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while ((char)c != *s)
	{
		if (!*s)
			return (0);
		s++;
	}
	return ((char *)s);
}
/*
int	main()
{
	char *src = "there is so \0ma\0ny \0 \\0 in t\0his stri\0ng !\0\0\0\0";
 	char *d1 = strchr(src, '\0');
 	char *d2 = ft_strchr(src, '\0');

 	if (d1 == d2)
 		printf("OK");
	else
		printf("KO");

//	const char *str = "One two three";
//	char *ptr = ft_strchr(str, 't');

//	if (ptr)
//		printf("Found:%s\n", ptr);
//	else
//		printf("Not found:\n");

	return (0);
}*/
