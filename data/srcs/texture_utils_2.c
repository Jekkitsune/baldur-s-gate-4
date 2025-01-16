/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:22:09 by fparis            #+#    #+#             */
/*   Updated: 2025/01/16 19:22:22 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	*get_tex(t_data *data, char *name)
{
	t_list		*i;
	t_texture	*current_tex;

	i = data->textures;
	while (i)
	{
		if (i->content)
		{
			current_tex = i->content;
			if (!ft_strcmp(name, current_tex->name))
				return (current_tex);
		}
		i = i->next;
	}
	return (NULL);
}

void	add_tex(t_data *data, t_texture *tex, char *name)
{
	if (!tex || !data)
	{
		ft_putstr_fd("Could not load texture: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd("\n", 2);
		free(name);
		return ;
	}
	tex->name = name;
	ft_lstadd_front(&data->textures, ft_lstnew(tex));
}

t_texture	*get_resized_free(t_texture *texture, int size)
{
	t_texture	*resized;

	if (!texture)
		return (NULL);
	resized = resize(texture, size);
	free_tex(texture);
	return (resized);
}
