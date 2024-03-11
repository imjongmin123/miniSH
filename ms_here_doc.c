/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:06:03 by jijeong           #+#    #+#             */
/*   Updated: 2023/05/20 10:38:47 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_make_here_doc(t_mslist *l)
{
	t_here_doc	hd;
	t_token		*tmp;
	int			i;
	int			flag;

	flag = 0;
	i = 1000;
	tmp = l->token;
	while (tmp)
	{
		if (tmp->code == 8)
		{
			ms_get_delimiter(tmp->token, &hd);
			free(tmp->token);
			ms_make_temp_file(tmp, &hd, &i);
			flag = ms_here_doc(l->env, l->status, &hd, 0);
			hd.quote = 0;
			free(hd.del);
			if (flag == SIGINT)
				return (1);
			i += 1;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ms_here_doc(t_env env, int c, t_here_doc *hd, pid_t pid)
{
	int	flag;

	pid = fork();
	if (pid > 0)
		ms_set_sigign();
	else if (pid == 0)
	{
		while (1)
		{
			hd->line = ms_hd_readline("> ");
			if (!ft_strncmp(hd->line, hd->del, ft_strlen(hd->line) + 1))
				break ;
			if (!hd->quote)
				hd->line = ms_param(hd->line, env, c, 0);
			write(hd->fd, hd->line, ft_strlen(hd->line));
			write(hd->fd, "\n", ft_strlen("\n"));
			free(hd->line);
		}
		free(hd->line);
		exit(0);
	}
	waitpid(pid, &flag, 0);
	ms_set_sigdfl();
	return (flag / 256);
}

int	ms_make_temp_file(t_token *tmp, t_here_doc *hd, int *i)
{
	char	*str;
	char	*nbr;

	while (1)
	{
		nbr = ft_itoa(*i);
		str = ft_strjoin(".temp_", nbr);
		free(nbr);
		hd->fd = open(str, O_TRUNC | O_CREAT | O_WRONLY, 0644);
		if (hd->fd != -1)
			break ;
		free(str);
		*i += 1;
	}
	tmp->token = str;
	tmp->fd = hd->fd;
	return (0);
}

int	ms_get_delimiter(char *limiter, t_here_doc *hd)
{
	t_strlist	*head;
	char		*str;
	int			i;

	hd->quote = 0;
	i = 0;
	while (limiter[i] && hd->quote == 0)
	{
		hd->quote = ms_isq(limiter[i]);
		i++;
	}
	head = ms_quote_to_strl(limiter, 0, 1);
	str = ms_cat_strlist(head);
	hd->del = str;
	ms_free_strlist(head);
	return (0);
}
