/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:14:14 by ohladkov          #+#    #+#             */
/*   Updated: 2023/05/27 10:32:42 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*cur;

	if (!lst || !f)
		return ;
	cur = lst;
	while (cur)
	{
		(*f)(cur->content);
		cur = cur->next;
	}
}
/*
void	f(void *first_cur)
{
	((char *)first_cur)[0] = 'W';
}

int	main()
{
	t_list	*lst;
	t_list	*lst1;
	char	*a1;
	int	size_of_lst = 2;

	a1 = malloc(sizeof(char) * 6);
	ft_strlcpy(a1, "word1", 6);
	lst = ft_lstnew(a1);

	lst1 = lst;
	while (size_of_lst < 12)
	{
		a1 = malloc(sizeof(char) * 6);
		ft_strlcpy(a1, "word1", 6);
		a1[4] = (size_of_lst % 10) + 48;
		lst->next = ft_lstnew(a1);
		lst = lst->next;
		size_of_lst++;
	}
	ft_lstiter(lst1, f);
	while (lst1)
	{
		printf("%s\n", (char *)lst1->content);
		lst1 = lst1->next;
	}
	return (0);
}*/
