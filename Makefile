# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/19 20:34:46 by nmikuka           #+#    #+#              #
#    Updated: 2025/07/13 21:27:10 by nmikuka          ###   ########.fr        #
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
CFLAGS := -Wall -Wextra -Werror -I$(INCLUDES) -I$(LIBFT_DIR)
READLINE_LIB := -lreadline
LIBFT = $(LIBFT_DIR)/libft.a

# Library name
NAME := minishell

# Source and object files
SRC_FILES := main.c run_cmd.c clean_utils.c export_utils.c \
			pipex.c ft_split_cmd.c fork_utils.c pipex_utils.c
GNL_FILES := get_next_line.c get_next_line_utils.c

# Structure of SRC and OBJ
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
GNL_SRC = $(addprefix $(GNL_DIR)/, $(GNL_FILES))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
GNL_OBJ = $(addprefix $(GNL_DIR)/, $(GNL_FILES:.c=.o))

# Build libft.a
$(LIBFT):
	@echo "Building libft..."
	@$(MAKE) -C $(LIBFT_DIR)

all: $(LIBFT) $(NAME)

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