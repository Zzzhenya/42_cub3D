/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:21:17 by ohladkov          #+#    #+#             */
/*   Updated: 2023/05/12 20:01:21 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*str;

	str = (char *)s;
	while (n > 0)
	{
		*str = '\0';
		str++;
		n--;
	}
}
/*
int	main(void)
{
	char	str[20] = "Oneee two";
	
//	bzero((str + 3), 3);
	ft_bzero(str + 3, 3);
	printf("%s", str);
	return (0);
}*/
