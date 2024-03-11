/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:22:12 by jijeong           #+#    #+#             */
/*   Updated: 2023/05/20 10:38:40 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_free_token(t_mslist *l);
static int	ms_free_cmd_struct(t_mslist *l);
static int	ms_free_cmd(t_cmd *cmd);
static int	ms_free_redi(t_redi *redi);

int	ms_free_data(t_mslist *l)
{
	if (l->token_len)
	{
		ms_free_token(l);
		ms_free_cmd_struct(l);
	}
	return (0);
}

static int	ms_free_token(t_mslist *l)
{
	t_token	*current;
	t_token	*temp;

	current = l->token;
	while (current)
	{
		if (current->code == 8)
			unlink(current->token);
		if (current->token)
			free(current->token);
		temp = current;
		current = current->next;
		free(temp);
	}
	l->token = (void *)0;
	l->token_len = 0;
	return (0);
}

static int	ms_free_cmd_struct(t_mslist *l)
{
	int	i;

	i = 0;
	while (i <= l->cmds_list.pipenum && l->cmds_list.cmds_set)
	{
		ms_free_cmd(l->cmds_list.cmds_set[i].command);
		ms_free_redi(l->cmds_list.cmds_set[i].redi);
		free(l->cmds_list.cmds_set[i].cmds);
		i += 1;
	}
	if (l->cmds_list.cmds_set)
		free(l->cmds_list.cmds_set);
	l->cmds_list.cmds_set = (void *)0;
	if (l->cmds_list.pid)
		free(l->cmds_list.pid);
	l->cmds_list.pid = (void *)0;
	if (l->cmds_list.pipe)
		free(l->cmds_list.pipe);
	l->cmds_list.pipe = (void *)0;
	return (0);
}

static int	ms_free_cmd(t_cmd *cmd)
{
	t_cmd	*current;
	t_cmd	*temp;

	current = cmd;
	while (current)
	{
		if (current->cmd)
			free(current->cmd);
		temp = current;
		current = current->next;
		free(temp);
	}
	return (0);
}

static int	ms_free_redi(t_redi *redi)
{
	t_redi	*current;
	t_redi	*temp;

	current = redi;
	while (current)
	{
		if (redi->fd)
			close(redi->fd);
		if (current->filename)
			free(current->filename);
		temp = current;
		current = current->next;
		free(temp);
	}
	return (0);
}
