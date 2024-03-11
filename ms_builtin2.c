/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:07:37 by jijeong           #+#    #+#             */
/*   Updated: 2023/05/31 16:07:39 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_try_add_env(t_mslist *l, char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (l->env.envp[i])
	{
		if (ms_check_key(l->env.envp[i], str))
		{
			ms_replace_env(l, str, i);
			flag = 1;
		}
		i++;
	}
	if (flag == 0)
		ms_add_env(l, str);
	return (0);
}

int	ms_exit(t_mslist *l, char **cmds)
{
	int	i;

	if (!cmds[1])
		exit(l->status);
	i = 0;
	while (cmds[1][i])
	{
		if (cmds[1][0] == '-')
			i = 1;
		if (!ft_isdigit(cmds[1][i]) || i > 9)
			ms_error_msg_exit("exit: numeric argument required", 255);
		i++;
	}
	if (cmds[1] && cmds[2])
		return (ms_error_msg(cmds[0], "too many arguments", 0));
	exit(ft_atoi(cmds[1]));
	return (0);
}

int	ms_pwd(t_mslist *l)
{
	char	*str;

	str = ms_get_value(ft_strdup("PWD"), l->env.envp);
	if (str[0] == '\0')
	{
		free(str);
		str = ms_get_cwd();
	}
	printf("%s\n", str);
	l->status = 0;
	free(str);
	return (0);
}

char	*ms_get_cwd(void)
{
	char	str[PWDLEN];
	char	*tmp;

	ft_memset(str, '\0', PWDLEN);
	getcwd(str, PWDLEN);
	str[499] = '\0';
	tmp = ft_strdup(str);
	return (tmp);
}

int	ms_echo(t_mslist *l, char **cmds)
{
	int	i;

	i = 1;
	if (cmds[1] && !ft_strncmp("-n", cmds[1], 3))
		i += 1;
	while (cmds[i] != (void *)0)
	{
		if (2 < i || (i == 2 && cmds[1] && ft_strncmp("-n", cmds[1], 3)))
			write(1, " ", ft_strlen(" "));
		write(1, cmds[i], ft_strlen(cmds[i]));
		i++;
	}
	if (!cmds[1] || (cmds[1] && ft_strncmp("-n", cmds[1], 3)))
		write(1, "\n", ft_strlen("\n"));
	l->status = 0;
	return (0);
}
