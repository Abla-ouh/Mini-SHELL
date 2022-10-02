# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: midfath <midfath@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/19 12:13:55 by abouhaga          #+#    #+#              #
#    Updated: 2022/10/02 11:05:52 by midfath          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#Color:

RED		= \033[0;31m
DEFAULT	= \033[0;39m
PINK	= \033[1;35m
BLUE	= \033[1;34m

#vars

CC 			= gcc
CFLAGS 		= -Wall -Wextra -Werror  -fsanitize=address
# CFLAGS 		= -Wall -Wextra -Werror
NAME 		= minishell
LIBFT    	= libft/libft.a
OBJ_DIR		= obj
BIN_DIR		= bin
NAME		= $(BIN_DIR)/$(BIN)
BIN			= minishell
SRC_DIR		= code
RDLINE		= -lreadline

#cmd

PRINTF		= printf

#src&&obj
SRC			= minishell.c lunch_minishell.c strings_utils.c \
				cd_exe.c env_exe.c

OBJS    	= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))


all : $(NAME)

$(NAME) : $(BIN_DIR) $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(RDLINE) -I inc -o $(NAME)
	@$(PRINTF) "\r%100s\r$(BLUE)$(NAME) is up to date!$(DEFAULT)\n"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -I inc -c $< -o $@
	@$(PRINTF) "\rCompiling $(BLUE)$<$(DEFAULT)..."

$(LIBFT):
	@make -C libft

$(BIN_DIR) :
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

clean :
	@make clean -C libft

fclean : clean
	@rm -rf libft/libft.a
	@rm -rf $(BIN_DIR)
	@rm -rf $(OBJ_DIR)
	@$(PRINTF) "$(RED) $(NAME) removed successfully. $(DEFAULT)\n"

re : fclean all

.PHONY : all clean fclean 