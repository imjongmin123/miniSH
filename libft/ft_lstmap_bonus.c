/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:18:17 by jijeong           #+#    #+#             */
/*   Updated: 2022/04/11 10:59:45 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*tmp;
	t_list	*bef;

	if (lst == (void *)0 || f == (void *)0)
		return ((void *)0);
	head = ft_lstnew(f(lst->content));
	bef = head;
	lst = lst->next;
	while (lst != (void *)0)
	{
		tmp = ft_lstnew(f(lst->content));
		if (tmp == (void *)0)
		{
			ft_lstclear(&head, del);
			return ((void *)0);
		}
		bef->next = tmp;
		bef = tmp;
		lst = lst->next;
	}
	return (head);
}
