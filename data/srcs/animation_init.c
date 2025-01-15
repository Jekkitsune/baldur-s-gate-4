/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:02:10 by fparis            #+#    #+#             */
/*   Updated: 2025/01/15 02:22:07 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_anim(t_data *data, t_animation *anim, int size, char *path)
{
	int		i;
	char	*str;
	int		nb_sprite;

	nb_sprite = ft_strlen(path) - 6;
	anim->tab = ft_calloc(size, sizeof(t_texture));
	if (!anim->tab)
		exit_free(data, "could not allocate anim");
	str = malloc((ft_strlen(path) + 1) * sizeof(char));
	if (!str)
		exit_free(data, "could not load anim");
	anim->size = size;
	ft_strlcpy(str, path, ft_strlen(path) + 1);
	i = 0;
	while (i++ < size)
	{
		if (i >= 100 && i % 100 == 0)
			str[nb_sprite - 1] = '0' + i % 1000 / 100;
		str[nb_sprite] = '0' + (i % 100 / 10);
		str[nb_sprite + 1] = '0' + i % 10;
		anim->tab[i - 1] = path_to_tex(data, str);
	}
	free(str);
}

void	init_test(t_data *data)
{
	t_entity	*test2;

	add_prefab(data, get_prefab_data(data, "prefabs/guard"), ft_strjoin("guard", ""));
	data->prefab_tab[data->nb_prefab - 1]->sheet.hp = 10;
	data->prefab_tab[data->nb_prefab - 1]->sheet.max_hp = 10;
	data->prefab_tab[data->nb_prefab - 1]->sheet.type = living;
	data->prefab_tab[data->nb_prefab - 1]->sheet.description = ft_strdup("MOI QUAND LE LOUP EST ENSTEIN");
	test2 = spawn_entity(data, get_prefab(data, "guard"), vec(25, 10), ft_strjoin("john", ""));
	add_active(data, test2, ft_nothing);

	add_prefab(data, get_prefab_data(data, "prefabs/omen"), ft_strjoin("omen", ""));
	add_prefab(data, get_prefab_data(data, "prefabs/wizard"), ft_strjoin("wizard", ""));

	test2 = spawn_entity(data, get_prefab(data, "omen"), vec(20, 3), ft_strjoin("omen", ""));
	test2->sheet.wander_ia = base_aggro;
	test2->sheet.team = 1;
	test2->sheet.fight_ia = martial_ia;
	add_active(data, test2, test2->sheet.wander_ia);
	test2->size_scale = 0.9; 

	test2 = spawn_entity(data, get_prefab(data, "omen"), vec(20, 2), ft_strjoin("omen", ""));
	test2->sheet.wander_ia = base_aggro;
	test2->sheet.team = 1;
	test2->sheet.fight_ia = martial_ia;
	add_active(data, test2, test2->sheet.wander_ia);
	test2->size_scale = 0.9; 

	test2 = spawn_entity(data, get_prefab(data, "omen"), vec(20, 4), ft_strjoin("omen", ""));
	test2->sheet.wander_ia = base_aggro;
	test2->sheet.team = 1;
	test2->sheet.fight_ia = martial_ia;
	add_active(data, test2, test2->sheet.wander_ia);
	test2->size_scale = 0.9; 

	test2 = spawn_entity(data, get_prefab(data, "wizard"), vec(26, 9), ft_strjoin("lisa", ""));
	add_active(data, test2, ft_nothing);
	possess_control(test2, true);
	ft_lstadd_front(&data->round_manager.party, ft_lstnew(test2));
	test2->size_scale = 0.9;

	test2 = spawn_entity(data, get_prefab(data, "wizard"), vec(26, 9), ft_strjoin("lisa", ""));
	add_active(data, test2, ft_nothing);
	possess_control(test2, true);
	ft_lstadd_front(&data->round_manager.party, ft_lstnew(test2));
	test2->size_scale = 0.9;

	test2 = spawn_entity(data, get_prefab(data, "wizard"), vec(26, 9), ft_strjoin("lisa", ""));
	add_active(data, test2, ft_nothing);
	possess_control(test2, true);
	ft_lstadd_front(&data->round_manager.party, ft_lstnew(test2));
	test2->size_scale = 0.9;
}
