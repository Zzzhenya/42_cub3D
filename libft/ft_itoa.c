/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 12:52:27 by ohladkov          #+#    #+#             */
/*   Updated: 2023/05/31 17:46:38 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	ft_putnum(int n, char *str, int len)
{
	int	temp;
	int	rem;

	temp = n;
	str[len] = '\0';
	len = len - 1;
	while (len > 0)
	{
		rem = temp % 10;
		temp = temp / 10;
		if (n < 0)
			rem = rem * -1;
		rem = rem + 48;
		str[len] = rem;
		len--;
	}
	if (n < 0)
		str[len] = '-';
	else
	{
		rem = temp % 10;
		rem = rem + 48;
		str[len] = rem;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = ft_len(n);
	if (n < 0)
		len = len + 1;
	str = (char *)malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);
	ft_putnum(n, str, len);
	return (str);
}
