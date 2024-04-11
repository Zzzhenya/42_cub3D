/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:18:22 by ohladkov          #+#    #+#             */
/*   Updated: 2023/05/28 11:14:05 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t			len;
	unsigned int	i;	

	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		(*f)(i, s + i);
		i++;
	}
}
/*
int	main()
{
	char b[] = "override this !";
 	char b2[0xF0];
 	size_t size = strlen(b);

 	for (size_t i = 0; i < size; i++)
 		ft_striteri(i, b2 + i);
 	b2[size] = 0;
 	ft_striteri(b, f_striteri);
 	if (!strcmp(b, b2))
 		printf("OK");
	printf("KO");
}*/
