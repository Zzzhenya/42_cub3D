/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:36:56 by ohladkov          #+#    #+#             */
/*   Updated: 2023/06/01 17:05:52 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*cur;
	t_list	*temp;
	t_list	*new_list;

	if (lst == NULL)
		return (NULL);
	temp = (*f)(lst->content);
	new_list = ft_lstnew(temp);
	if (!new_list)
		return (NULL);
	cur = new_list;
	while (lst->next != NULL && cur != NULL)
	{
		lst = lst->next;
		temp = (*f)(lst->content);
		cur->next = ft_lstnew(temp);
		cur = cur->next;
	}
	if (cur == NULL)
		ft_lstclear(&new_list, del);
	return (new_list);
}
