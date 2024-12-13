/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:45:04 by fparis            #+#    #+#             */
/*   Updated: 2024/12/07 20:48:22 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	confirm(t_button *pushed)
{
	static t_button	*check = NULL;

	if (pushed && pushed == check)
		return (true);
	check = pushed;
	return (false);
}

t_entity	*create_selector(t_data *data)
{
	t_entity	*res;

	res = spawn_entity(data, get_prefab(data, "selector"), data->player.pos, ft_strjoin("selector", ""));
	change_anim(res, "idle");
	if (!res)
		return (NULL);
	possess_control(res, true);
	if (data->player.possession)
		teleport_entity(data, res, data->player.possession->pos, data->player.possession->offset);
	return (res);
}

void	remove_selector(t_data *data)
{
	confirm(NULL);
	if (data->player.active_button)
	{
		data->player.active_button->active = false;
		data->player.active_button = NULL;
	}
	if (data->player.arrow)
		destroy_entity(data, data->player.arrow);
}

void	select_target(t_data *data)
{
	if (!data->player.arrow && in_bound(*data->current_map, data->player.pos))
		data->player.arrow = create_selector(data);
}

t_bool	check_dist_obstacle(t_data *data, t_entity *entity, int dist, t_bool visible_target)
{
	if (!entity || !data->player.arrow)
		return (false);
	if (get_dist(entity->pos, data->player.arrow->pos) > dist || (visible_target && has_obstacle(data)))
	{
		if (data->player.arrow->current_anim
			&& ft_strcmp(data->player.arrow->current_anim->name, "death"))
				change_anim(data->player.arrow, "dead");
		return (false);
	}
	else if (data->player.arrow->current_anim
		&& ft_strcmp(data->player.arrow->current_anim->name, "idle"))
			change_anim(data->player.arrow, "idle");
	return (true);
}

void	exemple_action(void *data_param, void *entity_param, t_spellinfo spell)
{
	t_data		*data;
	t_entity	*entity;
	t_vector	pos;

	data = data_param;
	entity = entity_param;
	if (!data->player.arrow)
		select_target(data);
	if (!confirm(data->player.active_button))
		return ;
	pos = data->player.arrow->pos;
	remove_selector(data);

	//apres faire ce que fait l'action
	printf("POS: %d %d\n", pos.x, pos.y);
}
