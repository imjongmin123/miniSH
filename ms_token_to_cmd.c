/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token_to_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:07:58 by jijeong           #+#    #+#             */
/*   Updated: 2023/05/31 16:08:00 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_set_command_struct(t_mslist *l)
{
	ms_set_command_set_struct(l);
	ms_set_redi_cmd_sets(l, 0);
	ms_set_cmds(l, 0);
	return (0);
}

int	ms_set_command_set_struct(t_mslist *l)
{
	int		i;
	t_token	*tmp;

	tmp = l->token;
	while (tmp)
	{
		i = 0;
		while (tmp && !(tmp->code == 6 || tmp->code == 7))
		{
			if (tmp->code == 5)
				i += 1;
			tmp = tmp->next;
		}
		ms_set_command_list(l, i);
		i += 1;
		if (tmp && (tmp->code == 6 || tmp->code == 7))
			tmp = tmp->next;
	}
	return (0);
}

int	ms_set_command_list(t_mslist *l, int i)
{
	int	k;

	l->cmds_list.cmds_set = (t_cmds_set *)malloc(sizeof(t_cmds_set) \
		* (i + 1));
	k = 0;
	while (k <= i)
	{
		l->cmds_list.cmds_set[k].command = (void *)0;
		l->cmds_list.cmds_set[k].redi = (void *)0;
		l->cmds_list.cmds_set[k].cmds = (void *)0;
		l->cmds_list.cmds_set[k].id = k;
		k += 1;
	}
	l->cmds_list.pipenum = i;
	l->cmds_list.pipe = (int *)malloc(sizeof(int) * (i * 2));
	l->cmds_list.pid = (pid_t *)malloc(sizeof(pid_t) * (i + 1));
	return (0);
}

int	ms_set_redi_cmd_sets(t_mslist *l, int i)
{
	t_token	*tmp;

	tmp = l->token;
	while (tmp)
	{
		if (tmp->code == 5)
			i += 1;
		else if (tmp->code == 6 || tmp->code == 7)
			i = 0;
		else
		{
			if (tmp->code == 10)
				ms_add_cmd_list(&(l->cmds_list.cmds_set[i]), tmp);
			else
			{
				ms_add_redi_list(&(l->cmds_list.cmds_set[i]), tmp);
				tmp = tmp->next;
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
