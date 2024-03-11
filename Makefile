# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jijeong <jijeong@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/27 14:40:05 by jijeong           #+#    #+#              #
#    Updated: 2023/05/20 10:35:55 by jijeong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
AR = ar
ARFLAG = -rcs
CC = cc
CFLAG = -Wall -Wextra -Werror #-fsanitize=address
RM = rm
RMFLAG = -fr
LIBFTDIR = libft
LIBFT =  -l ft -L $(LIBFTDIR)
GNURLDIR = ~/.brew/Cellar/readline/8.2.1
GNURL = -l readline -L $(GNURLDIR)/lib -I $(GNURLDIR)/include


SRCS =	minishell.c					\
		ms_builtin.c				\
		ms_builtin1.c				\
		ms_builtin2.c				\
		ms_builtin3.c				\
		ms_env.c					\
		ms_error.c					\
		ms_excute_cmd1.c			\
		ms_execute_cmd.c			\
		ms_free_data.c				\
		ms_here_doc.c				\
		ms_line_parse.c				\
		ms_line_parse1.c			\
		ms_parameter_expansion.c	\
		ms_parse.c					\
		ms_parse_cmdline.c			\
		ms_redi.c					\
		ms_rl.c						\
		ms_sb_redi.c				\
		ms_set_data.c				\
		ms_sig.c					\
		ms_token_to_cmd.c			\
		ms_token_to_cmd1.c
OBJS = $(SRCS:%.c=%.o)

$(NAME) : $(OBJS)
	make -C libft
	$(CC) $(CFLAG) $(LIBFT) $(GNURL) $^ -o $@

%.o : %.c
	$(CC) $(CFLAG) -I $(GNURLDIR)/include -c $^ -o $@

all : $(NAME)

bonus : $(NAME_B)

clean :
	make -C libft clean
	$(RM) $(RMFLAG) $(OBJS) $(OBJS_B)

fclean :
	make clean
	make -C libft fclean
	$(RM) $(RMFLAG) $(NAME) $(NAME_B)

re :
	make fclean
	make all

.PHONY: all bonus clean fclean re
