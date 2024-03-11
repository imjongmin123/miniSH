/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:07:41 by jijeong           #+#    #+#             */
/*   Updated: 2023/05/31 16:07:43 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_check_key(char *s1, char *s2)
{
	int	i;
	int	l;

	i = 0;
	l = ft_strlen(s2);
	while (i < l)
	{
		if (0 < i && (s1[i] == '=' && s2[i] == '='))
			return (1);
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (0);
}

int	ms_add_env(t_mslist *l, char *str)
{
	l->env.envp = add_env(l->env.envp, str);
	return (0);
}

int	ms_replace_env(t_mslist *l, char *str, int i)
{
	free(l->env.envp[i]);
	l->env.envp[i] = ft_strdup(str);
	return (0);
}
