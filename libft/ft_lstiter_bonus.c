/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:17:59 by jijeong           #+#    #+#             */
/*   Updated: 2022/04/05 13:19:26 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*cnode;

	if (lst == (void *)0 || f == (void *)0)
		return ;
	cnode = lst;
	while (cnode != (void *)0)
	{
		f(cnode->content);
		cnode = cnode->next;
	}
}
