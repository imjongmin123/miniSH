/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:17:33 by jijeong           #+#    #+#             */
/*   Updated: 2022/04/11 09:36:59 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (del == (void *)0 || lst == (void *)0)
		return ;
	while (*lst != (void *)0)
	{
		if ((*lst)->next)
		{
			tmp = (*lst)->next;
			del((*lst)->content);
			free(*lst);
			*lst = tmp;
		}
		else
		{
			del((*lst)->content);
			free(*lst);
			*lst = (void *)0;
		}
	}
}
