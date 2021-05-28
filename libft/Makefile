# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oagrram <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 15:02:47 by oagrram           #+#    #+#              #
#    Updated: 2021/03/29 16:38:21 by oagrram          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OC = ft_isalpha.c ft_lstadd.c ft_memccpy.c ft_memset.c ft_putnbr.c ft_strcat.c ft_strdup.c ft_strlen.c ft_strnequ.c ft_strstr.c ft_spl_whitespaces.c\
	 ft_isascii.c ft_lstdel.c ft_memchr.c ft_print_tables.c ft_putnbr_fd.c ft_strchr.c ft_strequ.c ft_strmap.c ft_strnew.c ft_strsub.c ft_dectohex.c\
	 ft_atoi.c ft_isdigit.c ft_lstdelone.c ft_memcmp.c ft_putchar.c ft_putstr.c ft_strclr.c ft_striter.c ft_strmapi.c ft_strnstr.c ft_strtrim.c\
	 ft_bzero.c ft_isprint.c ft_lstiter.c ft_memcpy.c ft_putchar_fd.c ft_putstr_fd.c ft_strcmp.c ft_striteri.c ft_strncat.c ft_strrchr.c ft_tolower.c\
	 ft_countwords.c ft_itoa.c ft_lstnew.c ft_memdel.c ft_putendl.c ft_sort_ascii.c ft_strcpy.c ft_strjoin.c ft_strncmp.c ft_strrev.c ft_toupper.c ft_strndup.c\
	 ft_isalnum.c ft_len_words.c ft_memalloc.c ft_memmove.c ft_putendl_fd.c ft_space.c ft_strdel.c ft_strlcat.c ft_strncpy.c ft_strsplit.c ft_put2str.c	ft_put4str.c ft_is_whitespace.c\
	 ft_ultimputstr.c get_next_line.c ft_is_there.c ft_putsfd.c ft_putc2str.c ft_putnbstr.c ft_free_tab.c  ft_skip_until_char.c ft_skip_chars.c ft_max.c ft_die.c ft_str_occurence.c ft_swap.c abs.c ft_isinstr.c ft_strreplace.c between.c\

OB = $(OC:.c=.o)

NAME = libft.a

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror

all : $(NAME) $(OB)

$(NAME) :$(OB)
	ar rc libft.a $(OB)
clean :
	    rm -f $(OB)
fclean : clean
	    rm -f $(NAME)
re : fclean all
