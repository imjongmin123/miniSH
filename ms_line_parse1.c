/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_line_parse1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:08:08 by jijeong           #+#    #+#             */
/*   Updated: 2023/05/31 16:08:11 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_isq_piar(int c1, int c2)
{
	if ('\'' == c1 && '\'' == c2)
		return (1);
	if ('\"' == c1 && '\"' == c2)
		return (2);
	return (0);
}

int	ms_add_strlint(t_strlist **head, char *str, int quote)
{
	t_strlist	*current;

	if (!(*head))
	{
		*head = (t_strlist *)malloc(sizeof(t_strlist) * 1);
		(*head)->next = (void *)0;
		current = *head;
	}
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = (t_strlist *)malloc(sizeof(t_strlist) * 1);
		current = current->next;
	}
	current->str = str;
	current->quote = quote;
	current->next = (void *)0;
	return (0);
}

char	*ms_cat_strlist(t_strlist *head)
{
	t_strlist	*tmp_l;
	char		*str;
	char		*tmp_s;

	str = ft_strdup("");
	tmp_l = head;
	while (tmp_l)
	{
		tmp_s = str;
		str = ft_strjoin(str, tmp_l->str);
		free(tmp_s);
		tmp_l = tmp_l->next;
	}
	return (str);
}

int	ms_free_strlist(t_strlist *head)
{
	t_strlist	*current;
	t_strlist	*temp;

	current = head;
	while (current)
	{
		free(current->str);
		temp = current;
		current = current->next;
		free(temp);
	}
	return (0);
}
