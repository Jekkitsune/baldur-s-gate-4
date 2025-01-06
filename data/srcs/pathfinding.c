/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 22:00:32 by fparis            #+#    #+#             */
/*   Updated: 2025/01/06 14:12:33 by fparis           ###   ########.fr       */
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
	new = get_good_path(full_path, get_specific_path(full_path, goal->from), start);
	add_path(goal->pos, goal->from, &new);
	return (new);
}

t_bool	check_goal(t_path **current, t_data *data, t_path *full_path, t_vector goal)
{
	static t_vector	diff = (t_vector){.x = 0, .y = 0};

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
		*current = (*current)->next;
	}
	//printf("try: %d %d (%d %d)\n", (*current)->pos.x + diff.x, (*current)->pos.y + diff.y, (*current)->pos.x, (*current)->pos.y);
	if (!*current)
		return (true);
	if (good_path(data, vec((*current)->pos.x + diff.x, (*current)->pos.y + diff.y), full_path))
		add_path(vec((*current)->pos.x + diff.x, (*current)->pos.y + diff.y), (*current)->pos, &full_path);
	if ((*current)->pos.x + diff.x == goal.x && (*current)->pos.y + diff.y == goal.y)
		return (true);
	return (false);
}

void	print_path(t_path *path)
{
	if (!path)
		printf("NONE");
	while (path)
	{
		printf("%d %d -> ", path->pos.x, path->pos.y);
		path = path->next;
	}
	printf("\n");
}

t_bool	is_adjacent(t_vector goal, t_vector pos)
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
	//printf("start: %d %d end: %d %d\n", start.x, start.y, goal.x, goal.y);
	while (current && i < 1000
		&& ((!closest && (current->pos.x != goal.x || current->pos.y != goal.y))
		|| (closest && !is_adjacent(goal, current->pos))))
	{
		check_goal(&current, data, path, goal);
		i++;
	}
	// printf("\n");
	// print_path(path);
	// printf("%p\n", current);
	res = NULL;
	if (current && ((!closest && current->pos.x == goal.x && current->pos.y == goal.y)
		|| (closest && is_adjacent(goal, current->pos))))
		res = get_good_path(path, current, start);
	free_path(&path);
	return (res);
}
