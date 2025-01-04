/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 22:00:32 by fparis            #+#    #+#             */
/*   Updated: 2024/12/22 02:11:26 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_path(t_path *path)
{
	if (!path)
		return ;
	free_path(path->next);
	free(path);
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
	if (!in_bound(data->current_map, pos) || data->current_map->arr[pos.x][pos.y].type == WALL || get_specific_path(path, pos))
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
		diff.x = 1;
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

t_path	*get_path(t_data *data, t_vector start, t_vector goal)
{
	t_path		*path;
	t_path		*res;
	t_path		*current;
	int			i;

	i = 0;
	if (!in_bound(data->current_map, goal) || data->current_map->arr[start.x][start.y].type == WALL
		|| !in_bound(data->current_map, start) || data->current_map->arr[goal.x][goal.y].type == WALL)
		return (NULL);
	path = NULL;
	add_path(start, start, &path);
	current = path;
	//printf("start: %d %d (%d %d)\n", current->pos.x, current->pos.y, current->from.x, current->from.y);
	while (current && (current->pos.x != goal.x || current->pos.y != goal.y) && i < 1000)
	{
		check_goal(&current, data, path, goal);
		i++;
	}
	// printf("\n");
	// print_path(path);
	// printf("%p\n", current);
	res = NULL;
	if (current && current->pos.x == goal.x && current->pos.y == goal.y)
		res = get_good_path(path, current, start);
	free_path(path);
	return (res);
}
