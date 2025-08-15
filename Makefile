# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/19 20:34:46 by nmikuka           #+#    #+#              #
#    Updated: 2025/08/14 14:57:51 by nmikuka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Directories
SRC_DIR := src
OBJ_DIR := obj
LIBFT_DIR := libft
GNL_DIR := get_next_line
INCLUDES := include

# Compiler and flags
CC := cc
CFLAGS := -Wall -Wextra -Werror -I$(INCLUDES) -I$(LIBFT_DIR) -I/opt/homebrew/opt/readline/include
READLINE_LIB := -lreadline -L/opt/homebrew/opt/readline/lib
LIBFT = $(LIBFT_DIR)/libft.a

# Library name
NAME := minishell

# Source and object files
SRC_FILES := main.c tokenize_pipe_redir.c tokenize_space.c \
			builtin_cmds.c builtin_export.c builtin_simple_cmds.c builtin_unset.c \
			builtin_utils.c \
			create_cmd.c create_cmd_utills.c run_cmd.c find_executable.c \
			history_utils.c tokenize_utils.c \
			redir_init.c redir_handler.c other.c \
      		signals.c heredoc_utils.c var_expansion.c clean_utils.c
GNL_FILES := get_next_line.c get_next_line_utils.c

# Structure of SRC and OBJ
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
GNL_SRC = $(addprefix $(GNL_DIR)/, $(GNL_FILES))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
GNL_OBJ = $(addprefix $(GNL_DIR)/, $(GNL_FILES:.c=.o))

all: $(LIBFT) $(NAME)

# Build libft.a
$(LIBFT):
	@echo "Building libft..."
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(GNL_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(GNL_OBJ) $(READLINE_LIB) $(LIBFT) -o $@
	@echo "\nMinishell is ready to go!"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(GNL_DIR)/%.o : $(GNL_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)
	rm -f  $(GNL_OBJ)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re