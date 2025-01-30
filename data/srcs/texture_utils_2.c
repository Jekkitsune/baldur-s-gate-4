/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:22:09 by fparis            #+#    #+#             */
/*   Updated: 2025/01/29 23:05:52 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_all_cell_tex(t_cell *cell, t_texture *tex)
{
	cell->tex[0] = tex;
	cell->tex[1] = tex;
	cell->tex[2] = tex;
	cell->tex[3] = tex;
}

t_texture	*get_default_tex(t_data *data, char *name)
{
	if (!ft_strcmp(name, "NO"))
		return (data->wall_tex[0]);
	if (!ft_strcmp(name, "SO"))
		return (data->wall_tex[1]);
	if (!ft_strcmp(name, "WE"))
		return (data->wall_tex[2]);
	if (!ft_strcmp(name, "EA"))
		return (data->wall_tex[3]);
	return (NULL);
}

t_texture	*get_tex(t_data *data, char *name)
{
	t_list		*i;
	t_texture	*current_tex;

	if (!name)
		return (NULL);
	if (!ft_strcmp(name, "NO") || !ft_strcmp(name, "SO")
		|| !ft_strcmp(name, "WE") || !ft_strcmp(name, "EA"))
		return (get_default_tex(data, name));
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
