# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oagrram <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/25 16:01:20 by oagrram           #+#    #+#              #
#    Updated: 2021/03/25 16:01:22 by oagrram          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = 	src/builtins.c\
	   	src/environement.c\
	   	src/execute_pipe.c\
	   	src/execute_redirection.c\
	   	src/execute_redirection2.c\
	   	src/execute_simple_cmd.c\
	   	src/ft_cd.c\
	   	src/ft_cd_env.c\
	   	src/ft_change_arg.c\
	   	src/main.c\
	   	src/path_checker.c\
	   	src/sh_execution.c\
	   	src/sh_loop.c\
	   	src/tools.c\
	   	src/tools2.c\
		src/ft_expanitions.c\
		src/free_ast.c\
		src/parser/check_quotes.c\
	   	src/parser/check_syntax.c\
	   	src/parser/parse_types.c\
	   	src/parser/parser.c\
	   	src/parser/tokenz.c\
	   	src/parser/tokenz_checker.c\
		src/parser/tokenz_checker2.c\


OBJS    = $(SRCS:.c=.o)


NAME		= 21sh
CC = gcc
CFLAGS		= -Wall -Wextra -Werror -g

all : makelib $(NAME)

makelib:
	@make -C libft
	@make -C readline	

$(NAME) : $(OBJS) libft/libft.a  readline/readline.a 
	gcc -g -ltermcap $(CFLAG) $(OBJS) libft/libft.a  readline/readline.a -o $(NAME)

clean :
	rm -rf $(OBJS) 
	@make -C libft clean

fclean : clean
	rm -rf $(NAME)
	@make -C libft fclean

re : fclean all
