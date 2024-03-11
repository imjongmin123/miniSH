/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:22:07 by jijeong           #+#    #+#             */
/*   Updated: 2023/05/20 10:38:37 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_execute(t_mslist *l, int cnt_cmd)
{
	int	fds[2];

	fds[0] = dup(STDIN_FILENO);
	fds[1] = dup(STDOUT_FILENO);
	ms_make_pipe(l);
	ms_executer(l, cnt_cmd);
	dup2(fds[0], STDIN_FILENO);
	dup2(fds[1], STDOUT_FILENO);
	return (0);
}

int	ms_executer(t_mslist *l, int cnt_cmd)
{
	char	**cmds;

	while (cnt_cmd <= l->cmds_list.pipenum)
	{
		l->cmds_list.pid[cnt_cmd] = fork();
		if (l->cmds_list.pid[cnt_cmd] == 0)
		{
			cmds = l->cmds_list.cmds_set[cnt_cmd].cmds;
			ms_set_redirection(l, cnt_cmd);
			if (cmds == (void *)0)
				exit(0);
			ms_execute_builtin(l, cmds);
			cmds[0] = ms_get_cmd(cmds[0], ms_get_path(l->env.envp));
			l->status = execve(cmds[0], cmds, l->env.envp);
			exit(l->status);
		}
		cnt_cmd += 1;
	}
	ms_set_sigign();
	waiting_child(l);
	ms_set_sigdfl();
	return (0);
}

int	ms_set_redirection(t_mslist *l, int cnt_cmd)
{
	t_redi	*tmp;

	ms_set_pipe_fd(l, cnt_cmd);
	tmp = l->cmds_list.cmds_set[cnt_cmd].redi;
	while (tmp)
	{
		if (tmp->redi_code == 1)
			ms_redi_here_doc(tmp);
		if (tmp->redi_code == 2)
			ms_redi_file_in(tmp);
		if (tmp->redi_code == 3)
			ms_redi_file_out(tmp);
		if (tmp->redi_code == 4)
			ms_redi_file_cat(tmp);
		tmp = tmp->next;
	}
	return (0);
}

int	ms_make_pipe(t_mslist *l)
{
	int	i;

	i = 0;
	while (i < l->cmds_list.pipenum)
	{
		pipe(&(l->cmds_list.pipe[i * 2]));
		i++;
	}
	return (0);
}

int	ms_set_pipe_fd(t_mslist *l, int cnt_cmd)
{
	int	i;
	int	n;
	int	*pipe;

	i = 0;
	pipe = l->cmds_list.pipe;
	n = l->cmds_list.pipenum;
	while (i <= n)
	{
		if (i == cnt_cmd)
			ms_set_pipe_fds(pipe, i, n);
		else
		{
			if (i != 0)
				close(pipe[2 * (i - 1)]);
			if (i != n)
				close(pipe[(2 * i) + 1]);
		}
		i += 1;
	}
	return (0);
}
