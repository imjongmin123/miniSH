/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:38:23 by jijeong           #+#    #+#             */
/*   Updated: 2023/05/20 10:38:15 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*commandline;
	t_mslist	l;
	int			flag;

	ms_set_data(&l, argc, argv, envp);
	while (1)
	{
		commandline = ms_readline("minishell> ");
		if (commandline[0] != '\0')
		{
			flag = ms_parse(&l, commandline);
			if (flag == 1)
				l.status = 1;
			else if (l.token_len)
			{
				add_history(commandline);
				if (flag != 2 && !ms_check_single_builtin(&l))
					ms_execute(&l, 0);
			}
		}
		free(commandline);
		ms_free_data(&l);
	}
	return (0);
}
