/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 01:20:38 by fparis            #+#    #+#             */
/*   Updated: 2025/01/16 01:43:53 by fparis           ###   ########.fr       */
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
	add_button(data, "textures/fireball_button.png", "fireball_button");
	add_button(data, "textures/take_button.png", "take_button");
	add_button(data, "textures/inventory_button.png", "inventory_button");
	add_button(data, "textures/check_button.png", "check_button");
	add_button(data, "textures/move_button.png", "move_button");
	add_button(data, "textures/melee_button.png", "melee_button");
	add_button(data, "textures/range_button.png", "range_button");
	add_button(data, "textures/punch_button.png", "punch_button");
}
