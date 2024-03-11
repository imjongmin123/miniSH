/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:22:09 by jijeong           #+#    #+#             */
/*   Updated: 2023/05/20 10:38:26 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_error_msg(char *s1, char *s2, int exit_code)
{
	write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
	write(STDERR_FILENO, s1, ft_strlen(s1));
	write(STDERR_FILENO, ": ", ft_strlen(": "));
	write(STDERR_FILENO, s2, ft_strlen(s2));
	write(STDERR_FILENO, "\n", ft_strlen("\n"));
	return (exit_code);
}

int	ms_stderr_msg_exit(char *s1, char *s2, int exit_code)
{
	write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
	write(STDERR_FILENO, s1, ft_strlen(s1));
	write(STDERR_FILENO, ": ", ft_strlen(": "));
	write(STDERR_FILENO, s2, ft_strlen(s2));
	write(STDERR_FILENO, "\n", ft_strlen("\n"));
	exit(exit_code);
	return (exit_code);
}

int	ms_syntax_error_msg(char *s, int exit_code)
{
	printf("minishell: syntax error near unexpected token '%s'\n", s);
	return (exit_code);
}

int	ms_error_msg_exit(char *s, int exit_code)
{
	write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
	write(STDERR_FILENO, s, ft_strlen(s));
	write(STDERR_FILENO, "\n", ft_strlen("\n"));
	exit(exit_code);
	return (exit_code);
}
