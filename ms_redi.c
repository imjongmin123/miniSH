/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:07:47 by jijeong           #+#    #+#             */
/*   Updated: 2023/05/31 16:07:48 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_redi_here_doc(t_redi *redi)
{
	redi->fd = open(redi->filename, O_RDONLY);
	if (0 > redi->fd)
		ms_stderr_msg_exit(redi->filename, "open fail", 1);
	dup2(redi->fd, STDIN_FILENO);
	return (0);
}

int	ms_redi_file_in(t_redi *redi)
{
	redi->fd = open(redi->filename, O_RDONLY);
	if (0 > redi->fd)
		ms_stderr_msg_exit(redi->filename, "open fail", 1);
	dup2(redi->fd, STDIN_FILENO);
	return (0);
}

int	ms_redi_file_out(t_redi *redi)
{
	redi->fd = open(redi->filename, O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (0 > redi->fd)
		ms_stderr_msg_exit(redi->filename, "open fail", 1);
	dup2(redi->fd, STDOUT_FILENO);
	return (0);
}

int	ms_redi_file_cat(t_redi *redi)
{
	redi->fd = open(redi->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (0 > redi->fd)
		ms_stderr_msg_exit(redi->filename, "open fail", 1);
	dup2(redi->fd, STDOUT_FILENO);
	return (0);
}
