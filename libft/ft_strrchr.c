/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:29:51 by ohladkov          #+#    #+#             */
/*   Updated: 2023/05/14 10:32:07 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char) c)
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}
/*
int	main()
{
	char *src = "there is so \0ma\0ny \0 \\0 in t\0his stri\0ng !\0\0\0\0";
 	char *d1 = strrchr(src, '\0');
 	char *d2 = ft_strrchr(src, '\0');

 	if (d1 == d2)
 		printf("OK");
	else
 		printf("KO");


//	char	*str = "One two thee";
//	char 	*res = strrchr(str, 't');
//
//	if (str)
//		printf("Found:%s", res);
//	else
//		printf("Not found");

	return (0);
}*/
