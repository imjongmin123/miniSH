/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:23:13 by jijeong           #+#    #+#             */
/*   Updated: 2022/04/18 13:29:29 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*(needle) || haystack == needle)
		return ((char *)haystack);
	while (*(haystack + i) && i < len)
	{
		if (*(haystack + i) == *(needle))
		{
			j = 0;
			while (*(needle + j) && *(haystack + i + j) == *(needle + j))
				j++;
			if (!*(needle + j) && i + j <= len)
				return ((char *)haystack + i);
		}
		i++;
	}
	return (0);
}
