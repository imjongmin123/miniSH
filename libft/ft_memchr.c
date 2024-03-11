/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:18:41 by jijeong           #+#    #+#             */
/*   Updated: 2022/04/09 15:18:58 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t count)
{
	size_t			i;

	i = 0;
	while (i < count)
	{
		if (*((unsigned char *)s + i) == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	return (0);
}
