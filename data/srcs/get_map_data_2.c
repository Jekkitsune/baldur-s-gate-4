/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 02:45:59 by fparis            #+#    #+#             */
/*   Updated: 2025/01/28 22:47:37 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*map_param(char **splited, char *name);
t_bool	add_to_inventory(t_data *data, t_entity *taker, t_entity *taken,
		t_bool no_equip);
void	add_entity_map_behavior(t_data *data, t_entity *entity, char **splited);

void	set_entity_map_properties(t_data *data, t_entity *entity, char *prop)
{
	char	**splited;
	int		i;

	splited = ft_split(prop, ',');
	if (!splited)
		return ;
	i = 0;
	while (splited[i])
	{
		entity->sheet.properties |= get_property(data, splited[i]);
		i++;
	}
	ft_free_tab(splited);
}

void	set_entity_map_inventory(t_data *data, t_entity *entity, char *inv)
{
	char		**splited;
	int			i;
	t_bool		no_equip;
	t_entity	*item;

	splited = ft_split(inv, ',');
	if (!splited)
		return ;
	i = 0;
	no_equip = entity->sheet.properties & shop_keeper;
	while (splited[i])
	{
		item = spawn_entity(data, get_prefab(data, splited[i]), entity->pos,
			ft_strdup(splited[i]));
		if (item && item->sheet.type == gold && splited[i + 1])
			item->sheet.price = ft_atoi(splited[++i]);
		add_to_inventory(data, entity, item, no_equip);
		i++;
	}
	ft_free_tab(splited);
}

void	set_team(t_entity *entity, char **splited)
{
	char		*current;

	current = map_param(splited, "TEAM");
	if (current)
	{
		entity->sheet.default_team = ft_atoi(current);
		entity->sheet.team = entity->sheet.default_team;
	}
}

t_entity	*set_entity_map_data(t_data *data, char **splited, t_entity *prefab,
		t_vector pos)
{
	char		*current;
	char		*name;
	t_entity	*entity;

	name = prefab->sheet.name;
	current = map_param(splited, "NAME");
	if (current)
		name = current;
	entity = spawn_entity(data, prefab, pos, ft_strdup(name));
	if (!entity)
		return (NULL);
	current = map_param(splited, "LVL");
	if (current)
		entity->sheet.level = ft_atoi(current);
	set_team(entity, splited);
	add_entity_map_behavior(data, entity, splited);
	current = map_param(splited, "PROPERTIES");
	if (current)
		set_entity_map_properties(data, entity, current);
	current = map_param(splited, "INVENTORY");
	if (current)
		set_entity_map_inventory(data, entity, current);
	set_entity_dialog(entity, map_param(splited, "DIALOG"));
	return (entity);
}

void	set_entity_map(t_data *data, char **splited)
{
	t_vector	pos;
	char		*current;
	char		**tmp_splited;
	t_entity	*prefab;
	t_entity	*entity;

	current = map_param(splited, "POS");
	if (!current)
		return ;
	tmp_splited = ft_split(current, ',');
	if (!tmp_splited)
		return ;
	pos.x = ft_atoi(tmp_splited[0]);
	pos.y = ft_atoi(tmp_splited[1]);
	ft_free_tab(tmp_splited);
	if (!in_bound(data->current_map, pos))
		return ;
	prefab = get_prefab(data, map_param(splited, "PREFAB"));
	if (!prefab)
		return ;
	entity = set_entity_map_data(data, splited, prefab, pos);
	if (entity)
		long_rest(data, entity);
}
