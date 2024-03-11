/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:22:23 by jijeong           #+#    #+#             */
/*   Updated: 2022/04/16 23:24:44 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_l;
	size_t	src_l;
	size_t	i;

	dst_l = 0;
	while (*(dst + dst_l) && dst_l < size)
		dst_l++;
	src_l = 0;
	while (*(src + src_l))
		src_l++;
	if (size == 0)
		return (src_l);
	i = 0;
	while (i < src_l && dst_l + i < size - 1)
	{
		*(dst + dst_l + i) = *(src + i);
		i++;
	}
	if (i != 0)
		*(dst + dst_l + i) = 0;
	if (size <= dst_l)
		return (src_l + size);
	return (dst_l + src_l);
}
