/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 23:25:12 by fparis            #+#    #+#             */
/*   Updated: 2024/12/05 19:57:44 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tex(t_texture *tex)
{
	int	i;

	i = 0;
	if (!tex)
		return ;
	if (tex->name)
		free(tex->name);
	if (tex->tab)
	{
		while (i < tex->size)
		{
			if (tex->tab[i])
				free(tex->tab[i]);
			i++;
		}
		free(tex->tab);
	}
	free(tex);
}

void	free_map(t_data *data, t_map *map)
{
	int		x;
	int		y;
	t_list	*lst;
	t_list	*tmp;

	x = 0;
	lst = map->active_entities;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		destroy_entity(data, tmp->content);
	}
	while (x < map->size.x)
	{
		y = 0;
		while (y < map->size.y)
		{
			lst = map->arr[x][y].entities;
			while (lst)
			{
				tmp = lst;
				lst = lst->next;
				destroy_entity(data, tmp->content);
			}
			y++;
		}
		free(map->arr[x]);
		x++;
	}
	free(map->arr);
	if (map->path)
		free(map->path);
	free(map);
}

void	free_minimap(t_data *data)
{
	int	i;

	i = 0;
	if (data->minimap.img)
		mlx_destroy_image(data->mlx, data->minimap.img);
	while (i < data->minimap.chunk_size)
	{
		free(data->minimap.chunk[i]);
		i++;
	}
	free(data->minimap.chunk);
	data->minimap.chunk = NULL;
}

void	free_prefab_tab(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_prefab)
	{
		free_prefab_entity(data, data->prefab_tab[i]);
		i++;
	}
	if (data->prefab_tab)
		free(data->prefab_tab);
	data->prefab_tab = NULL;
}

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
	entity->anim = NULL;
	entity->current_anim = NULL;
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

void	free_data(t_data *data)
{
	int		i;
	t_list	*lst;
	t_list	*to_free;

	free_prefab_tab(data);
	lst = data->map_list;
	while (lst)
	{
		free_map(data, lst->content);
		to_free = lst;
		lst = lst->next;
		free(to_free);
	}
	free_minimap(data);
	free_tex_lst(data);
	free_visible_lst(data);
	mlx_destroy_image(data->mlx, data->screen_display);
	i = 0;
	while (i < data->win_size.y)
	{
		free(data->screen_buffer[i]);
		i++;
	}
	free(data->screen_buffer);
}

void	exit_free(t_data *data, char *error)
{
	free_data(data);
	ft_putstr_fd("Cub3d error: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}
