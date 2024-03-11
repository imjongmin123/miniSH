/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token_to_cmd1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:08:01 by jijeong           #+#    #+#             */
/*   Updated: 2023/05/31 16:08:05 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_add_cmd_list(t_cmds_set *cmds, t_token *token)
{
	t_cmd	*tmp;

	tmp = cmds->command;
	if (tmp == (void *)0)
	{
		cmds->command = (t_cmd *)malloc(sizeof(t_cmd));
		cmds->command->next = (void *)0;
		cmds->command->cmd = ft_strdup(token->token);
	}
	else
	{
		while (tmp->next != (void *)0)
			tmp = tmp->next;
		tmp->next = (t_cmd *)malloc(sizeof(t_cmd));
		tmp->next->next = (void *)0;
		tmp->next->cmd = ft_strdup(token->token);
	}
	return (0);
}

int	ms_add_redi_list(t_cmds_set *cmds, t_token *token)
{
	t_redi	*tmp;

	tmp = cmds->redi;
	if (tmp == (void *)0)
	{
		cmds->redi = (t_redi *)malloc(sizeof(t_redi));
		cmds->redi->next = (void *)0;
		cmds->redi->redi_code = token->code;
		cmds->redi->filename = ft_strdup(token->next->token);
		if (cmds->redi->redi_code == 1)
			cmds->redi->fd = token->fd;
	}
	else
	{
		while (tmp->next != (void *)0)
			tmp = tmp->next;
		tmp->next = (t_redi *)malloc(sizeof(t_redi));
		tmp->next->next = (void *)0;
		tmp->next->redi_code = token->code;
		tmp->next->filename = ft_strdup(token->next->token);
		if (tmp->next->redi_code == 1)
			tmp->next->fd = token->fd;
	}
	return (0);
}

int	ms_set_cmds(t_mslist *l, int i)
{
	while (i <= l->cmds_list.pipenum)
	{
		ms_cmdtoken_to_cmds(&(l->cmds_list.cmds_set[i]));
		i++;
	}
	return (0);
}

int	ms_cmdtoken_to_cmds(t_cmds_set *set)
{
	t_cmd	*tmp;
	int		i;
	int		j;

	i = 0;
	tmp = set->command;
	while (tmp)
	{
		i += 1;
		tmp = tmp->next;
	}
	set->cmds = (char **)malloc(sizeof(char *) * (i + 1));
	ft_memset(set->cmds, '\0', sizeof(char *) * (i + 1));
	j = 0;
	tmp = set->command;
	while (j < i)
	{
		set->cmds[j] = tmp->cmd;
		tmp = tmp->next;
		j++;
	}
	set->cmds[j] = (void *)0;
	return (0);
}
