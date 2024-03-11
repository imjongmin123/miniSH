/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:16:06 by jijeong           #+#    #+#             */
/*   Updated: 2022/04/30 13:15:45 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*ft_number_check_mkstr(long long int nb, int *len);

char	*ft_itoa(int n)
{
	char			*nbr;
	int				len;
	int				i;
	long long int	nb;

	len = 0;
	nb = (long long int)n;
	nbr = ft_number_check_mkstr(nb, &len);
	if (!nbr)
		return ((void *)0);
	i = 0;
	if (nb < 0)
		nb *= -1;
	while (nb > 0)
	{
		*(nbr + len - i - 1) = '0' + nb % 10;
		nb /= 10;
		i++;
	}
	if (n == 0)
		*nbr = '0';
	return (nbr);
}

static char	*ft_number_check_mkstr(long long int nb, int *len)
{
	int		minus;
	char	*str;

	minus = 0;
	if (0 > nb)
	{
		minus = 1;
		*len += 1;
		nb *= -1;
	}
	if (nb == 0)
		*len += 1;
	while (nb > 0)
	{
		*len += 1;
		nb /= 10;
	}
	str = (char *)malloc(sizeof(char) * (*len + 1));
	if (str && minus == 1)
		*str = '-';
	if (str)
		*(str + *len) = '\0';
	return (str);
}
