#COLOR:

BLUE = \033[0;34m
DEFAULT = \033[0;39m
PINK = \033[1;35m


#Make_file
NAME		= libft.a

CC			= gcc
CFLAG	    = -Wall -Wextra -Werror

RM			= rm -f

AR			= ar
ARFLAGS     = crs

PRINTF		= printf

SRCS	= ft_strlen.c \
		  ft_strlcpy.c \
		  ft_strlcat.c \
		  ft_strchr.c \
		  ft_strnstr.c \
		  ft_strncmp.c \
		  ft_strcmp.c \
		  ft_strdup.c \
		  ft_strrchr.c \
		  ft_striteri.c \
		  ft_memset.c \
		  ft_memcpy.c \
		  ft_memmove.c \
		  ft_memchr.c \
		  ft_memcmp.c \
		  ft_bzero.c \
		  ft_atoi.c \
		  ft_calloc.c \
		  ft_isalnum.c \
		  ft_isalpha.c \
		  ft_isascii.c \
		  ft_isdigit.c \
		  ft_isprint.c \
		  ft_strdup.c \
		  ft_tolower.c \
		  ft_toupper.c \
		  ft_substr.c \
		  ft_strtrim.c \
		  ft_split.c \
		  ft_strmapi.c \
		  ft_itoa.c \
		  ft_putchar_fd.c \
		  ft_putstr_fd.c \
		  ft_putendl_fd.c \
		  ft_putnbr_fd.c \
		  ft_countchar.c \
		  ft_strjoin3.c \
		  ft_strjoin.c \
		  ft_strrncmp.c \
		  ft_matrixdup.c \
		  ft_matfreex.c \
		  ft_istrchr.c

SRCS_BN = ft_lstnew_bonus.c \
		  ft_lstsize_bonus.c \
		  ft_lstadd_front_bonus.c \
		  ft_lstadd_back_bonus.c \
		  ft_lstclear_bonus.c \
		  ft_lstlast_bonus.c \
		  ft_lstiter_bonus.c \
		  ft_lstmap_bonus.c	\
		  ft_lstdelone_bonus.c

OBJS	= $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BN:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) bonus 
	@$(PRINTF) "\r%100s\r$(BLUE)$(NAME) is up to date!$(DEFAULT)\n"

%.o : %.c
	@$(CC) $(CFLAG) -c $< -o $@
	@$(AR) $(ARFLAGS) $(NAME) $@
	@$(PRINTF) "\rCompiling $(BLUE)$<$(DEFAULT)..."
	

clean :
	@$(PRINTF) "$(PINK)Cleaning libft ...$(DEFAULT)\n"
	@$(RM)  $(OBJS) $(OBJS_BONUS)

fclean : clean
	@$(RM)  $(NAME)
	@$(PRINTF) "$(PINK)$(NAME) removed successfully :D$(DEFAULT)\n"

re : fclean all

bonus : $(OBJS_BONUS)

.PHONY : all clean fclean re