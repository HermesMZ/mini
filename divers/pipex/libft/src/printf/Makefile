NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS_DIR = .
OBJS_DIR = objs
INCLUDES_DIR = .
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Fichiers sources de libftprintf
SRCS = \
    check_input.c \
    ft_printf_utils.c \
    ft_printf.c \
    handler_format.c \
    handler_null.c \
    handler_options.c \
    handler_padding.c \
    handler_precision.c \
    handler_precision_nbr.c \
    handler_utils.c \
    parsing_options.c \
	parsing_specs.c \
    parsing.c \

SRCS_PATHS = $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS = $(SRCS_PATHS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# La cible 'all' est la cible par défaut.
# Elle s'assure que libft.a est construite en premier, puis libftprintf.a.
all: $(LIBFT) $(NAME)

# Règle pour construire libftprintf.a
# Elle dépend de ses propres fichiers objets.
# make ne reconstruira l'archive que si un des fichiers objets est plus récent.
$(NAME): $(OBJS) $(LIBFT)
	@mkdir -p tmp_lib_objs
	@cd tmp_lib_objs && ar x ../$(LIBFT)
	@ar rcs $(NAME) tmp_lib_objs/*.o $(OBJS)
	@rm -rf tmp_lib_objs


# Règle pour compiler les fichiers C en fichiers objets
# Le prérequis '| $(OBJS_DIR)' assure que le répertoire 'objs' est créé avant la compilation.
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -c $< -o $@

# Règle pour construire libft.a
# Elle délègue la compilation à son propre Makefile dans le dossier libft.
$(LIBFT):
	@echo "Construction de libft.a..."
	@$(MAKE) -C $(LIBFT_DIR)

# Règle pour créer le répertoire des objets s'il n'existe pas
$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

# La cible 'bonus' est souvent la même que 'all' si les bonus sont gérés par des fichiers séparés
# ou des options de compilation. Si vos bonus sont dans des fichiers _bonus.c,
# vous devrez adapter cette règle pour inclure ces fichiers.
bonus: all

clean:
	@echo "Nettoyage des fichiers objets..."
	@rm -rf $(OBJS_DIR)

fclean: clean
	@echo "Nettoyage de $(NAME) et de libft..."
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# Déclaration des cibles "phony" (non associées à des fichiers réels)
.PHONY: all clean fclean re bonus libft
