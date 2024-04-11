/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 20:11:34 by ohladkov          #+#    #+#             */
/*   Updated: 2023/05/28 14:06:22 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*cur;

	if (!lst)
		return (NULL);
	cur = lst;
	while (cur->next != NULL)
		cur = cur->next;
	return (cur);
}
/*
int main()
{
	t_list	*node1 = malloc(sizeof(t_list));
	t_list	*node2 = malloc(sizeof(t_list));
	t_list	*node3 = malloc(sizeof(t_list));

	node1->content = 1;	
	node2->content = 2;	
	node3->content = 3;	

	node1->next = node2;
	node2->next = node3;
	node3->next = NULL;

	//get the last node
	t_list *lastN = ft_lstlast(node1);

	if (lastN != NULL)
		printf("%d", lastN->content);
	else
		write(1, "\n", 1);
	
	free(node1);
	free(node2);
	free(node3);
	return (0);
}*/
