/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:13:23 by ohladkov          #+#    #+#             */
/*   Updated: 2023/05/26 16:11:25 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cur;
	t_list	*temp;

	if (lst == NULL || del == NULL)
		return ;
	cur = *lst;
	while (cur != NULL)
	{
		temp = cur->next;
		(*del)(cur->content);
		free(cur);
		cur = temp;
	}
	*lst = NULL;
}
