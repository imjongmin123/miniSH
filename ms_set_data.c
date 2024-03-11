/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_set_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:21:57 by jijeong           #+#    #+#             */
/*   Updated: 2023/05/20 10:38:53 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_set_data(t_mslist *l, int ac, char **argv, char **envp)
{
	if (1 < ac)
		ms_error_msg_exit("too many argument", 1);
	(void)argv;
	l->cmds_list.pipenum = 0;
	l->cmds_list.pipe = (void *)0;
	l->cmds_list.pid = (void *)0;
	l->cmds_list.cmds_set = (void *)0;
	l->env.envp = init_env(envp);
	l->multicmd = 0;
	l->status = 0;
	l->token = (void *)0;
	l->token_len = 0;
	return (0);
}
