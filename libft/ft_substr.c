/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 12:22:41 by ohladkov          #+#    #+#             */
/*   Updated: 2023/05/31 18:36:45 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	len_s;
	size_t	i;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (len >= len_s && start < len_s)
		len = len_s - start;
	if (start >= len_s)
		len = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	if (start < len_s)
	{
		while (s[start + i] != '\0' && i < len)
		{
			str[i] = (char)s[start + i];
			i++;
		}
	}
	str[i] = '\0';
	return (str);
}
/*
int main()
{
	const char	*s = "My string";
	unsigned int	i = 5;
	char	*res;
	res = ft_substr(s, i, 4);
	printf("%s", res);
	return (0);
}*/
