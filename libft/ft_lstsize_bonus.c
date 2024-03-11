/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:18:24 by jijeong           #+#    #+#             */
/*   Updated: 2022/04/04 12:41:29 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	l;

	if (!lst)
		return (0);
	if (!lst->next)
		return (1);
	l = 1;
	while (!(lst->next == 0))
	{
		lst = lst->next;
		l++;
	}
	return (l);
}
