NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src
LIBFT_DIR = usefull
OBJ_DIR = obj
INCLUDES_DIR = includes

LIBS = -lreadline

LIBFT = \
	ft_lstadd_back.c \
	ft_strdup.c \
	ft_strlen.c \
	ft_lstclear.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_strjoin.c \
	is_char_token.c \
	ft_strcmp.c \
	ft_split.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_strchr.c \
	ft_strncmp.c \
	ft_putstr_fd.c \

SRC = \
	main.c \
	tokenizer.c \
	type_token.c \
	token_check_syntaxe.c \
	test_parsing.c \
	create_command.c \
	free_command.c \
	ft_lst_add_back_command.c \
	handler_token.c \
	handler_token_2.c \
	m_builtin_cd.c \
	m_builtin_env.c \
	m_builtin.c \
	m_command_validation.c \
	m_debug.c \
	m_env_utils.c \
	m_env.c \
	m_error_handler.c \
	m_exec.c \
	m_pipeline.c \
	m_redirect.c \


SRC_ALL = \
	$(addprefix $(SRC_DIR)/, $(SRC)) \
	$(addprefix $(LIBFT_DIR)/, $(LIBFT)) \

OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRC_ALL)))

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)🔧 Compilation de $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)
	@echo "$(GREEN)✅ Compilé avec succès !$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -c $< -o $@

$(OBJ_DIR)/%.o: $(LIBFT_DIR)/%.c
	@$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)🧹 Fichiers objets supprimés.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)🧼 Exécutable supprimé.$(RESET)"

re: fclean all

.PHONY: all clean fclean re