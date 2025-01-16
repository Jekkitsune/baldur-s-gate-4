/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 23:11:45 by fparis            #+#    #+#             */
/*   Updated: 2025/01/15 23:12:18 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_prefab_entity(t_data *data, t_entity *entity)
{
	int	i;
	int	i2;

	if (entity->anim)
	{
		i = 0;
		while (i < entity->nb_anim)
		{
			if (entity->anim[i].name)
				free(entity->anim[i].name);
			i2 = 0;
			while (i2 < entity->anim[i].size)
			{
				free_tex(entity->anim[i].tab[i2]);
				i2++;
			}
			free(entity->anim[i].tab);
			i++;
		}
		free(entity->anim);
	}
	if (entity->sheet.portrait)
		free_tex(entity->sheet.portrait);
	free(entity->sheet.description);
	destroy_entity(data, entity);
}

void	free_tex_lst(t_data *data)
{
	t_list		*lst_i;
	t_list		*tmp;

	lst_i = data->textures;
	while (lst_i)
	{
		if (lst_i->content)
			free_tex(lst_i->content);
		tmp = lst_i;
		lst_i = lst_i->next;
		free(tmp);
	}
	free_tex(data->wall_tex[0]);
	free_tex(data->wall_tex[1]);
	free_tex(data->wall_tex[2]);
	free_tex(data->wall_tex[3]);
}
