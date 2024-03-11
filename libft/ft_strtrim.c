/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:23:37 by jijeong           #+#    #+#             */
/*   Updated: 2022/03/30 10:19:12 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		l;
	int		start;
	char	*str;
	int		i;

	l = ft_strlen(s1);
	start = 0;
	while (*(s1 + start) && ft_strchr(set, (int)*(s1 + start)))
		start++;
	while (start < l && *(s1 + l - 1) && ft_strchr(set, (int)*(s1 + l - 1)))
		l--;
	str = (char *)malloc(sizeof(char) * (l - start + 1));
	if (!str)
		return (0);
	i = 0;
	while (i < l - start)
	{
		*(str + i) = *(s1 + start + i);
		i++;
	}
	*(str + i) = 0;
	return (str);
}
