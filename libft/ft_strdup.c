/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:20:57 by jijeong           #+#    #+#             */
/*   Updated: 2022/03/22 10:15:32 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *string)
{
	size_t	i;
	size_t	l;
	char	*str;

	l = 0;
	while (*(string + l))
		l++;
	str = (char *)malloc(sizeof(char) * (l + 1));
	if (!str)
		return (0);
	i = 0;
	while (i <= l)
	{
		*(str + i) = *(string + i);
		i++;
	}
	return (str);
}
