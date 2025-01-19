# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fparis <fparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/01 15:23:49 by fparis            #+#    #+#              #
#    Updated: 2025/01/16 23:51:00 by fparis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wextra -Wall -Werror -g
NAME = cub3D
HEADER = data/headers

SRC_DIR = data/srcs
OBJ_DIR = data/obj

SRCS = main.c \
		vector_utils.c\
		vectorf_utils.c\
		init_data.c\
		free.c\
		parsing.c\
		parsing2.c\
		parsing3.c\
		parsing4.c\
		parsing5.c\
		texture_utils.c\
		texture_utils_2.c\
		resize.c\
		player.c\
		trigo_utils.c\
		command.c\
		move.c\
		player_vision.c\
		raycast.c\
		raycast2.c

LIBFT = data/libft/libft.a

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $(NAME) $(LIBFT) data/macroLibX/libmlx.so -lSDL2 -I $(HEADER) -lm
	 @echo "$(NAME) compilation successful !"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "Compiling $(notdir $<)..."
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(LIBFT):
	@make -s -C data/libft

clean:
	@echo "Removing object..."
	@rm -rf $(OBJ_DIR)
	@echo "Removing libft..."
	@make fclean -s -C data/libft

fclean: clean
	@echo "Removing $(NAME)..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
