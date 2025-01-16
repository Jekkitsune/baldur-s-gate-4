/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 23:43:25 by fparis            #+#    #+#             */
/*   Updated: 2025/01/16 23:44:23 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_path(t_path **path)
{
	if (!path || !*path)
		return ;
	free_path(&(*path)->next);
	free(*path);
	*path = NULL;
}

t_path	*pop_path(t_path **path)
{
	t_path	*res;

	if (!path || !*path)
		return (NULL);
	res = *path;
	if (*path)
		*path = (*path)->next;
	return (res);
}

t_path	*get_specific_path(t_path *path, t_vector pos)
{
	t_path	*tmp;

	tmp = path;
	while (tmp && (tmp->pos.x != pos.x || tmp->pos.y != pos.y))
		tmp = tmp->next;
	return (tmp);
}

void	add_path(t_vector pos, t_vector from, t_path **path)
{
	t_path	*new;
	t_path	*tmp;

	new = ft_calloc(sizeof(t_path), 1);
	if (!new)
		return ;
	new->from = from;
	new->pos = pos;
	tmp = *path;
	if (!tmp)
		*path = new;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = new;
}

t_bool	good_path(t_data *data, t_vector pos, t_path *path)
{
	if (!is_empty_cell(data, pos) || get_specific_path(path, pos))
		return (false);
	return (true);
}
