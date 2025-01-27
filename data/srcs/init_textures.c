/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 01:20:38 by fparis            #+#    #+#             */
/*   Updated: 2025/01/27 04:59:29 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_button(t_data *data, char *path, char *name)
{
	t_texture	*tex;

	tex = path_to_tex(data, path);
	tex = get_resized_free(tex, data->button_scale_size);
	add_tex(data, tex, ft_strdup(name));
}

void	init_more_buttons(t_data *data)
{
	add_button(data, "textures/trapdoor_button.png", "trapdoor_button");
	add_button(data, "textures/group_invi_button.png", "group_invi_button");
	add_button(data, "textures/hypnotic_button.png", "hypnotic_button");
	add_button(data, "textures/dominate_button.png", "dominate_button");
}

void	init_buttons(t_data *data)
{
	add_button(data, "textures/fireball_button.png", "fireball_button");
	add_button(data, "textures/take_button.png", "take_button");
	add_button(data, "textures/inventory_button.png", "inventory_button");
	add_button(data, "textures/check_button.png", "check_button");
	add_button(data, "textures/move_button.png", "move_button");
	add_button(data, "textures/melee_button.png", "melee_button");
	add_button(data, "textures/range_button.png", "range_button");
	add_button(data, "textures/punch_button.png", "punch_button");
	add_button(data, "textures/rage_button.png", "rage_button");
	add_button(data, "textures/reckless_button.png", "reckless_button");
	add_button(data, "textures/man_throw_button.png", "man_throw_button");
	add_button(data, "textures/eldritch_button.png", "eldritch_button");
	add_button(data, "textures/hellish_button.png", "hellish_rebuke_button");
	add_button(data, "textures/acid_puddle_button.png", "acid_puddle_button");
	add_button(data, "textures/darkness_button.png", "darkness_button");
	add_button(data, "textures/misty_step_button.png", "misty_step_button");
	add_button(data, "textures/shadow_sword_button.png", "shadow_sword_button");
	add_button(data, "textures/hadar_button.png", "hadar_button");
	add_button(data, "textures/blight_button.png", "blight_button");
	add_button(data, "textures/banishment_button.png", "banishment_button");
	add_button(data, "textures/fire_bolt_button.png", "fire_bolt_button");
	add_button(data, "textures/healing_word_button.png", "healing_word_button");
	add_button(data, "textures/web_button.png", "web_button");
	add_button(data, "textures/hold_person_button.png", "hold_person_button");
	init_more_buttons(data);
}

void	init_textures(t_data *data)
{
	add_tex(data, path_to_tex(data, "textures/s1.png"), ft_strdup("skybox1"));
	add_tex(data, path_to_tex(data, "textures/s2.png"), ft_strdup("skybox2"));
	add_tex(data, path_to_tex(data, "textures/s3.png"), ft_strdup("skybox3"));
	add_tex(data, path_to_tex(data, "textures/s4.png"), ft_strdup("skybox4"));
	data->sky_box_tex[0] = get_tex(data, "skybox1");
	data->sky_box_tex[1] = get_tex(data, "skybox2");
	data->sky_box_tex[2] = get_tex(data, "skybox3");
	data->sky_box_tex[3] = get_tex(data, "skybox4");
	add_tex(data, path_to_tex(data, "textures/brickwall.png"),
		ft_strdup("ceiling"));
	add_tex(data, path_to_tex(data, "textures/woodwall.png"),
		ft_strdup("floor"));
	data->ceiling = get_tex(data, "ceiling");
	data->floor = get_tex(data, "floor");
	init_buttons(data);
}
