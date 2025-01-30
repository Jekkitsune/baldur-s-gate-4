# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fparis <fparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/01 15:23:49 by fparis            #+#    #+#              #
#    Updated: 2025/01/30 12:44:13 by fparis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -g3 -Ofast -fno-short-enums -Wextra -Wall ##-Werror
NAME = cub3D
HEADER = data/headers

SRC_DIR = data/srcs
OBJ_DIR = data/obj

SRCS = main.c\
		maps.c\
		map_utils.c\
		map_utils_2.c\
		minimap.c\
		minimap_2.c\
		vector_utils.c\
		player.c\
		command.c\
		command_2.c\
		move.c\
		move_utils.c\
		move_possession.c\
		draw_utils.c\
		draw_utils_2.c\
		raycast.c\
		raycast_2.c\
		raycast_3.c\
		raycast_simple.c\
		player_vision.c\
		player_vision_2.c\
		player_vision_3.c\
		floor.c\
		ceiling.c\
		skybox.c\
		doors.c\
		shape_func.c\
		init_data.c\
		init_button_lst.c\
		trigo_utils.c\
		parsing.c\
		parsing2.c\
		parsing3.c\
		parsing4.c\
		parsing5.c\
		mouse.c\
		resize.c\
		init_textures.c\
		texture_utils.c\
		texture_utils_2.c\
		vectorf_utils.c\
		free.c\
		free_2.c\
		free_map.c\
		ia.c\
		ia_2.c\
		ia_fight.c\
		ia_fights_utils.c\
		update_active.c\
		update_active_2.c\
		entity.c\
		entity_draw.c\
		entity_draw_2.c\
		entity_draw_3.c\
		entity_active.c\
		entity_possess.c\
		entity_move.c\
		pathfinding.c\
		pathfinding_2.c\
		animation.c\
		animation_init.c\
		prefab.c\
		load_prefab.c\
		load_prefab_utils.c\
		get_prefab_stats.c\
		get_prefab_stats_utils.c\
		get_prefab_stats_utils_2.c\
		buttons.c\
		buttons_draw.c\
		buttons_draw_2.c\
		buttons_inventory.c\
		buttons_inventory_2.c\
		inventory.c\
		inventory_2.c\
		inventory_draw_utils.c\
		actions.c\
		actions_2.c\
		actions_3.c\
		spells_init.c\
		spells.c\
		spells_2.c\
		spells_3.c\
		fireball.c\
		ui.c\
		ui_2.c\
		put_screen.c\
		strput.c\
		stats.c\
		stats_2.c\
		stats_3.c\
		stats_4.c\
		dice.c\
		dice_2.c\
		check.c\
		check_2.c\
		properties.c\
		properties_2.c\
		timer_effect.c\
		timer_property.c\
		timer_property_2.c\
		timer_property_3.c\
		printf_to_str.c\
		printf_to_str_utils.c\
		class.c\
		class_init.c\
		attack.c\
		attack_2.c\
		party.c\
		party_2.c\
		party_3.c\
		i_hate_dice.c\
		participant_icon.c\
		combat.c\
		combat_2.c\
		round_manager.c\
		check_radius_team.c\
		finish_gnl.c\
		interact.c\
		talk.c\
		loot.c\
		gold.c\
		init_game.c\
		get_map_data.c\
		get_map_data_2.c\
		get_map_data_3.c\
		travel.c\
		barbarian.c\
		barbarian_init.c\
		man_throw.c\
		warlock.c\
		warlock_init.c\
		hellish_rebuke.c\
		acid_puddle.c\
		fog.c\
		darkness.c\
		misty_step_shadow_sword.c\
		hunger_of_hadar.c\
		banishment.c\
		wizard_init.c\
		wizard.c\
		web.c\
		hold_person.c\
		dimension_trapdoor.c\
		group_invisibility.c\
		hypnotic_pattern.c\
		dominate.c\
		rogue_init.c\
		steal.c\
		sneak_attack.c\
		menaced.c\
		dash.c\
		monk_init.c\
		monk.c\
		flurry_of_blows.c\
		step_of_the_wind.c\
		stunning_strike.c\
		init_ranger.c\
		hunter_mark.c\
		special_arrow.c\
		special_arrow_2.c\
		sharp_shooter.c\
		arrow_rain.c\
		selection_screen.c\
		selection_screen_2.c\
		consumable.c\
		consumable_2.c

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

.PHONY: all clean fclean re run
