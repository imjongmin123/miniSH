/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:16:19 by jijeong           #+#    #+#             */
/*   Updated: 2022/04/05 11:22:13 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (new == (void *)0 || lst == (void *)0)
		return ;
	if (*lst == (void *)0)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != (void *)0)
		current = current->next;
	current->next = new;
}
