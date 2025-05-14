
NAME = minishell

INCLUDE = -Iincludes

BUILTINS_FILES =	ft_pwd.c\
					ft_env.c\
					ft_exit.c\
					ft_echo.c\
					ft_cd.c\
					ft_export.c\
					ft_unset.c\
					exec_builtins.c\
					main_builtins.c

UTILS =

MAKEFLAGS += --no-print-directory

CC	= cc
CFLAGS	= -Wall -Wextra -Werror -MMD -g3

FILE =	$(BUILTINS_FILES)\
		$(UTILS)
		
OBJ_DIR = obj/

OBJ = $(addprefix $(OBJ_DIR), $(FILE:.c=.o))
DEPD = $(addprefix $(OBJ_DIR), $(FILE:.c=.d))

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: banner lib $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@echo "                 $(BLUE)============================================$(RESET)"
	@echo "                 $(BLUE)|             $(BOLD_GREEN)$(NAME) $(BOLD_WHITE)program            $(BLUE)|$(RESET)"
	@echo "                 $(BLUE)|         $(YELLOW)Compilation in progress...       $(BLUE)|$(RESET)"
	@echo "                 $(BLUE)============================================\n$(RESET)"
	@start_time=$$(date +%s); \
	for file in $(notdir $(SRCS)); do \
		echo "$(GREEN)⚙️ $(YELLOW)Compiling... $(CYAN)$$file$(RESET)"; \
		done;
		$(CC) $(CFLAGS) -lreadline $(OBJ) -o $(NAME) $(LIBFT)
			end_time=$$(date +%s); \
	duration=$$((end_time - start_time)); \
	printf "\n                             $(GREEN)== SUCCESS ✅ ==\n\n $(GREEN) The $(NAME) program has been compiled successfully in $(RED)%02d:%02d $(CYAN)(min:sec)\n\n$(RESET)" $$((duration / 60)) $$((duration % 60))

$(OBJ_DIR)%.o: %.c Makefile
			@mkdir -p $(dir $@)
			@echo "$(YELLOW) Compiling ... $(BLUE)$(notdir $<) $(RESET)"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

-include $(DEPD)

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean:	clean
	$(MAKE) -C $(LIBFT_DIR) fclean	
	rm -f $(NAME)      

lib:
	@echo "                 $(BLUE)============================================$(RESET)"
	@echo "                 $(BLUE)|             $(BOLD_GREEN)LIBFT $(BOLD_WHITE)library                $(BLUE)|$(RESET)"
	@echo "                 $(BLUE)|         $(YELLOW)Compilation in progress...       $(BLUE)|$(RESET)"
	@echo "                 $(BLUE)============================================\n$(RESET)"
	@start_time=$$(date +%s); \
	make -C $(LIBFT_DIR); \
	end_time=$$(date +%s); \
	duration=$$((end_time - start_time)); \
	printf "\n                             $(GREEN)== SUCCESS ✅ ==\n\n$(GREEN) The LIBFT library has been compiled successfully in $(RED)%02d:%02d $(CYAN)(min:sec)\n\n$(RESET)" $$((duration / 60)) $$((duration % 60))
re: fclean all

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

.PHONY: all clean fclean re lib banner

.SILENT:

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