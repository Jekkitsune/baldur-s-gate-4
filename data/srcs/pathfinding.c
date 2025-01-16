/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 22:00:32 by fparis            #+#    #+#             */
/*   Updated: 2025/01/16 23:45:17 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_path	*get_specific_path(t_path *path, t_vector pos);
void	add_path(t_vector pos, t_vector from, t_path **path);
t_bool	good_path(t_data *data, t_vector pos, t_path *path);

t_path	*get_good_path(t_path *full_path, t_path *goal, t_vector start)
{
	t_path	*new;

	if (!goal)
		return (NULL);
	if (goal->pos.x == start.x && goal->pos.y == start.y)
	{
		new = NULL;
		add_path(goal->pos, goal->from, &new);
		return (new);
	}
	new = get_good_path(full_path, get_specific_path(full_path, goal->from),
			start);
	add_path(goal->pos, goal->from, &new);
	return (new);
}

t_vector	get_diff(t_path **current)
{
	static t_vector	diff = (t_vector){.x = 0, .y = 0};
	static int		count = 0;

	if (diff.x == 0 && diff.y == 0)
		diff.x = 1;
	else if (diff.x == 1)
		diff.x = -1;
	else if (diff.x == -1)
	{
		diff.x = 0;
		diff.y = 1;
	}
	else if (diff.y == 1)
		diff.y = -1;
	else if (diff.y == -1)
	{
		diff.y = 0;
	}
	count++;
	if (count > 4)
	{
		*current = (*current)->next;
		count = 0;
	}
	return (diff);
}

t_bool	check_goal(t_path **current, t_data *data, t_path *full_path,
	t_vector goal)
{
	t_vector	diff;

	diff = get_diff(current);
	if (!*current)
		return (true);
	if (good_path(data, vec((*current)->pos.x + diff.x,
				(*current)->pos.y + diff.y), full_path))
		add_path(vec((*current)->pos.x + diff.x, (*current)->pos.y + diff.y),
			(*current)->pos, &full_path);
	if ((*current)->pos.x + diff.x == goal.x
		&& (*current)->pos.y + diff.y == goal.y)
		return (true);
	return (false);
}

t_bool	adjacent(t_vector goal, t_vector pos)
{
	if (ft_abs(goal.x - pos.x) <= 1 && ft_abs(goal.y - pos.y) <= 1)
		return (true);
	return (false);
}

t_path	*get_path(t_data *data, t_vector start, t_vector goal, t_bool closest)
{
	t_path		*path;
	t_path		*res;
	t_path		*current;
	int			i;

	i = 0;
	if ((!closest && !is_empty_cell(data, goal)))
		return (NULL);
	path = NULL;
	add_path(start, start, &path);
	current = path;
	while (current && i < 1000
		&& ((!closest && (current->pos.x != goal.x || current->pos.y != goal.y))
			|| (closest && !adjacent(goal, current->pos))))
	{
		check_goal(&current, data, path, goal);
		i++;
	}
	res = NULL;
	if (current && ((!closest && current->pos.x == goal.x \
	&& current->pos.y == goal.y) || (closest && adjacent(goal, current->pos))))
		res = get_good_path(path, current, start);
	free_path(&path);
	return (res);
}
