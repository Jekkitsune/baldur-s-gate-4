/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:02:10 by fparis            #+#    #+#             */
/*   Updated: 2024/11/09 14:53:19 by fparis           ###   ########.fr       */
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
	t_entity	*test;
	int			i;

	test = add_active(data, create_entity(data, vec(25, 10), 1, data->textures[4]), ft_nothing);
	test->anim = ft_calloc(4, sizeof(t_animation));
	test->nb_anim = 4;
	i = 0;
	while (i < 4)
	{
		test->anim[i].interval = 17;
		i++;
	}
	init_anim(data, &test->anim[0], 11, "test/walk_r_01.png");
	test->anim[0].name = ft_strjoin("walk", "");
	init_anim(data, &test->anim[1], 11, "test/walk_r_01.png");
	test->anim[1].name = ft_strjoin("walk_sider", "");
	init_anim(data, &test->anim[2], 11, "test/walk_l_01.png");
	test->anim[2].name = ft_strjoin("walk_sidel", "");
	init_anim(data, &test->anim[3], 11, "test/walk_l_01.png");
	test->anim[3].name = ft_strjoin("walk_back", "");
	change_anim(test, "walk", 0);
}
