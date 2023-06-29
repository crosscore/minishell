# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/26 18:50:32 by ysakahar          #+#    #+#              #
#    Updated: 2023/06/28 02:58:42 by ysakahar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= cc
MKDIR		= mkdir -p

LIBFTP		= libft
SRC_DIR		= src
BUILD_DIR	= $(SRC_DIR)/build
OBJ_DIR		= $(BUILD_DIR)/objs
LIB_DIR		= ./libft

READLINE_DIR = $(shell brew --prefix readline)
READLINE_LIB = -lreadline -lhistory -L $(READLINE_DIR)/lib
INCLUDES = -Iincludes -I$(LIBFTP) -I$(READLINE_DIR)/include

SRCS		= $(shell find $(SRC_DIR) -name "*.c")
OBJS		= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
#$(info $(SRCS))

FLAGS		= -Wall -Werror -Wextra -g -fsanitize=address
LIBFT		= $(LIB_DIR)/libft.a
HEADER		= includes/minishell.h

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "Linking $@"
	@$(CC) $(FLAGS) $(LIBFT) $(OBJS) $(READLINE_LIB) -o $(NAME)
	@echo "Success"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@$(MKDIR) $(@D)
	@echo "Compiling $<"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIB_DIR)

clean:
	@echo "Cleaning"
	@rm -f $(OBJS)
	@rm -rf $(BUILD_DIR)
	@make fclean -C $(LIB_DIR)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)

re: fclean all

.PRECIOUS: $(OBJ_DIR)/%.o
.PHONY: clean fclean re