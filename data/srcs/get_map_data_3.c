/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 04:59:22 by fparis            #+#    #+#             */
/*   Updated: 2025/01/24 06:46:23 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*map_param(char **splited, char *name);

void	cell_loop_range(t_vector *start, t_vector *end)
{
	int	tmp;

	if (start->x > end->x)
	{
		tmp = start->x;
		start->x = end->x;
		end->x = tmp;
	}
	if (start->y > end->y)
	{
		tmp = start->y;
		start->y = end->y;
		end->y = tmp;
	}
}

void	get_cell_pos(char **splited_pos, t_vector *start, t_vector *end)
{
	start->x = -1;
	start->y = -1;
	end->x = start->x;
	end->y = start->y;
	if (!splited_pos[0] || !splited_pos[1])
		return ;
	start->x = ft_atoi(splited_pos[0]);
	start->y = ft_atoi(splited_pos[1]);
	if (!splited_pos[2] || !splited_pos[3])
	{
		end->x = start->x;
		end->y = start->y;
		return ;
	}
	end->x = ft_atoi(splited_pos[2]);
	end->y = ft_atoi(splited_pos[3]);
	cell_loop_range(start, end);
}

void	(*get_behavior(char *name))(void *data, void *entity)
{
	if (!name)
		return (NULL);
	if (!ft_strcmp(name, "base_aggro"))
		return (base_aggro);
	return (NULL);
}

void	add_entity_map_behavior(t_data *data, t_entity *entity, char **splited)
{
	entity->sheet.wander_ia = get_behavior(map_param(splited, "BEHAVIOR"));
	if (entity->sheet.wander_ia)
	{
		entity->sheet.fight_ia = martial_ia;
		add_active(data, entity, entity->sheet.wander_ia);
	}
}
