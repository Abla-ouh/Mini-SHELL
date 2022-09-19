# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/19 12:13:55 by abouhaga          #+#    #+#              #
#    Updated: 2022/09/19 12:43:35 by abouhaga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = minishell

LIBFT    = libft/libft.a

SRCS = minishell.c lunch_minishell.c strings_utils.c

$(LIBFT):
	make -C libft

OBJS    = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS)  -o $(NAME) $(LIBFT) -lreadline

clean :
	make clean -C libft
	rm -rf $(OBJS)

fclean : clean
	rm -rf libft/libft.a
	rm -rf $(NAME) 

re : fclean all

.PHONY : all clean fclean re