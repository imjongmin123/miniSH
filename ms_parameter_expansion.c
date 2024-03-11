/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parameter_expansion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:08:12 by jijeong           #+#    #+#             */
/*   Updated: 2023/05/31 16:08:14 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_param(char *tmp, t_env env, int c, int i)
{
	char	*key;
	char	*value;
	int		j;

	while (tmp[i])
	{
		j = 0;
		value = (void *)0;
		if (tmp[i] == '$')
		{
			if (tmp[i + 1] == '?')
				tmp = ms_get_new_str(tmp, ft_itoa(c), &i, 2);
			else if (ms_isverable(tmp[i + 1]))
			{
				key = ms_get_key(&tmp[i + 1], &j);
				value = ms_get_value(key, env.envp);
				tmp = ms_get_new_str(tmp, value, &i, j + 1);
			}
			else
				i += 1;
		}
		else
			i += 1;
	}
	return (tmp);
}

int	ms_isverable(char c)
{
	if (c == '_')
		return (1);
	return (ft_isalpha((int)c));
}

char	*ms_get_key(char *str, int *i)
{
	*i = 1;
	while (ms_isverable(str[*i]) || ft_isdigit(str[*i]))
		*i += 1;
	return (ft_substr(str, 0, *i));
}

char	*ms_get_value(char *key, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(key);
	while (envp[i])
	{
		if (!ft_strncmp(key, envp[i], j))
		{
			if (envp[i][j] == '=')
			{
				free(key);
				return (ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j - 1));
			}
		}
		i += 1;
	}
	free(key);
	return (ft_strdup(""));
}

char	*ms_get_new_str(char *tmp, char *value, int *i, int j)
{
	char	*str;
	char	*temp;
	char	*left;
	char	*right;

	left = ft_substr(tmp, 0, *i);
	right = ft_substr(tmp, *i + j, ft_strlen(tmp) - *i - j);
	temp = ft_strjoin(left, value);
	*i = ft_strlen(temp);
	str = ft_strjoin(temp, right);
	free(left);
	free(value);
	free(temp);
	free(right);
	free(tmp);
	return (str);
}
