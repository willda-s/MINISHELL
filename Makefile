NAME = minishell

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

NAME_UPPER = $(shell echo $(NAME) | tr '[:lower:]' '[:upper:]')

INCLUDE = -Iincludes -I$(LIBFT_DIR)/Include -Iexec

CFLAGS      = -Wall -Wextra -Werror -MMD -g3 -I./ $(INCLUDE)

# Liste des fichiers builtins (sans backslash final sur le dernier)
BUILTINS_FILES =	ft_pwd.c\
					ft_env.c\
					ft_exit.c\
					ft_exit_is_number_utils.c\
					ft_echo.c\
					ft_cd.c\
					ft_export.c\
					ft_unset.c\
					exec_builtins.c\
					main_builtins.c

# Nouvelle liste des fichiers exec (à compléter avec tes fichiers .c exec)
EXEC_FILES =  exec.c\
			  lst.c\

# Regroupement des fichiers
FILE = $(BUILTINS_FILES) $(EXEC_FILES)

# Sources avec chemin complet
SRCS_BUILTINS = $(addprefix builtins/, $(BUILTINS_FILES))
SRCS_EXEC = $(addprefix exec/, $(EXEC_FILES))
SRCS = $(SRCS_BUILTINS) $(SRCS_EXEC)

OBJ_DIR = obj/

# Objets dans obj/builtins/ et obj/exec/
OBJ_BUILTINS = $(addprefix $(OBJ_DIR)builtins/, $(BUILTINS_FILES:.c=.o))
OBJ_EXEC = $(addprefix $(OBJ_DIR)exec/, $(EXEC_FILES:.c=.o))
OBJ = $(OBJ_BUILTINS) $(OBJ_EXEC)

DEPD = $(OBJ:.o=.d)

CC = cc

MAKEFLAGS += --no-print-directory

# ========== Couleurs ==========
BLUE = \033[34m
GREEN = \033[32m
RED = \033[31m
YELLOW = \033[33m
CYAN = \033[36m
RESET = \033[0m
BOLD = \033[1m
BOLD_GREEN = \033[1;32m
BOLD_WHITE = \033[1;37m
GREEN_DARKER = \033[2;32m
GREEN_LIGHT = \033[;32m
PURPLE = \033[35m

# ========== Règles ==========

all: banner lib $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@start_time=$$(date +%s); \
	$(CC) $(CFLAGS) -lreadline $(OBJ) -o $(NAME) $(LIBFT); \
	end_time=$$(date +%s); \
	duration=$$((end_time - start_time)); \
	printf "\n\n                             $(GREEN)== SUCCESS ✅ ==\n\n\n $(GREEN) The $(NAME) program has been compiled successfully in $(RED)%02d:%02d $(CYAN)(min:sec)\n\n$(RESET)" $$((duration / 60)) $$((duration % 60))

prebuild:
	@echo "                 $(BLUE)============================================$(RESET)"
	@echo "                 $(BLUE)|             $(BOLD_GREEN)$(NAME_UPPER) $(BOLD_WHITE)program            $(BLUE)|$(RESET)"
	@echo "                 $(BLUE)|         $(YELLOW)Compilation in progress...       $(BLUE)|$(RESET)"
	@echo "                 $(BLUE)============================================\n$(RESET)"

# Règle pour compiler un .o à partir d'un .c dans builtins/
$(OBJ_DIR)builtins/%.o: builtins/%.c Makefile prebuild
	@mkdir -p $(dir $@)
	@echo "$(GREEN)⚙️ $(YELLOW)Compiling ... $(CYAN)builtins/$(notdir $<)$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Règle pour compiler un .o à partir d'un .c dans exec/
$(OBJ_DIR)exec/%.o: exec/%.c Makefile prebuild
	@mkdir -p $(dir $@)
	@echo "$(GREEN)⚙️ $(YELLOW)Compiling ... $(CYAN)exec/$(notdir $<)$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Inclusion des fichiers de dépendances
-include $(DEPD)

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

lib:
	@echo "                 $(BLUE)============================================$(RESET)"
	@echo "                 $(BLUE)|               $(BOLD_GREEN)LIBFT $(BOLD_WHITE)library              $(BLUE)|$(RESET)"
	@echo "                 $(BLUE)|         $(YELLOW)Compilation in progress...       $(BLUE)|$(RESET)"
	@echo "                 $(BLUE)============================================\n\n$(RESET)"
	@start_time=$$(date +%s); \
	make -C $(LIBFT_DIR); \
	end_time=$$(date +%s); \
	duration=$$((end_time - start_time)); \
	printf "\n\n                             $(GREEN)== SUCCESS ✅ ==\n\n\n$(GREEN)     The LIBFT $(BOLD_WHITE)library$(GREEN) has been compiled successfully in $(RED)%02d:%02d $(CYAN)(min:sec)\n\n$(RESET)\n\n" $$((duration / 60)) $$((duration % 60))

banner:
	@clear
	@echo "	   $(GREEN_DARKER)▐▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▌$(RESET)"
	@echo "           $(GREEN_DARKER)▐                                                      ▌$(RESET)"
	@echo "           $(GREEN_DARKER)▐    $(GREEN_LIGHT)• ▌ ▄ ·. ▪   ▐ ▄ ▪  .▄▄ ·  ▄ .▄▄▄▄ .▄▄▌  ▄▄▌     $(GREEN_DARKER) ▌$(RESET)"
	@echo "           $(GREEN_DARKER)▐    $(GREEN_LIGHT)·██ ▐███▪██ •█▌▐███ ▐█ ▀. ██▪▐█▀▄.▀·██•  ██•     $(GREEN_DARKER) ▌$(RESET)"
	@echo "           $(GREEN_DARKER)▐    $(GREEN_LIGHT)▐█ ▌▐▌▐█·▐█·▐█▐▐▌▐█·▄▀▀▀█▄██▀▐█▐▀▀▪▄██▪  ██▪     $(GREEN_DARKER) ▌$(RESET)"
	@echo "           $(GREEN_DARKER)▐    $(GREEN_LIGHT)██ ██▌▐█▌▐█▌██▐█▌▐█▌▐█▄▪▐███▌▐▀▐█▄▄▌▐█▌▐▌▐█▌▐▌   $(GREEN_DARKER) ▌$(RESET)"
	@echo "           $(GREEN_DARKER)▐    $(GREEN_LIGHT)▀▀  █▪▀▀▀▀▀▀▀▀ █▪▀▀▀ ▀▀▀▀ ▀▀▀ · ▀▀▀ .▀▀▀ .▀▀▀    $(GREEN_DARKER) ▌$(RESET)"
	@echo "           $(GREEN_DARKER)▐                                                      ▌$(RESET)"
	@echo "           $(GREEN_DARKER)▐▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▌$(RESET)\n"

.PHONY: all clean fclean re lib banner prebuild

.SILENT:
