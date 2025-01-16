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

void	update_doors(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->current_map->size.x)
	{
		j = 0;
		while (j < data->current_map->size.y)
		{
			if (data->current_map->arr[i][j].type == DOOR)
			{
				if (data->current_map->arr[i][j].status == OPENING)
				{
					data->current_map->arr[i][j].timer -= 0.1;
					if (data->current_map->arr[i][j].timer <= 0)
						data->current_map->arr[i][j].status = OPEN;
				}
				if (data->current_map->arr[i][j].status == CLOSING)
				{
					data->current_map->arr[i][j].timer += 0.1;
					if (data->current_map->arr[i][j].timer >= 1)
						data->current_map->arr[i][j].status = CLOSE;
				}
			}
			j++;
		}
		i++;
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
	if ((tmp == 0 || tmp == 4) && data->current_map->arr[pos.x + 1][pos.y].type == DOOR)
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
