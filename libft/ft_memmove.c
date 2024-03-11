/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:19:33 by jijeong           #+#    #+#             */
/*   Updated: 2022/04/23 15:26:42 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;

	if (dst == src)
		return (dst);
	if (dst > src && dst < src + len)
	{
		i = len;
		while (0 < i)
		{
			*((unsigned char *)dst + i - 1) = *((unsigned char *)src + i - 1);
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < len)
		{
			*((unsigned char *)dst + i) = *((unsigned char *)src + i);
			i++;
		}
	}
	return (dst);
}
