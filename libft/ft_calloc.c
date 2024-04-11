/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:32:19 by ohladkov          #+#    #+#             */
/*   Updated: 2023/05/13 15:21:25 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*p;

	p = (void *)malloc(nitems * size);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, (nitems * size));
	return (p);
}
/*
int	main()
{
	char	*str;
	str = (char *)calloc(30, 0);
	if (!str)
	    	printf("%s", "NULL");
//        	write(1, "NULL", 4);
    	else
	    	printf("%s", "OK");
//        	write(1, str, 30);

	return (0);
}*/
