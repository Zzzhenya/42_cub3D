/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:47:37 by ohladkov          #+#    #+#             */
/*   Updated: 2023/05/28 11:16:01 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;
	size_t			i;

	i = -1;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (s < d)
	{
		while (n-- > 0)
			d[n] = s[n];
	}
	else
	{
		while (++i < n)
			d[i] = s[i];
	}
	return (d);
}
/*
int	main()
{
	char	dest[] = "oldstring";
	const char src[] = "newstring";
	
	printf("Before memmove dest = %s\n, src = %s\n", dest, src);
//	ft_memmove(dest, src, 9);
	memmove(dest, src, 9);
	printf("After: dest = %s\n, src = %s\n", dest, src);
	return (0);
}*/
