# --- Configuration de base ---
NAME := libft.a
CC := cc
CFLAGS := -Wall -Wextra -Werror

# --- Répertoires ---
SRC_DIR := src
OBJ_DIR := obj
INCLUDES_DIR := includes

# --- Listes de fichiers sources par catégorie ---
SRCS_GNL := \
	get_next_line.c \
	get_next_line_utils.c \

SRCS_LISTS := \
	ft_dlstadd_back.c \
	ft_dlstadd_front.c \
	ft_dlstclear.c \
	ft_dlstdelone.c \
	ft_dlstinit.c \
	ft_dlstnew_elem.c \
	ft_dlstsize.c \
    ft_lstadd_back.c \
    ft_lstadd_front.c \
    ft_lstclear.c \
    ft_lstdelone.c \
    ft_lstiter.c \
    ft_lstlast.c \
    ft_lstmap.c \
    ft_lstnew.c \
    ft_lstsize.c \
	ft_lstremove_nod.c

SRCS_MEM := \
    ft_bzero.c \
    ft_calloc.c \
    ft_memchr.c \
    ft_memcmp.c \
    ft_memcpy.c \
    ft_memmove.c \
    ft_memset.c \
    ft_realloc.c

SRCS_MY_ALLOC := \
	ft_my_free_all.c \
	ft_my_free.c \
	ft_my_malloc.c \
	ft_split_alloc.c \
	ft_strjoin_alloc.c \
	ft_init_allocator.c \

SRCS_NUM := \
	ft_abs.c \
    ft_atoi.c \
    ft_atol.c \
    ft_hextoi.c \
    ft_itoa.c \
    ft_itoa_ll.c \
	ft_max.c \
	ft_min.c \
    ft_ptoa.c \
    ft_utohex.c

SRCS_PRINTF := \
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
    parsing.c

SRCS_PUT := \
    ft_putchar_fd.c \
    ft_putendl_fd.c \
    ft_putnbr_fd.c \
    ft_putstr_fd.c

SRCS_STR := \
    ft_split.c \
    ft_strchr.c \
	ft_strcmp.c \
    ft_strdup.c \
    ft_striteri.c \
    ft_strjoin.c \
    ft_strlcat.c \
    ft_strlcpy.c \
    ft_strlen.c \
    ft_strmapi.c \
    ft_strncmp.c \
    ft_strndup.c \
    ft_strnstr.c \
    ft_strrchr.c \
    ft_strtrim.c \
    ft_substr.c \
    ft_tolower.c \
    ft_toupper.c \
    ft_toupper_string.c

SRCS_TYPE := \
    ft_isalnum.c \
    ft_isalpha.c \
    ft_isascii.c \
    ft_isdigit.c \
    ft_isprint.c

# Génère une liste de tous les fichiers .c avec leurs chemins complets
SRCS_ALL := \
    $(addprefix $(SRC_DIR)/gnl/, $(SRCS_GNL)) \
    $(addprefix $(SRC_DIR)/lists/, $(SRCS_LISTS)) \
    $(addprefix $(SRC_DIR)/mem/, $(SRCS_MEM)) \
    $(addprefix $(SRC_DIR)/my_alloc/, $(SRCS_MY_ALLOC)) \
    $(addprefix $(SRC_DIR)/num/, $(SRCS_NUM)) \
    $(addprefix $(SRC_DIR)/printf/, $(SRCS_PRINTF)) \
    $(addprefix $(SRC_DIR)/put/, $(SRCS_PUT)) \
    $(addprefix $(SRC_DIR)/str/, $(SRCS_STR)) \
    $(addprefix $(SRC_DIR)/type/, $(SRCS_TYPE))

# Génère la liste des fichiers objets correspondants
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o, $(SRCS_ALL))

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Création de $(NAME)"
	ar rcs $(NAME) $(OBJS)

# Crée les répertoires obj nécessaires avant de compiler
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -c $< -o $@

# --- Nettoyage ---
clean:
	@echo "Nettoyage des fichiers objets..."
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "Nettoyage de la bibliothèque..."
	@rm -f $(NAME)

re: fclean all

# --- Cibles par défaut ---
.PHONY: all clean fclean re