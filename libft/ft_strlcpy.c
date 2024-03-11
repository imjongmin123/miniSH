/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:22:30 by jijeong           #+#    #+#             */
/*   Updated: 2022/03/29 15:31:33 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	l;
	size_t	i;

	l = 0;
	while (*(src + l))
		l++;
	if (!dstsize)
		return (l);
	i = 0;
	while (i <= l && i < dstsize)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	*(dst + dstsize - 1) = 0;
	return (l);
}
