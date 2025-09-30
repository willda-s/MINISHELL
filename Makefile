NAME = minishell

INCLUDE = -Iincludes

SIG_DIR = signals/

SIG_FILES = 		setup_signal.c\
					setup_child_parent_signals.c\
					setup_sigint_main_signals.c

ENV_DIR = env/

ENV_FILES = 		env.c\
					lst_utils_env.c

PARSING_DIR = parsing/

PARSING_FILES = 	init_data_and_pars.c\
					init_filename.c\
					init_lst_exec.c\
					lst_utils_exec.c\
					lst_utils_pars.c\
					lst_utils_redir.c\
					split_quotes.c\
					heredoc/heredoc.c\
					heredoc/heredoc_utils.c\
					expand/expandf.c\
					expand/expandf_utils.c\
					expand/expand_utils.c\
					expand/expand_var.c\
					expand/expand_var_utils.c\
					token/type.c\
					token/type_utils.c\
					functions_free.c\
					validate_syntax.c\
					check_input/syntax_error.c\
					check_input/check_input.c\
					check_input/check_input_utils.c\
					check_input/check_input_quotes.c

EXEC_DIR = exec/

EXEC_FILES = 		path/path.c\
					path/path_utils.c\
					exec.c\
					redirections/ft_fd.c\
					redirections/redirections.c\
					redirections/redirections_utils.c\
					handle_builtins_parent.c\
					exec_utils.c\
					wait_process.c

BUILTINS_DIR = builtins/

BUILTINS_FILES = 	builtin_pwd.c\
					builtin_cd.c\
					builtin_cd_utils.c\
					builtin_exit.c\
					builtin_export.c\
					builtin_export_extract.c\
					builtin_unset.c\
					builtin_echo.c\
					builtin_env.c
UTILS = main.c\
		main_utils.c

MAKEFLAGS += --no-print-directory

CC	= cc
CFLAGS	= -Wall -Wextra -Werror -MMD -g3 \
		  -I includes \
		  -I libft/libft_functions/includes \
		  -I libft/vectors/includes \
		  -I libft/ft_printf/includes \
		  -I libft/get_next_line/includes

LIBS = -L$(LIBFT_DIR) -lft -lreadline

FILE =	$(addprefix $(ENV_DIR), $(ENV_FILES))\
		$(addprefix $(EXEC_DIR), $(EXEC_FILES))\
		$(addprefix $(PARSING_DIR), $(PARSING_FILES))\
		$(addprefix $(SIG_DIR), $(SIG_FILES))\
		$(addprefix $(BUILTINS_DIR), $(BUILTINS_FILES))\
		$(UTILS)
		
OBJ_DIR = .obj/

OBJ = $(addprefix $(OBJ_DIR), $(FILE:.c=.o))
DEPD = $(addprefix $(OBJ_DIR), $(FILE:.c=.d))

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)/libft.a

all: banner lib $(NAME)

$(NAME): $(OBJ) $(LIBFT)
		$(CC) $(CFLAGS) -lreadline $(OBJ) -o $(NAME) $(LIBFT) $(LIBS)
# 	@echo "$(PURPLE)👾 Minishell compilation done ! $(RESET)"

$(OBJ_DIR)%.o: %.c Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

-include $(DEPD)

.PHONY: FORCE
FORCE:

$(LIBFT): FORCE
	@make -s -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean:	clean
	$(MAKE) -C $(LIBFT_DIR) fclean	
	rm -f $(NAME)      

lib:
# 	@echo "$(GREEN)🦀 Compiling libft in progress... $(RESET)"
	$(MAKE) -C $(LIBFT_DIR)
# 	@echo "$(GREEN)🦀 Libft compilation done ! $(RESET)"
# 	@echo "$(PURPLE)👾 Compiling Minishell in progress ... $(RESET)"

re: fclean all

banner:
	@clear
	@echo "$(GREEN_DARKER)▐▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▌$(RESET)"
	@echo "$(GREEN_DARKER)▐                                                      ▌$(RESET)"
	@echo "$(GREEN_DARKER)▐    $(GREEN_LIGHT)• ▌ ▄ ·. ▪   ▐ ▄ ▪  .▄▄ ·  ▄ .▄▄▄▄ .▄▄▌  ▄▄▌     $(GREEN_DARKER) ▌$(RESET)"
	@echo "$(GREEN_DARKER)▐    $(GREEN_LIGHT)·██ ▐███▪██ •█▌▐███ ▐█ ▀. ██▪▐█▀▄.▀·██•  ██•     $(GREEN_DARKER) ▌$(RESET)"
	@echo "$(GREEN_DARKER)▐    $(GREEN_LIGHT)▐█ ▌▐▌▐█·▐█·▐█▐▐▌▐█·▄▀▀▀█▄██▀▐█▐▀▀▪▄██▪  ██▪     $(GREEN_DARKER) ▌$(RESET)"
	@echo "$(GREEN_DARKER)▐    $(GREEN_LIGHT)██ ██▌▐█▌▐█▌██▐█▌▐█▌▐█▄▪▐███▌▐▀▐█▄▄▌▐█▌▐▌▐█▌▐▌   $(GREEN_DARKER) ▌$(RESET)"
	@echo "$(GREEN_DARKER)▐    $(GREEN_LIGHT)▀▀  █▪▀▀▀▀▀▀▀▀ █▪▀▀▀ ▀▀▀▀ ▀▀▀ · ▀▀▀ .▀▀▀ .▀▀▀    $(GREEN_DARKER) ▌$(RESET)"
	@echo "$(GREEN_DARKER)▐                                                      ▌$(RESET)"
	@echo "$(GREEN_DARKER)▐▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▌$(RESET)"

.PHONY: all clean fclean re lib banner

# .SILENT:

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