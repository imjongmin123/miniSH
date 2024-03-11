/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:06:34 by jijeong           #+#    #+#             */
/*   Updated: 2022/04/30 13:15:10 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_atoi_checker(long n, long m, long check);

int	ft_atoi(const char *string)
{
	long	i;
	long	m;
	long	n;
	long	check;

	i = 0;
	m = 1;
	n = 0;
	check = 0;
	while (*(string + i) == ' ' || (9 <= *(string + i) && *(string + i) <= 13))
		i++;
	if (*(string + i) == '+' || *(string + i) == '-')
	{
		if (*(string + i) == '-')
			m *= -1;
		i++;
	}
	while ('0' <= *(string + i) && *(string + i) <= '9')
	{
		n = n * 10 + *(string + i) - '0';
		check++;
		i++;
	}
	return (ft_atoi_checker(n, m, check));
}

static int	ft_atoi_checker(long n, long m, long check)
{
	if (check > 19 && m > 0)
		return (-1);
	if (check > 19 && m < 0)
		return (0);
	if (n < 0 && m < 0)
		return (0);
	if (n < 0 && m > 0)
		return (-1);
	return ((int)(n * m));
}
