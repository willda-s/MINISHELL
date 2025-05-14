NAME			= libft.a
CC			 	= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror
HEADER			= libft.h

vpath %.o obj

MAKEFLAGS += --no-print-directory

SRCS			= 	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c \
					ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
					ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
					ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
					ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
					ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
					ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
					ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
					ft_tolower.c ft_toupper.c get_next_line.c get_next_line_utils.c \
					itoa.c ft_printf_address.c ft_printf_conv.c \
					ft_printf_hex.c ft_printf_uns.c ft_printf.c \
					ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
					ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
					ft_lstmap_bonus.c


OBJ_DIR = obj/

OBJS	= $(SRCS:%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

$(OBJ_DIR)%.o : %.c $(HEADER) Makefile
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW) Compiling ... $(BLUE)$(notdir $<) $(RESET)"
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@echo "$(BLUE) Cleaning ..."
	@rm -rf $(OBJ_DIR)

fclean:	clean
	@$(RM) $(NAME)

re:	fclean $(NAME)

.PHONY: all clean fclean re


BLUE = \033[34m
GREEN = \033[32m
RED = \033[31m
YELLOW = \033[33m
RESET = \033[0m
BOLD = \033[1m
GREEN_DARKER = \033[2;32m
GREEN_LIGHT = \033[;32m
RESET = \033[0m
PURPLE = \033[35m