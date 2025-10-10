NAME    = minishell
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
INCS    = -Ilibft -Iincludes

LDFLAGS = -lreadline

SRC     = main.c \
			main_helpers.c \
			builtins/cd.c \
			builtins/echo.c \
			builtins/export_utils.c \
			builtins/export.c \
			builtins/others.c \
			builtins/unset.c \
			exe/builtin.c \
			exe/exec_child.c \
			exe/executor_helpers.c \
			exe/executor.c \
			exe/find_command_path.c \
			exe/heredoc_helpers.c \
			exe/heredoc_helpers2.c \
			exe/heredoc_helpers3.c \
			exe/heredoc.c \
			exe/path_exec.c \
			exe/pipe_helpers.c \
			exe/redir.c \
			exe/wait_utils.c \
			parser/dollar_expansion.c \
			parser/expand.c \
			parser/expander.c \
			parser/parser.c \
			parser/tokenizer.c \
			utils/command_utils.c \
			utils/env_utils.c \
			utils/redir_utils.c \
			utils/string_utils_more.c \
			utils/string_utils.c \
			utils/token_utils.c

OBJ     = $(SRC:.c=.o)

LIBFT_DIR   = libs/libft
LIBFT_A     = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) $(LDFLAGS) -o $@

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
