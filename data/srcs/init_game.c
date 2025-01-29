/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 01:06:19 by fparis            #+#    #+#             */
/*   Updated: 2025/01/28 19:33:48 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map_data(t_data *data);

void	init_one_prefab(t_data *data, char *path, char *name)
{
	t_entity	*prefab;

	prefab = get_prefab_data(data, path);
	add_prefab(data, prefab, ft_strdup(name));
}

void	init_prefabs(t_data *data)
{
	init_one_prefab(data, "prefabs/warlock", "warlock");
	init_one_prefab(data, "prefabs/wizard", "wizard");
	init_one_prefab(data, "prefabs/sword", "sword");
	init_one_prefab(data, "prefabs/bow", "bow");
	init_one_prefab(data, "prefabs/gold", "gold");
}

void	init_all_maps_data(t_data *data)
{
	t_list	*lst;

	lst = data->map_list;
	while (lst)
	{
		data->current_map = lst->content;
		init_map_data(data);
		lst = lst->next;
	}
	data->current_map = data->map_list->content;
}

void	init_game(t_data *data)
{
	init_player(data);
	create_minimap(data, 100, 20);
	update_chunk(data);
	init_textures(data);
	load_spells_prefab(data);
	init_button_lst(data);
	init_all_classes(data);	
	init_prefabs(data);
	init_all_maps_data(data);
}
