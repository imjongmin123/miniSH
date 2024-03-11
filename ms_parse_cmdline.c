/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_cmdline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:22:03 by jijeong           #+#    #+#             */
/*   Updated: 2023/05/20 10:38:50 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_parse(t_mslist *l, char *cmd)
{
	if (ms_tokenize(l, cmd))
		return (1);
	if (!(l->token))
		return (1);
	ms_set_token_code(l->token);
	if (ms_check_token_code(l->token))
		return (1);
	if (ms_make_here_doc(l))
		return (2);
	if (ms_expansion_token(l))
		return (1);
	if (ms_set_command_struct(l))
		return (1);
	return (0);
}

int	ms_tokenize(t_mslist *l, char *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (ms_isifs(cmd[i]))
			i++;
		else if (ms_ismeta(cmd[i]))
			ms_get_meta_token(l, &i, &j, cmd);
		else
			if (ms_get_word_token(l, &i, &j, cmd))
				return (1);
	}
	return (0);
}

int	ms_ismeta(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	ms_get_meta_token(t_mslist *l, int *i, int *j, char *cmd)
{
	char	*token;

	*j = *i;
	if (cmd[*i] == cmd[*i + 1] && !(cmd[*i] == '|'))
		*i += 1;
	token = ft_substr(cmd, *j, *i - *j + 1);
	ms_add_token(l, token);
	*i += 1;
	return (0);
}

int	ms_get_word_token(t_mslist *l, int *i, int *j, char *cmd)
{
	char	*token;

	*j = *i;
	while (cmd[*i])
	{
		if (cmd[*i] == '\'' || cmd[*i] == '\"')
			if (ms_pass_quote(i, cmd, cmd[*i]))
				return (1);
		if (!cmd[*i + 1] || ms_isifs(cmd[*i + 1]) || ms_ismeta(cmd[*i + 1]))
		{
			token = ft_substr(cmd, *j, *i - *j + 1);
			ms_add_token(l, token);
			*i += 1;
			break ;
		}
		*i += 1;
	}
	return (0);
}
