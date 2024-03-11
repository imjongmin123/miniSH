/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_line_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:08:06 by jijeong           #+#    #+#             */
/*   Updated: 2023/05/31 16:08:07 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_expansion_token(t_mslist *l)
{
	t_token		*tmptoken;

	tmptoken = l->token;
	while (tmptoken)
	{
		if (tmptoken->code == 10 || tmptoken->code == 9)
			ms_do_expantion(l, tmptoken);
		tmptoken = tmptoken->next;
	}
	return (0);
}

int	ms_do_expantion(t_mslist *l, t_token *tmptoken)
{
	t_strlist	*head;
	t_strlist	*tmp;
	char		*str;
	char		*temp_str;

	head = ms_quote_to_strl(tmptoken->token, 0, 1);
	tmp = head;
	while (tmp)
	{
		if (tmp->quote != 1)
			tmp->str = ms_param(tmp->str, l->env, l->status, 0);
		tmp = tmp->next;
	}
	str = ms_cat_strlist(head);
	temp_str = tmptoken->token;
	tmptoken->token = str;
	free(temp_str);
	ms_free_strlist(head);
	return (0);
}

t_strlist	*ms_quote_to_strl(char *str, int i, int j)
{
	t_strlist	*head;
	char		*tmp;

	head = (void *)0;
	while (str[i])
	{
		while (str[i + j] && ((!ms_isq(str[i]) && !ms_isq(str[i + j])) \
				|| (ms_isq(str[i]) && !ms_isq_piar(str[i], str[i + j]))))
			j++;
		if (ms_isq_piar(str[i], str[i + j]))
		{
			tmp = ft_substr(str, i + 1, j - 1);
			ms_add_strlint(&head, tmp, ms_isq(str[i]));
			i = i + j + 1;
			j = 1;
		}
		else
		{
			tmp = ft_substr(str, i, j);
			ms_add_strlint(&head, tmp, ms_isq(str[i]));
			i = i + j;
			j = 1;
		}
	}
	return (head);
}

int	ms_isq(int c)
{
	if ('\'' == c)
		return (1);
	if ('\"' == c)
		return (2);
	return (0);
}

int	ms_isifs(int c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}
