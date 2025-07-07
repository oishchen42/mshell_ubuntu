# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/19 20:34:46 by nmikuka           #+#    #+#              #
#    Updated: 2025/07/07 23:01:21 by oishchen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -$(INCLUDES)
CFLAGS_GNL = -Wall -Wextra -Werror -I$(GNL_DIR)
READLINE_LIB = -lreadline

#Directories name
SRC_DIR := src
OBJ_DIR := obj
GNL_DIR := get_next_line
INCLUDES := Iinclude

# Library name
NAME := minishell

# Source and object files
SRC_FILES := main.c ft_split.c ft_strjoin.c libft_utils.c
GNL_FILES := get_next_line.c get_next_line_utils.c

# Structure of SRC and OBJ
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
GNL_SRC = $(addprefix $(GNL_DIR)/, $(GNL_FILES))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
GNL_OBJ = $(addprefix $(GNL_DIR)/, $(GNL_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ) $(GNL_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(GNL_OBJ) $(READLINE_LIB) -o $@
	@echo "\nMinishell is ready to go!"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(GNL_DIR)/%.o : $(GNL_DIR)/%.c
	$(CC) $(CFLAGS_GNL) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR)
	rm -f  $(GNL_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re