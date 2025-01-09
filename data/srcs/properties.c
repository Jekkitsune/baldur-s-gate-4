/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:01:11 by fparis            #+#    #+#             */
/*   Updated: 2025/01/07 07:15:44 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*stat_name_nb(char *name, int nb)
{
	char	*itoa_res;
	char	*res;

	itoa_res = ft_itoa(nb);
	if (!itoa_res)
		return (NULL);
	res = ft_vajoin(name, ": ", itoa_res, "  ", NULL);
	free(itoa_res);
	return (res);
}

void	show_check_properties(t_data *data, t_entity *entity, t_vector pos)
{
	t_strput	*to_put;
	char		*info;
	int			i;

	info = NULL;
	i = 0;
	while (i < NB_PROPERTIES)
	{
		if (entity->sheet.properties & (1 << i))
			add_to_str(&info, ft_strjoin((char *)PROPERTIES_TAB[i], "  "));
		i++;
	}
	pos.x = data->win_size.x / 8;
	pos.y += data->button_scale_size;
	to_put = strput(info, pos, (float)data->button_scale_size / 1.5, 0xFFFFFFFF);
	screen_string_put(data, to_put, 3);
	if (entity->sheet.description)
	{
		pos.y += data->button_scale_size;
		info = ft_vajoin("\"", entity->sheet.description, "\"", NULL);
		to_put = strput(info, pos, (float)data->button_scale_size / 1.5, 0xFFFFFFFF);
		screen_string_put(data, to_put, 3);
	}
}

void	show_check_stats(t_data *data, t_entity *entity, t_vector pos)
{
	t_strput	*to_put;
	char		*info;

	info = NULL;
	add_to_str(&info, stat_name_nb("STR", entity->sheet.stats[STR]));
	add_to_str(&info, stat_name_nb("STR", entity->sheet.stats[DEX]));
	add_to_str(&info, stat_name_nb("STR", entity->sheet.stats[CON]));
	add_to_str(&info, stat_name_nb("STR", entity->sheet.stats[WIS]));
	add_to_str(&info, stat_name_nb("STR", entity->sheet.stats[CHA]));
	pos.x = data->win_size.x / 8;
	pos.y += data->button_scale_size;
	to_put = strput(info, pos, (float)data->button_scale_size / 1.5, 0xFFFFFFFF);
	screen_string_put(data, to_put, 3);
	show_check_properties(data, entity, pos);
}

void	show_check_info(t_data *data, t_entity *entity)
{
	t_strput	*to_put;
	t_sheet		*sheet;
	char		*info;
	t_vector	pos;

	sheet = &entity->sheet;
	pos = vec(data->win_size.x / 6, data->win_size.y / 3);
	info = NULL;
	add_to_str(&info, ft_vajoin("name: ", sheet->name, "  ", NULL));
	if (sheet->class)
		add_to_str(&info, ft_vajoin("class: ", sheet->class->name, "  ", NULL));
	add_to_str(&info, stat_name_nb("AC", sheet->ac));
	add_to_str(&info, stat_name_nb("speed", sheet->speed));
	add_to_str(&info, stat_name_nb("weight", sheet->weight));
	add_to_str(&info, stat_name_nb("carry", sheet->carry));
	to_put = strput(info, pos, (float)data->button_scale_size / 1.5, 0xFFFFFFFF);
	screen_string_put(data, to_put, 3);
	pos.y += data->button_scale_size;
	info = NULL;
	add_to_str(&info, stat_name_nb("level", sheet->level));
	add_to_str(&info, stat_name_nb("PB", sheet->pb));
	add_to_str(&info, stat_name_nb("atk bonus", sheet->atk_bonus));
	add_to_str(&info, stat_name_nb("spell bonus", sheet->spell_bonus));
	add_to_str(&info, stat_name_nb("spell DC", sheet->spell_dc));
	to_put = strput(info, pos, (float)data->button_scale_size / 1.5, 0xFFFFFFFF);
	screen_string_put(data, to_put, 3);
	show_check_stats(data, entity, pos);
}

void	check_select(void *data_param, void *entity_param, t_spellinfo spell)
{
	t_data		*data;
	t_entity	*entity;

	data = data_param;
	entity = entity_param;
	if (!data->player.arrow)
		select_target(data);
	if (!confirm(data->player.active_button)
		|| !check_dist_obstacle(data, entity, spell.range, spell.visible_target))
		return ;
	spell.target = cycle_entity_cell(data, 0);
	if (!spell.target)
		return ;
	confirm(data->player.active_button);
	show_check_info(data, spell.target);
}

void	init_check_button(t_data *data, t_button *button)
{
	button->spellinfo.radius = 0;
	button->spellinfo.range = 30;
	button->spellinfo.anim = NULL;
	button->spellinfo.timer = 0;
	button->spellinfo.visible_target = false;
	button->spellinfo.target_self = true;
	button->spellinfo.type = 0;
	button->img = get_tex(data, "check_button");
	button->func = check_select;
	button->spellinfo.effect = NULL;
	button->name = "Check";
	button->description = "Get information from selected entity";
}

t_bool	check_properties(t_property properties, t_property check)
{
	return ((properties & check) == check);
}
