/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:22:19 by jijeong           #+#    #+#             */
/*   Updated: 2022/03/29 15:23:25 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_l;
	size_t	s2_l;
	size_t	i;

	s1_l = ft_strlen(s1);
	s2_l = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (s1_l + s2_l + 1));
	if (!str)
		return ((void *)0);
	i = 0;
	while (i < s1_l)
	{
		*(str + i) = *(s1 + i);
		i++;
	}
	i = 0;
	while (i < s2_l)
	{
		*(str + s1_l + i) = *(s2 + i);
		i++;
	}
	*(str + s1_l + s2_l) = '\0';
	return (str);
}
