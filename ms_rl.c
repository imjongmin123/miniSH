/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_rl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:07:26 by jijeong           #+#    #+#             */
/*   Updated: 2023/05/31 16:07:27 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_readline(char *s)
{
	char			*commandline;
	struct termios	ord_term;
	struct termios	new_term;

	tcgetattr(1, &ord_term);
	tcgetattr(1, &new_term);
	new_term.c_lflag &= ~(ICANON | ECHOCTL);
	new_term.c_cc[VMIN] = 1;
	new_term.c_cc[VTIME] = 0;
	tcsetattr(1, TCSANOW, &new_term);
	signal(SIGINT, ms_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	commandline = readline(s);
	if (!commandline)
	{
		write(1, "exit\n", 5);
		exit(1);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	tcsetattr(1, TCSANOW, &ord_term);
	return (commandline);
}

char	*ms_hd_readline(char *s)
{
	char			*commandline;
	struct termios	ord_term;
	struct termios	new_term;

	tcgetattr(1, &ord_term);
	tcgetattr(1, &new_term);
	new_term.c_lflag &= ~(ICANON | ECHOCTL);
	new_term.c_cc[VMIN] = 1;
	new_term.c_cc[VTIME] = 0;
	tcsetattr(1, TCSANOW, &new_term);
	signal(SIGINT, ms_hd_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	commandline = readline(s);
	if (!commandline)
		exit(0);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	tcsetattr(1, TCSANOW, &ord_term);
	return (commandline);
}
