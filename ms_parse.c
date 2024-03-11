/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:07:52 by jijeong           #+#    #+#             */
/*   Updated: 2023/05/31 16:07:55 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pass_quote(int *i, char *cmd, char c)
{
	while (cmd[*i])
	{
		*i += 1;
		if (cmd[*i] == c)
			return (0);
	}
	return (ms_error_msg("tokenizer", "sorry. i can't handle odd quote", 1));
}

int	ms_add_token(t_mslist *l, char *token)
{
	t_token	*current;

	if (!l->token)
	{
		l->token = (t_token *)malloc(sizeof(t_token) * 1);
		l->token->code = 0;
		l->token->next = (void *)0;
		l->token->token = token;
		l->token_len = 1;
		return (0);
	}
	current = l->token;
	while (current->next)
		current = current->next;
	current->next = (t_token *)malloc(sizeof(t_token) * 1);
	current = current->next;
	current->token = token;
	current->code = 0;
	current->next = (void *)0;
	l->token_len += 1;
	return (0);
}

int	ms_set_token_code(t_token *token)
{
	int	pre_code;

	pre_code = 0;
	while (token)
	{
		if (ms_ismeta(token->token[0]))
			ms_set_meta_token_code(token);
		else if (1 <= pre_code && pre_code <= 4)
		{
			token->code = 9;
			if (pre_code == 1)
				token->code = 8;
		}
		else
			token->code = 10;
		pre_code = token->code;
		token = token->next;
	}
	return (0);
}

int	ms_check_token_code(t_token *token)
{
	int	pre_code;
	int	word;

	word = 0;
	pre_code = 0;
	while (token)
	{
		if ((1 <= pre_code && pre_code <= 4) && \
			(1 <= token->code && token->code <= 7))
			return (ms_syntax_error_msg(token->token, 1));
		else if (5 <= token->code && token->code <= 7 && word == 0)
			return (ms_syntax_error_msg(token->token, 1));
		else if ((1 <= token->code && token->code <= 7) && \
			token->next == (void *)0)
			return (ms_syntax_error_msg("\\n", 1));
		else
			word += 1;
		if (token->code == 5)
			word = 0;
		pre_code = token->code;
		token = token->next;
	}
	return (0);
}

int	ms_set_meta_token_code(t_token *token)
{
	if (!ft_strncmp(token->token, "<", 2))
		token->code = 2;
	if (!ft_strncmp(token->token, ">", 2))
		token->code = 3;
	if (!ft_strncmp(token->token, "|", 2))
		token->code = 5;
	if (!ft_strncmp(token->token, "&", 2))
		token->code = 10;
	if (!ft_strncmp(token->token, "<<", 2))
		token->code = 1;
	if (!ft_strncmp(token->token, ">>", 2))
		token->code = 4;
	if (!ft_strncmp(token->token, "||", 2))
		token->code = 10;
	if (!ft_strncmp(token->token, "&&", 2))
		token->code = 10;
	return (0);
}
