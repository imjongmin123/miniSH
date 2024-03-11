/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:07:35 by jijeong           #+#    #+#             */
/*   Updated: 2023/05/31 16:07:36 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_cd(t_mslist *l, char **cmds)
{
	struct stat	s;

	if (!cmds[1])
		l->status = 0;
	else if (access(cmds[1], F_OK))
		l->status = ms_error_msg(cmds[1], "file not exist", 1);
	else if (access(cmds[1], X_OK))
		l->status = ms_error_msg(cmds[1], "permition denied", 1);
	else
	{
		stat(cmds[1], &s);
		if ((s.st_mode & S_IFMT) != S_IFDIR)
		{
			l->status = ms_error_msg(cmds[1], "is not a directory", 1);
			return (1);
		}
		chdir(cmds[1]);
		ms_set_old_last_pwd(l);
		l->status = 0;
	}
	return (0);
}

int	ms_set_old_last_pwd(t_mslist *l)
{
	char	*value;
	char	*tmp;

	value = ms_get_value(ft_strdup("PWD"), l->env.envp);
	tmp = ft_strjoin("OLDPWD=", value);
	ms_try_add_env(l, tmp);
	free(value);
	free(tmp);
	value = ms_get_cwd();
	tmp = ft_strjoin("PWD=", value);
	ms_try_add_env(l, tmp);
	free(value);
	free(tmp);
	return (0);
}

int	ms_unset(t_mslist *l, char **cmds)
{
	int	i;

	i = 1;
	while (cmds[i])
	{
		l->env.envp = unset(l->env.envp, cmds[i]);
		i++;
	}
	l->status = 0;
	return (0);
}

int	ms_env(t_mslist *l)
{
	int	i;

	i = 0;
	while (l->env.envp[i])
	{
		if (l->env.envp[i])
			printf("%s\n", l->env.envp[i]);
		i++;
	}
	l->status = 0;
	return (0);
}

int	ms_export(t_mslist *l, char **cmds)
{
	int	i;
	int	j;

	if (cmds[1] == (void *)0)
		ms_env(l);
	i = 1;
	while (cmds[i] != (void *)0)
	{
		j = 0;
		if (j == 0 && ms_isverable(cmds[i][j]))
			j++;
		while (j != 0 && (ms_isverable(cmds[i][j]) || ft_isdigit(cmds[i][j])))
			j++;
		if (j > 0 && cmds[i][j] == '=')
			ms_try_add_env(l, cmds[i]);
		i++;
	}
	l->status = 0;
	return (0);
}
