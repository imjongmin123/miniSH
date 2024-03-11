/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:23:06 by jijeong           #+#    #+#             */
/*   Updated: 2022/03/21 17:05:48 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*ch;

	i = 0;
	ch = 0;
	while (*(s + i))
	{
		if ((unsigned char)*(s + i) == (unsigned char)c)
			ch = (char *)s + i;
		i++;
	}
	if ((unsigned char)*(s + i) == (unsigned char)c)
		ch = (char *)s + i;
	return (ch);
}
