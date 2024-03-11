/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:10:57 by jijeong           #+#    #+#             */
/*   Updated: 2022/04/30 12:59:47 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t number, size_t size)
{
	char	*mem;
	size_t	i;

	mem = (char *)malloc(number * size);
	if (!mem || (size && number > (size_t)(-1) / size))
		return ((void *)0);
	i = 0;
	while (i < number * size)
	{
		*(mem + i) = 0;
		i++;
	}
	return ((void *)mem);
}
