NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes #-fsanitize=address
LINK = -lreadline -lcurses
HD = /var/tmp/hd_files

OBJ_SRC_DIR = obj_src
SRC_SRC = $(wildcard src/*.c)
OBJ_SRC = $(patsubst src/%.c, $(OBJ_SRC_DIR)/%.o, $(SRC_SRC))

OBJ_LEX_DIR = obj_lex
SRC_LEX = $(wildcard lex/*.c)
OBJ_LEX = $(patsubst lex/%.c, $(OBJ_LEX_DIR)/%.o, $(SRC_LEX))

OBJ_PARS_DIR = obj_pars
SRC_PARS = $(wildcard parsing/*.c)
OBJ_PARS = $(patsubst parsing/%.c, $(OBJ_PARS_DIR)/%.o, $(SRC_PARS))

OBJ_BUIL_DIR = obj_builtins
SRC_BUIL = $(wildcard builtins/*.c)
OBJ_BUIL = $(patsubst builtins/%.c, $(OBJ_BUIL_DIR)/%.o, $(SRC_BUIL))

OBJ_ERR_DIR = obj_error
SRC_ERR = $(wildcard error/*.c)
OBJ_ERR = $(patsubst error/%.c, $(OBJ_ERR_DIR)/%.o, $(SRC_ERR))

OBJ_LIBFT_DIR = obj_libft
SRC_LIBFT = $(wildcard libft/*.c)
OBJ_LIBFT = $(patsubst libft/%.c, $(OBJ_LIBFT_DIR)/%.o, $(SRC_LIBFT))

OBJ_UTILS_DIR = obj_utils
SRC_UTILS = $(wildcard utils/*.c)
OBJ_UTILS = $(patsubst utils/%.c, $(OBJ_UTILS_DIR)/%.o, $(SRC_UTILS))

MK = mkdir -p
RF = rm -f
RMRF = rm -rf

LIBCACH = ~/Library/Caches/

$(OBJ_SRC_DIR)/%.o: ./src/%.c | $(OBJ_SRC_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_LEX_DIR)/%.o: ./lex/%.c | $(OBJ_LEX_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PARS_DIR)/%.o: ./parsing/%.c | $(OBJ_PARS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_BUIL_DIR)/%.o: ./builtins/%.c | $(OBJ_BUIL_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_ERR_DIR)/%.o: ./error/%.c | $(OBJ_ERR_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_LIBFT_DIR)/%.o: ./libft/%.c | $(OBJ_LIBFT_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_UTILS_DIR)/%.o: ./utils/%.c | $(OBJ_UTILS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ_SRC) $(OBJ_LEX) $(OBJ_PARS) $(OBJ_BUIL) $(OBJ_ERR) $(OBJ_LIBFT) $(OBJ_UTILS)
	@$(CC) $(CFLAGS) $(LINK) -o $(NAME) $(OBJ_SRC) $(OBJ_LEX) $(OBJ_PARS) $(OBJ_BUIL) $(OBJ_ERR) $(OBJ_LIBFT) $(OBJ_UTILS)
	@$(MK) $(HD)

$(OBJ_SRC_DIR):
	@$(MK) $(OBJ_SRC_DIR)

$(OBJ_LEX_DIR):
	@$(MK) $(OBJ_LEX_DIR)

$(OBJ_PARS_DIR):
	@$(MK) $(OBJ_PARS_DIR)

$(OBJ_BUIL_DIR):
	@$(MK) $(OBJ_BUIL_DIR)

$(OBJ_ERR_DIR):
	@$(MK) $(OBJ_ERR_DIR)

$(OBJ_LIBFT_DIR):
	@$(MK) $(OBJ_LIBFT_DIR)

$(OBJ_UTILS_DIR):
	@$(MK) $(OBJ_UTILS_DIR)

clean:
	@$(RMRF) $(OBJ_SRC_DIR)
	@$(RMRF) $(OBJ_LEX_DIR)
	@$(RMRF) $(OBJ_PARS_DIR)
	@$(RMRF) $(OBJ_BUIL_DIR)
	@$(RMRF) $(OBJ_ERR_DIR)
	@$(RMRF) $(OBJ_LIBFT_DIR)
	@$(RMRF) $(OBJ_UTILS_DIR)

fclean: clean
	@$(RF)  $(NAME)
	@# $(RMRF) $(LIBCACH)
	@# $(RMRF) $(HD)

re: fclean all

.PHONY: all clean fclean re
