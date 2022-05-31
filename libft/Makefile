# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/23 12:28:09 by amarchal          #+#    #+#              #
#    Updated: 2022/05/30 17:10:29 by dvallien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	ft_bzero.c			\
		ft_calloc.c			\
	   	ft_isalnum.c		\
	   	ft_isalpha.c 		\
		ft_isascii.c		\
	   	ft_isdigit.c		\
	   	ft_isprint.c		\
	   	ft_itoa.c			\
	   	ft_memchr.c			\
	   	ft_memcmp.c			\
	   	ft_memcpy.c			\
	   	ft_memmove.c		\
	   	ft_memset.c			\
	   	ft_putchar_fd.c		\
	   	ft_putendl_fd.c		\
	   	ft_putnbr_fd.c		\
	   	ft_putstr_fd.c		\
	   	ft_split.c			\
		ft_split_clear.c	\
	   	ft_strchr.c			\
	   	ft_strdup.c			\
	   	ft_striteri.c		\
	   	ft_strjoin.c		\
	   	ft_strlcat.c		\
		ft_strcpy.c			\
	   	ft_strlcpy.c		\
	   	ft_strlen.c			\
	   	ft_strmapi.c 		\
		ft_strcmp.c			\
		ft_strncmp.c		\
	   	ft_strnstr.c		\
	   	ft_strrchr.c		\
	   	ft_strtrim.c		\
	   	ft_substr.c			\
	   	ft_tolower.c		\
		ft_atoi.c			\
	   	ft_toupper.c		\
		get_next_line.c		\
		get_next_line_utils.c	\

OBJS = $(SRCS:.c=.o)
HDRS = libft.h
CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a

%.o : %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@ 

all:	$(NAME)
		@printf "\033[0;32mLibft is set !\033[0m\n"

bonus:	all

$(NAME): $(OBJS)
		ar rcs $(NAME) $(OBJS)
		
clean:
		@rm -rf $(OBJS)
		@printf "\033[0;33mLibft's objects deleted\033[0m\n"

fclean:	clean
		@rm -rf $(NAME)
		
re:		fclean all

.PHONY:	all clean fclean re bonus 
