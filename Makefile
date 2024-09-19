# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fparis <fparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/01 15:23:49 by fparis            #+#    #+#              #
#    Updated: 2024/09/19 18:20:29 by fparis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g #-Wextra -Werror -Wall -g
NAME = bg4
HEADER = data/headers

SRC_DIR = data/srcs
OBJ_DIR = data/obj

SRCS = main.c\
		maps.c\
		map_utils.c\
		minimap.c\
		vector_utils.c\
		player.c\
		command.c\
		move.c\
		draw_utils.c\
		raycast.c\
		player_vision.c\
		shape_func.c\
		init_data.c\
		trigo_utils.c\
		draw_utils_2.c\
		parsing.c\
		mouse.c\
		move_utils.c\
		resize.c

LIBFT = data/libft/libft.a

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $(NAME) $(LIBFT) data/MacroLibX/libmlx.so -lSDL2 -I $(HEADER) -lm
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

.PHONY: all clean fclean re run
