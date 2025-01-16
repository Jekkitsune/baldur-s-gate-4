# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fparis <fparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/01 15:23:49 by fparis            #+#    #+#              #
#    Updated: 2025/01/16 02:04:57 by fparis           ###   ########.fr        #
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
		map_utils_2.c\
		minimap.c\
		vector_utils.c\
		player.c\
		command.c\
		command_2.c\
		move.c\
		draw_utils.c\
		draw_utils_2.c\
		raycast.c\
		player_vision.c\
		shape_func.c\
		init_data.c\
		trigo_utils.c\
		parsing.c\
		mouse.c\
		move_utils.c\
		resize.c\
		init_textures.c\
		texture_utils.c\
		vectorf_utils.c\
		free.c\
		free_2.c\
		free_map.c\
		ia.c\
		ia_fight.c\
		ia_fights_utils.c\
		update_active.c\
		entity.c\
		entity_draw.c\
		entity_draw_2.c\
		entity_active.c\
		entity_possess.c\
		entity_move.c\
		animation.c\
		animation_init.c\
		load_prefab.c\
		load_prefab_utils.c\
		prefab.c\
		buttons.c\
		buttons_draw.c\
		buttons_draw_2.c\
		buttons_inventory.c\
		inventory.c\
		inventory_2.c\
		inventory_draw_utils.c\
		actions.c\
		actions_2.c\
		spells_init.c\
		spells.c\
		raycast_simple.c\
		fireball.c\
		ui.c\
		put_screen.c\
		stats.c\
		dice.c\
		dice_2.c\
		properties.c\
		pathfinding.c\
		timer_effect.c\
		printf_to_str.c\
		doors.c\
		timer_property.c\
		class.c\
		class_init.c\
		attack.c\
		party.c\
		i_hate_dice.c\
		participant_icon.c\
		combat.c\
		combat_2.c\
		round_manager.c\
		get_prefab_stats.c\
		check_radius_team.c\
		get_prefab_stats_utils.c\
		finish_gnl.c\

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
