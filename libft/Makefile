NAME = libft.a

PRINTF_SRCS =	ft_print_char.c \
				ft_print_hex.c \
				ft_print_int.c \
				ft_print_pointer.c \
				ft_print_string.c \
				ft_input_check.c \
				ft_process_format.c \
				ft_process_input.c \
				ft_print_unsigned.c \
				fd_printf.c

GNL_SRCS = 		get_next_line_bonus.c \
		   
LIBFT_SRCS =	ft_atoi.c \
				ft_free.c \
	  			ft_bzero.c \
	  			ft_calloc.c \
	  			ft_isalnum.c \
	   			ft_isalpha.c \
	  			ft_isascii.c \
	  			ft_isdigit.c \
	  			ft_isprint.c \
	  			ft_memchr.c \
	  			ft_memcmp.c \
	   			ft_memcpy.c \
	   			ft_memmove.c \
	   			ft_memset.c \
	   			ft_strchr.c \
	   			ft_strdup.c \
	   			ft_strndup.c \
	   			ft_strlcat.c \
	   			ft_strlcpy.c \
	   			ft_strlen.c \
				ft_strcmp.c \
	   			ft_strncmp.c \
				ft_len_dif.c \
	   			ft_strnstr.c \
	  			ft_strrchr.c \
	        	ft_tolower.c \
	   			ft_toupper.c \
				ft_itoa.c \
	 			ft_putchar_fd.c \
	   			ft_putstr_fd.c \
	  			ft_putnbr_fd.c \
	  		 	ft_strjoin.c \
	 		 	ft_putendl_fd.c \
	 		 	ft_substr.c \
	 		 	ft_striteri.c \
	  		 	ft_split.c \
	  		 	ft_strmapi.c \
	  		 	ft_strtrim.c \
				ft_strchr_index.c \
			 	ft_lstnew_bonus.c \
			 	ft_lstadd_front_bonus.c \
			 	ft_lstsize_bonus.c \
			 	ft_lstlast_bonus.c \
			 	ft_lstadd_back_bonus.c \
			 	ft_lstclear_bonus.c

VECTORS_SRCS =	add_vector.c \
				at_vector.c \
				dup_vector.c \
				free_vector.c \
				init_vector.c \
				merge_vector.c \
				remove_vector.c \
				resize_vector.c \
				reserve_vector.c \
				set_alloc_size.c \
				set_value_at_vector.c

PRINTF_SRCS := $(addprefix ft_printf/srcs/,$(PRINTF_SRCS))
GNL_SRCS := $(addprefix get_next_line/srcs/,$(GNL_SRCS))
LIBFT_SRCS := $(addprefix libft_functions/srcs/,$(LIBFT_SRCS))
VECTORS_SRCS := $(addprefix vectors/srcs/,$(VECTORS_SRCS))

CC = cc
CFLAGS = -Wall -Wextra -Werror -MP -MMD \
	 -I libft_functions/includes \
	 -I ft_printf/includes \
	 -I get_next_line/includes \
	 -I vectors/includes

RED=\033[0;31m
MAGENTA=\033[0;35m
BLUE=\033[0;34m
YELLOW=\033[0;33m
WHITE=\033[0;37m
NC=\033[0m

SRCS = $(LIBFT_SRCS) $(PRINTF_SRCS) $(GNL_SRCS) $(VECTORS_SRCS)

OBJDIR = .objects
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

.PHONY: all
all: ${NAME}

-include ${OBJS:.o=.d}

${NAME}: ${OBJDIR} ${OBJS}
# 	@echo "${BLUE}Creating ${RED}${NAME} ${NC}"
	ar -rsc ${NAME} ${OBJS}

${OBJDIR}:
# 	@echo "${MAGENTA}Creating ${OBJDIR} files ${NC}"
	@mkdir -p ${OBJDIR}

$(OBJDIR)/%.o: %.c
# 	@echo "$(YELLOW)Compiling$(WHITE) $<...$(NC)"
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} -c $< -o $@

.PHONY: clean
clean:
# 	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf ${OBJDIR}

.PHONY: fclean
fclean: clean
# 	@echo "$(RED)Cleaning library $(NAME) $(NC)"
	@rm -f ${NAME}

.PHONY: re
re: fclean all
