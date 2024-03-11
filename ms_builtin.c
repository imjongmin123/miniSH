/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:07:31 by jijeong           #+#    #+#             */
/*   Updated: 2023/05/31 16:07:34 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_check_single_builtin(t_mslist *l)
{
	int	fds[2];

	if (l->cmds_list.pipenum == 0)
	{
		if (l->cmds_list.cmds_set[0].cmds[0] != (void *)0 && \
			ms_is_builtin(l->cmds_list.cmds_set[0].cmds))
		{
			fds[0] = dup(STDIN_FILENO);
			fds[1] = dup(STDOUT_FILENO);
			if (0 == ms_single_builtin_redi(l, l->cmds_list.cmds_set[0].redi))
				ms_execute_sbuiltin(l, l->cmds_list.cmds_set[0].cmds);
			dup2(fds[0], STDIN_FILENO);
			dup2(fds[1], STDOUT_FILENO);
			return (1);
		}
	}
	return (0);
}

int	ms_single_builtin_redi(t_mslist *l, t_redi *redi)
{
	while (redi)
	{
		if (redi->redi_code == 1)
			if (ms_sb_redi_here_doc(l, redi))
				return (1);
		if (redi->redi_code == 2)
			if (ms_sb_redi_file_in(l, redi))
				return (1);
		if (redi->redi_code == 3)
			if (ms_sb_redi_file_out(l, redi))
				return (1);
		if (redi->redi_code == 4)
			if (ms_sb_redi_file_cat(l, redi))
				return (1);
		redi = redi->next;
	}
	return (0);
}

int	ms_is_builtin(char **cmds)
{
	if (!cmds[0])
		return (0);
	if (!ft_strncmp("cd", cmds[0], 3))
		return (1);
	if (!ft_strncmp("unset", cmds[0], 6))
		return (1);
	if (!ft_strncmp("env", cmds[0], 4))
		return (1);
	if (!ft_strncmp("export", cmds[0], 7))
		return (1);
	if (!ft_strncmp("exit", cmds[0], 5))
		return (1);
	if (!ft_strncmp("pwd", cmds[0], 4))
		return (1);
	if (!ft_strncmp("echo", cmds[0], 5))
		return (1);
	return (0);
}

int	ms_execute_builtin(t_mslist *l, char **cmds)
{
	if (!ft_strncmp("cd", cmds[0], 3))
		exit(ms_cd(l, cmds));
	if (!ft_strncmp("unset", cmds[0], 6))
		exit(ms_unset(l, cmds));
	if (!ft_strncmp("env", cmds[0], 4))
		exit(ms_env(l));
	if (!ft_strncmp("export", cmds[0], 7))
		exit(ms_export(l, cmds));
	if (!ft_strncmp("exit", cmds[0], 5))
		exit(ms_exit(l, cmds));
	if (!ft_strncmp("pwd", cmds[0], 4))
		exit(ms_pwd(l));
	if (!ft_strncmp("echo", cmds[0], 5))
		exit(ms_echo(l, cmds));
	return (0);
}

int	ms_execute_sbuiltin(t_mslist *l, char **cmds)
{
	if (!ft_strncmp("cd", cmds[0], 3))
		return (!ms_cd(l, cmds));
	if (!ft_strncmp("unset", cmds[0], 6))
		return (!ms_unset(l, cmds));
	if (!ft_strncmp("env", cmds[0], 4))
		return (!ms_env(l));
	if (!ft_strncmp("export", cmds[0], 7))
		return (!ms_export(l, cmds));
	if (!ft_strncmp("exit", cmds[0], 5))
		return (!ms_exit(l, cmds));
	if (!ft_strncmp("pwd", cmds[0], 4))
		return (!ms_pwd(l));
	if (!ft_strncmp("echo", cmds[0], 5))
		return (!ms_echo(l, cmds));
	return (0);
}
