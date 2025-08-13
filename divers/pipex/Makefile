NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
SRCS_DIR = src
CORE_DIR = $(SRCS_DIR)/core
MANDATORY_DIR = $(SRCS_DIR)/mandatory
BONUS_DIR = $(SRCS_DIR)/bonus
OBJS_DIR = objs
INCLUDES_DIR = includes
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

CORE_SRCS = \
	init.c \
	parsing.c \
	command_parser.c \
	quote_parser.c \
	command_validation.c \
	exec.c \
	pipeline.c \
	utils.c \
	debug_utils.c \
	redirect.c \
	error_handler.c \

MANDATORY_SRCS = \
	main.c \

BONUS_SRCS = \
	exec_bonus.c \
	here_doc_bonus.c \
	main_bonus.c \
	pipeline_bonus.c \

CORE_SRCS_PATH = $(addprefix $(CORE_DIR)/, $(CORE_SRCS))
MANDATORY_SRCS_PATH = $(addprefix $(MANDATORY_DIR)/, $(MANDATORY_SRCS))
BONUS_SRCS_PATH = $(addprefix $(BONUS_DIR)/, $(BONUS_SRCS))

CORE_OBJS = $(CORE_SRCS_PATH:$(CORE_DIR)/%.c=$(OBJS_DIR)/core/%.o)
MANDATORY_OBJS = $(MANDATORY_SRCS_PATH:$(MANDATORY_DIR)/%.c=$(OBJS_DIR)/mandatory/%.o)
BONUS_OBJS = $(BONUS_SRCS_PATH:$(BONUS_DIR)/%.c=$(OBJS_DIR)/bonus/%.o)

INCLUDES = -I $(INCLUDES_DIR) -I $(LIBFT_DIR)/includes

all: $(LIBFT) $(NAME)

$(NAME): $(CORE_OBJS) $(MANDATORY_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(CORE_OBJS) $(MANDATORY_OBJS) $(LIBFT) -o $(NAME)

bonus: $(LIBFT) $(NAME)_bonus

$(NAME)_bonus: $(CORE_OBJS) $(BONUS_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(CORE_OBJS) $(BONUS_OBJS) $(LIBFT) -o $(NAME)

$(OBJS_DIR)/core/%.o: $(CORE_DIR)/%.c | $(OBJS_DIR)/core
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/mandatory/%.o: $(MANDATORY_DIR)/%.c | $(OBJS_DIR)/mandatory
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/bonus/%.o: $(BONUS_DIR)/%.c | $(OBJS_DIR)/bonus
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/core:
	mkdir -p $(OBJS_DIR)/core

$(OBJS_DIR)/mandatory:
	mkdir -p $(OBJS_DIR)/mandatory

$(OBJS_DIR)/bonus:
	mkdir -p $(OBJS_DIR)/bonus

$(LIBFT):
	@echo "Construction de libft.a..."
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@echo "Nettoyage des fichiers objets..."
	@rm -rf $(OBJS_DIR)

fclean: clean
	@echo "Nettoyage de $(NAME) et de libft..."
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

fclean_bonus: clean
	@echo "Nettoyage de $(NAME), libft et fichiers bonus..."
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

re_bonus: fclean_bonus bonus

.PHONY: all bonus clean fclean fclean_bonus re re_bonus