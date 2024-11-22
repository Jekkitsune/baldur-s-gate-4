/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:02:10 by fparis            #+#    #+#             */
/*   Updated: 2024/11/20 23:05:10 by fparis           ###   ########.fr       */
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
	anim->anim_sound = NULL;
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
	t_animation	anim;

	add_prefab(data, get_prefab_data(data, "guard"));
	test2 = spawn_entity(data, data->prefab_tab[0], vec(25, 10));
	add_active(data, test2, ft_nothing);
	possess_control(test2, true);
	change_anim(test2, "walk");
	test2->sheet.buttons[0].func = exemple_action;
}
