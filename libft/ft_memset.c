/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:09:48 by ohladkov          #+#    #+#             */
/*   Updated: 2023/05/28 11:13:39 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char			*p;
	unsigned char	ch;
	size_t			i;

	p = s;
	ch = c;
	i = 0;
	while (i < n)
	{
		p[i] = ch;
		i++;
	}
	return (p);
}
/*
int	main()
{
//	char	str[10] = "hello 1234";
//	ft_memset(str, '*', 7);
//	memset(str, '*', 7);	
//	write(1, str, 10);

	int	arr[10];

//	memset(arr, 0, sizeof(arr));
	ft_memset(arr, 0, sizeof(arr));
	for (int i = 0; i < 10; i++)
		printf("%d ", arr[i]);
	return (0);
}*/
