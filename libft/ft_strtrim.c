/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 13:37:41 by ohladkov          #+#    #+#             */
/*   Updated: 2023/05/21 18:02:46 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checkset(char const *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end;

	start = 0;
	end = ft_strlen(s1) - 1;
	if (!set || !s1)
		return (0);
	while (ft_checkset(set, s1[start]))
		start++;
	if (!s1[start])
		return (ft_calloc(1, 1));
	while (ft_checkset(set, s1[end]))
		end--;
	return (ft_substr(s1, start, end - start + 1));
}
/*
int	main()
{
	char	*s1 = "   ";
	char	*set = " ";
	printf("%s", ft_strtrim(s1, set));
	return (0);
}*/
