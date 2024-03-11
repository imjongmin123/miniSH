/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:27:44 by jijeong           #+#    #+#             */
/*   Updated: 2023/05/20 10:38:21 by jijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <term.h>

# define PWDLEN 500

typedef struct s_strlist
{
	char				*str;
	int					quote;
	struct s_strlist	*next;
}						t_strlist;

typedef struct s_here_doc
{
	char	*line;
	char	*del;
	int		quote;
	int		fd;
}			t_here_doc;

typedef struct s_token
{
	char			*token;
	int				code;
	int				fd;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd
{
	char			*cmd;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_redi
{
	char			*filename;
	int				redi_code;
	int				fd;
	struct s_redi	*next;
}					t_redi;

typedef struct s_cmds_set
{
	t_redi	*redi;
	t_cmd	*command;
	char	**cmds;
	int		id;
}			t_cmds_set;

typedef struct s_cmds_list
{
	int			*pipe;
	int			pipenum;
	pid_t		*pid;
	t_cmds_set	*cmds_set;
}			t_cmds_list;

typedef struct s_env
{
	char	**envp;
}			t_env;

typedef struct s_mslist
{
	int			status;
	t_token		*token;
	int			token_len;
	t_cmds_list	cmds_list;
	int			multicmd;
	t_env		env;
}				t_mslist;

// ms_sig.c
void		ms_sigint_handler(int sig);
void		ms_hd_sigint_handler(int sig);
void		ms_set_sigign(void);
void		ms_set_sigdfl(void);
// ms_rl.c
char		*ms_readline(char *s);
char		*ms_hd_readline(char *s);
// ms_builtin.c
int			ms_check_single_builtin(t_mslist *l);
int			ms_is_builtin(char **cmds);
int			ms_single_builtin_redi(t_mslist *l, t_redi *redi);
int			ms_execute_builtin(t_mslist *l, char **cmds);
int			ms_execute_sbuiltin(t_mslist *l, char **cmds);
// ms_parse_cmdline.c
int			ms_parse(t_mslist *l, char *cmd);
int			ms_tokenize(t_mslist *l, char *cmd);
int			ms_ismeta(char c);
int			ms_get_meta_token(t_mslist *l, int *i, int *j, char *cmd);
int			ms_get_word_token(t_mslist *l, int *i, int *j, char *cmd);
// ms_parse.c
int			ms_pass_quote(int *i, char *cmd, char c);
int			ms_add_token(t_mslist *l, char *token);
int			ms_set_token_code(t_token *token);
int			ms_check_token_code(t_token *token);
int			ms_set_meta_token_code(t_token *token);
// ms_here_doc.c
int			ms_make_here_doc(t_mslist *l);
int			ms_here_doc(t_env env, int c, t_here_doc *hd, pid_t pid);
int			ms_make_temp_file(t_token *tmp, t_here_doc *hd, int *i);
int			ms_get_delimiter(char *str, t_here_doc *hd);
// ms_token_to_cmd.c
int			ms_set_command_struct(t_mslist *l);
int			ms_set_command_list_struct(t_mslist *l);
int			ms_set_command_list(t_mslist *l, int i);
int			ms_set_command_set_struct(t_mslist *l);
int			ms_set_redi_cmd_sets(t_mslist *l, int i);
// ms_token_to_cmd1.c
int			ms_add_cmd_list(t_cmds_set *cmds, t_token *token);
int			ms_add_redi_list(t_cmds_set *cmds, t_token *token);
int			ms_set_cmds(t_mslist *l, int i);
int			ms_cmdtoken_to_cmds(t_cmds_set *set);
// ms_line_parse.c
int			ms_expansion_token(t_mslist *l);
int			ms_do_expantion(t_mslist *l, t_token *tmptoken);
t_strlist	*ms_quote_to_strl(char *str, int i, int j);
int			ms_isq(int c);
int			ms_isifs(int c);
// ms_line_parse1.c
int			ms_isq_piar(int c1, int c2);
int			ms_add_strlint(t_strlist **head, char *str, int quote);
char		*ms_cat_strlist(t_strlist	*head);
int			ms_free_strlist(t_strlist *head);
// ms_parameter_expansion.c
char		*ms_param(char *str, t_env env, int c, int i);
int			ms_isverable(char c);
char		*ms_get_key(char *str, int *i);
char		*ms_get_value(char *key, char **envp);
char		*ms_get_new_str(char *tmp, char *value, int *i, int j);
// ms_execute_cmd.c
int			ms_execute(t_mslist *l, int cnt_cmd);
int			ms_executer(t_mslist *l, int cnt_cmd);
int			ms_set_redirection(t_mslist *l, int cnt_cmd);
int			ms_make_pipe(t_mslist *l);
int			ms_set_pipe_fd(t_mslist *l, int cnt_cmd);
// ms_excute_cmd1.c
int			ms_set_pipe_fds(int *pipe, int i, int n);
char		**ms_get_path(char **env);
char		*ms_get_cmd(char *cmd, char **path);
int			ms_access_cmd(char *str);
int			waiting_child(t_mslist *l);
// ms_set_data.c
int			ms_set_data(t_mslist *l, int ac, char **argv, char **envp);
// ms_env.c
void		set_env(char **env, char *new_env);
char		**init_env(char **envp);
char		**add_env(char **env_envp, char *new_env);
void		del_env(char **new_env, char **env, char *var_name);
char		**unset(char **env, char *var_name);
// ms_free.c
int			ms_free_data(t_mslist *l);
// ms_error.c
int			ms_error_msg(char *s1, char *s2, int exit_code);
int			ms_stderr_msg_exit(char *s1, char *s2, int exit_code);
int			ms_syntax_error_msg(char *s, int exit_code);
int			ms_error_msg_exit(char *s, int exit_code);
// ms_builtin1.c
int			ms_cd(t_mslist *l, char **cmds);
int			ms_set_old_last_pwd(t_mslist *l);
int			ms_unset(t_mslist *l, char **cmds);
int			ms_env(t_mslist *l);
int			ms_export(t_mslist *l, char **cmds);
// ms_builtin2.c
int			ms_exit(t_mslist *l, char **cmds);
int			ms_pwd(t_mslist *l);
char		*ms_get_cwd(void);
int			ms_echo(t_mslist *l, char **cmds);
int			ms_try_add_env(t_mslist *l, char *str);
// ms_builtin3.c
int			ms_check_key(char *s1, char *s2);
int			ms_add_env(t_mslist *l, char *str);
int			ms_replace_env(t_mslist *l, char *str, int i);
// ms_sb_redi.c
int			ms_sb_redi_here_doc(t_mslist *l, t_redi *redi);
int			ms_sb_redi_file_in(t_mslist *l, t_redi *redi);
int			ms_sb_redi_file_out(t_mslist *l, t_redi *redi);
int			ms_sb_redi_file_cat(t_mslist *l, t_redi *redi);
// ms_redi.c
int			ms_redi_here_doc(t_redi *redi);
int			ms_redi_file_in(t_redi *redi);
int			ms_redi_file_out(t_redi *redi);
int			ms_redi_file_cat(t_redi *redi);

#endif
