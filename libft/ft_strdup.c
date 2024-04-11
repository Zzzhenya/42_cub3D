/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 13:13:23 by ohladkov          #+#    #+#             */
/*   Updated: 2023/05/13 14:09:45 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*s;
	size_t	len;

	len = ft_strlen(src);
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (s == NULL)
		return (0);
	ft_memcpy(s, src, len);
	s[len] = '\0';
	return (s);
}
/*
int main()
{
	char *str;
 	char *tmp = "I malloc so I am.";

 	str = ft_strdup(tmp);
 	if (strcmp(str, tmp))
 		printf("%s", "OK");
 	free(str);

//	printf("%s", strdup("salm"));
	return (0);
}*/
