/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 10:54:46 by ohladkov          #+#    #+#             */
/*   Updated: 2023/05/22 19:40:12 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	if (n == 0)
		return (0);
	while (n - 1 > 0 && (*s1 == *s2))
	{
		s1++;
		s2++;
		n--;
	}
	return ((int)(*s1 - *s2));
}
/*
int main () {
   char str1[15];
   char str2[15];
   int ret;

   memcpy(str1, "abcdef", 3);
   memcpy(str2, "abccEF", 3);

   ret = ft_memcmp(str1, str2, 3);
   printf("%i\n", ret);
   if(ret > 0) {
      printf("str2 is less than str1");
   } else if(ret < 0) {
      printf("str1 is less than str2");
   } else {
      printf("str1 is equal to str2");
   }

   return(0);
}*/
