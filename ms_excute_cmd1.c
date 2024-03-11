/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_excute_cmd1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:08:15 by jijeong           #+#    #+#             */
/*   Updated: 2023/05/31 16:08:17 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_set_pipe_fds(int *pipe, int i, int n)
{
	if (i != 0)
		dup2(pipe[2 * (i - 1)], STDIN_FILENO);
	if (i != n)
		dup2(pipe[(2 * i) + 1], STDOUT_FILENO);
	return (0);
}

char	**ms_get_path(char **env)
{
	char	*str;
	char	**path;

	str = ms_get_value(ft_strdup("PATH"), env);
	if (str[0] == '\0')
	{
		free(str);
		return ((void *)0);
	}
	path = ft_split(str, ':');
	free(str);
	return (path);
}

char	*ms_get_cmd(char *cmd, char **path)
{
	int		i;
	char	*str;
	char	*tmp;

	str = (void *)0;
	if ((cmd[0] == '\0' || cmd[0] == '.' || cmd[0] == '/') && \
		ms_access_cmd(cmd))
		return (cmd);
	i = 0;
	while (path && path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		str = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(str, X_OK))
			break ;
		free(str);
		str = (void *)0;
		i++;
	}
	if (!str && !ms_access_cmd(cmd))
		return (cmd);
	ms_access_cmd(str);
	return (str);
}

int	ms_access_cmd(char *str)
{
	struct stat	s;

	if (access(str, F_OK))
		ms_stderr_msg_exit(str, "file not found!", 1);
	else if (access(str, X_OK))
		ms_stderr_msg_exit(str, "permition denied", 1);
	stat(str, &s);
	if ((s.st_mode & S_IFMT) == S_IFDIR)
		ms_stderr_msg_exit(str, "is directory", 1);
	return (0);
}

int	waiting_child(t_mslist *l)
{
	int	i;
	int	status;
	int	*pipe;

	i = 0;
	pipe = l->cmds_list.pipe;
	while (i <= l->cmds_list.pipenum)
	{
		if (i != 0)
			close(pipe[2 * (i - 1)]);
		if (i != l->cmds_list.pipenum)
			close(pipe[(2 * i) + 1]);
		i += 1;
	}
	i = 0;
	while (i <= l->cmds_list.pipenum)
	{
		waitpid(l->cmds_list.pid[i], &status, 0);
		l->status = status / 256;
		i += 1;
	}
	return (0);
}
