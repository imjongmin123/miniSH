/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:07:49 by jijeong           #+#    #+#             */
/*   Updated: 2023/05/31 16:07:51 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_env(char **env_envp, char *new_env)
{
	char	**env;
	int		i;

	i = 0;
	while (env_envp[i])
		i++;
	env = (char **)malloc((i + 2) * sizeof(char *));
	ft_memset(env, '\0', (i + 2) * sizeof(char *));
	i = 0;
	while (env_envp[i])
	{
		env[i] = ft_strdup(env_envp[i]);
		free(env_envp[i]);
		i++;
	}
	env[i] = ft_strdup(new_env);
	env[i + 1] = (void *)0;
	free(env_envp);
	return (env);
}

char	**init_env(char **envp)
{
	int		i;
	char	**dup_envp;

	i = 0;
	while (envp[i])
		i++;
	dup_envp = (char **)malloc((i + 1) * sizeof(char *));
	ft_memset(dup_envp, '\0', (i + 1) * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		dup_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	dup_envp[i] = (void *)0;
	return (dup_envp);
}

void	set_env(char **env, char *new_env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (new_env[j])
		{
			if (env[i][j] == new_env[j])
				j++;
			else
				break ;
			if (new_env[j] == '=')
			{
				free(env[i]);
				env[i] = ft_strdup(new_env);
				return ;
			}
		}
		i++;
	}
}

void	del_env(char **new_env, char **env, char *var_name)
{
	int	i;
	int	j;
	int	l;

	l = ft_strlen(var_name);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (!(0 == ft_strncmp(var_name, env[i], l) && env[i][l] == '='))
		{
			new_env[j] = env[i];
			j++;
		}
		else
			free(env[i]);
		i++;
	}
	free(env);
}

char	**unset(char **env, char *var_name)
{
	int		i;
	int		flag;
	int		l;
	char	**new_env;

	i = 0;
	flag = 0;
	l = ft_strlen(var_name);
	while (env[i])
	{
		if (0 == ft_strncmp(var_name, env[i], l) && env[i][l] == '=')
			flag = 1;
		i++;
	}
	if (flag)
	{
		new_env = (char **)malloc((i + 1) * sizeof(char *));
		ft_memset(new_env, '\0', (i + 1) * sizeof(char *));
		del_env(new_env, env, var_name);
		return (new_env);
	}
	else
		return (env);
}
