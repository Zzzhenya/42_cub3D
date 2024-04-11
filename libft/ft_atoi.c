/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 10:51:38 by ohladkov          #+#    #+#             */
/*   Updated: 2023/05/31 19:17:04 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		sign;
	size_t	total;

	sign = 1;
	total = 0;
	while (*str != '\0' && (*str == 32 || (*str >= 9 && *str <= 13)))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		total *= 10;
		total += (*str - '0');
		str++;
	}
	return (total * sign);
}
/*
int	main()
{
//	char	str[10] = "++-+-+5364 nkjkd";
	
	printf("%d", ft_atoi("\001 2"));
	return (0);
}*/
