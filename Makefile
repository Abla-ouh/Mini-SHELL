# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: midfath <midfath@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/19 12:13:55 by abouhaga          #+#    #+#              #
#    Updated: 2022/10/27 22:55:11 by midfath          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



#Color:

RED		= \033[0;31m
DEFAULT	= \033[0;39m
PINK	= \033[1;35m
BLUE	= \033[1;34m

#vars

CC 			= gcc
CFLAGS 		= -Wall -Wextra -Werror  -fsanitize=address -g
# CFLAGS 		= -Wall -Wextra -Werror
NAME 		= minishell
LIBFT    	= libft/libft.a
OBJ_DIR		= obj
BIN_DIR		= bin
BTIN_DIR	= builtin_src
NAME		= $(BIN_DIR)/$(BIN)
BIN			= minishell
SRC_DIR		= code
RDLINE		= -lreadline -lncurses
RDLINE_FLAG =  -L ~/homebrew/opt/readline/lib
RDLINE_PATH =  -I ~/homebrew/opt/readline/include

#cmd
PRINTF		= printf
FT_FPRINTF = ft_fprintf/libftfprintf.a

#src&&obj
SRC			=	ft_shell.c  ft_tokenize.c \
			  	ft_outfiles.c ft_lexer.c ft_lexer_utils.c ft_parser.c ft_parser_utils.c\
			  	ft_last_io.c ft_infiles.c ft_heredoc.c ft_get_path.c ft_fill_args.c \
			  	ft_expand.c ft_errors.c \
		    	exe_data.c err_handling.c builtin_src/builtin_utils.c \
				builtin_src/cd_exe.c builtin_src/echo_exe.c builtin_src/env_exe.c \
				builtin_src/export_exe.c builtin_src/exit_exe.c builtin_src/pwd_exe.c \
				builtin_src/unset_exe.c exe_utils.c ft_exec.c exe_option.c
				

OBJS    	= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))


all : $(NAME)

$(NAME) : $(BIN_DIR) $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(FT_FPRINTF) $(RDLINE) $(RDLINE_FLAG) $(RDLINE_PATH) -I inc -o $(NAME)
	@$(PRINTF) "\r%100s\r$(BLUE)$(NAME) is up to date!$(DEFAULT)\n"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(RDLINE_PATH) -I inc -c $< -o $@ 
	@$(PRINTF) "\rCompiling $(BLUE)$<$(DEFAULT)..."

$(LIBFT):
	@make -C libft
	@make -C ft_fprintf

$(BIN_DIR) :
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)/$(BTIN_DIR)

clean :
	@make clean -C libft
	@make clean -C ft_fprintf

fclean : clean
	@rm -rf libft/libft.a
	@rm -rf ft_fprintf/libftfprintf.a
	@rm -rf $(BIN_DIR)
	@rm -rf $(OBJ_DIR)
	@$(PRINTF) "$(RED) $(NAME) removed successfully. $(DEFAULT)\n"

re : fclean all

.PHONY : all clean fclean 