/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:20:41 by jijeong           #+#    #+#             */
/*   Updated: 2022/04/30 13:17:05 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	**mk_strs(char const *s, char c);
static void	mk_strs_str(char **strs, char const *s, char c);
static void	fill_strs_str(char **strs, char const *s, char c);
static void	free_strs(char **strs);

char	**ft_split(char const *s, char c)
{
	char	**strs;

	strs = mk_strs(s, c);
	if (strs != (void *)0)
		mk_strs_str(strs, s, c);
	if (strs != (void *)0)
		fill_strs_str(strs, s, c);
	return (strs);
}

static char	**mk_strs(char const *s, char c)
{
	char	**strs;
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (*(s + i))
	{
		if ((i == 0 && *s != c) || (i && (*(s + i - 1) == c && *(s + i) != c)))
			count += 1;
		i++;
	}
	strs = (char **)malloc(sizeof(char *) * (count + 1));
	if (!strs)
		return (0);
	strs[count] = (void *)0;
	return (strs);
}

static void	mk_strs_str(char **strs, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = 0;
	count = 0;
	while (*(s + i))
	{
		if ((i == 0 && *s != c) || (i && (*(s + i - 1) == c && *(s + i) != c)))
		{
			j = 0;
			while (*(s + i + j) != c && *(s + i + j) != 0)
				j++;
			strs[count] = (char *)malloc(sizeof(char) * (j + 1));
			if (strs[count] == (void *)0)
				free_strs(strs);
			count += 1;
		}
		i++;
	}
}

static void	fill_strs_str(char **strs, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = 0;
	count = 0;
	while (*(s + i))
	{
		if ((i == 0 && *s != c) || (i && (*(s + i - 1) == c && *(s + i) != c)))
		{
			j = 0;
			while (*(s + i + j) != c && *(s + i + j) != 0)
			{
				strs[count][j] = *(s + i + j);
				j++;
			}
			strs[count][j] = 0;
			count += 1;
		}
		i++;
	}
}

static void	free_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i] != (void *)0)
	{
		free(strs[i]);
		i += 1;
	}
	free(strs);
}
