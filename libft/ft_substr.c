/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:23:59 by jijeong           #+#    #+#             */
/*   Updated: 2022/04/18 13:54:01 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	l;

	l = 0;
	while (*(s + l))
		l++;
	if (l <= (size_t)start)
		len = 0;
	if (l - (size_t)start + 1 < len)
		len = l - (size_t)start + 1;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return ((void *)0);
	i = 0;
	while (i < len && *(s + (size_t)start + i))
	{
		*(str + i) = *(s + (size_t)start + i);
		i++;
	}
	*(str + i) = 0;
	return (str);
}
