# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fparis <fparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/01 15:23:49 by fparis            #+#    #+#              #
#    Updated: 2025/01/10 15:30:03 by fparis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -g3 -Ofast -Wextra -Wall ##-Werror -g
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
		resize.c\
		texture_utils.c\
		vectorf_utils.c\
		free.c\
		entity.c\
		ia.c\
		entity_active.c\
		entity_possess.c\
		animation.c\
		animation_init.c\
		load_prefab.c\
		prefab.c\
		buttons.c\
		actions.c\
		spells_init.c\
		spells.c\
		raycast_simple.c\
		fireball.c\
		inventory.c\
		ui.c\
		put_screen.c\
		inventory_2.c\
		stats.c\
		dice.c\
		properties.c\
		pathfinding.c\
		timer_effect.c\
		printf_to_str.c\
		doors.c\
		timer_property.c\
		class.c\
		attack.c\
		party.c\
		i_hate_dice.c\
		participant_icon.c\
		combat.c\
		round_manager.c\
		get_prefab_stats.c\
		ia_fight.c

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
