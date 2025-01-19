/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 22:52:00 by gmassoni          #+#    #+#             */
/*   Updated: 2025/01/15 20:14:45 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	change_state(t_cell	*door)
{
	if (door->type == DOOR)
	{
		if (door->status == OPENING)
		{
			door->timer -= 0.1;
			if (door->timer <= 0)
				door->status = OPEN;
		}
		if (door->status == CLOSING)
		{
			door->timer += 0.1;
			if (door->timer >= 1)
				door->status = CLOSE;
		}
	}
}

void	update_doors(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->current_map->size.x)
	{
		j = -1;
		while (++j < data->current_map->size.y)
			change_state(&data->current_map->arr[i][j]);
	}
}

void	open_door(t_data *data)
{
	int			tmp;
	t_vector	pos;
	t_cell		*c;

	tmp = data->player.angle / (M_PI / 2);
	c = NULL;
	pos = data->player.pos;
	if (data->player.possession)
		pos = data->player.possession->pos;
	if ((tmp == 0 || tmp == 4)
		&& data->current_map->arr[pos.x + 1][pos.y].type == DOOR)
		c = &data->current_map->arr[pos.x + 1][pos.y];
	else if (tmp == 3 && data->current_map->arr[pos.x][pos.y - 1].type == DOOR)
		c = &data->current_map->arr[pos.x][pos.y - 1];
	else if (tmp == 2 && data->current_map->arr[pos.x - 1][pos.y].type == DOOR)
		c = &data->current_map->arr[pos.x - 1][pos.y];
	else if (tmp == 1 && data->current_map->arr[pos.x][pos.y + 1].type == DOOR)
		c = &data->current_map->arr[pos.x][pos.y + 1];
	if (!c)
		return ;
	if (c->status == OPEN)
		c->status = CLOSING;
	if (c->status == CLOSE)
		c->status = OPENING;
}
