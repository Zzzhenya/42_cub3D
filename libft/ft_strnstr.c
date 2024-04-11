/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:47:59 by ohladkov          #+#    #+#             */
/*   Updated: 2023/05/23 17:04:26 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!str && !len)
		return (NULL);
	if (little[0] == '\0' || little == str)
		return ((char *) str);
	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while ((str[i + j] == little[j]) && ((i + j) < len))
		{
			if (little[j + 1] == '\0')
				return ((char *)&str[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
/*
#include <bsd/string.h>
int	main(void)
{
	char	str[10] = "the string";
	char	little[10] = "stri";
	char	*result;

	result = ft_strnstr(str, little, 22);
//	result = strnstr(str, little, 1);
//	write(1, result, 5);
//	printf("%s", strnstr(str, little, 1));
	printf("%s", result);
}*/
