/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:58:27 by fparis            #+#    #+#             */
/*   Updated: 2025/01/31 12:55:55 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	show_check_stats(t_data *data, t_sheet *sheet, t_vector pos);
void	show_first_info(t_data *data, t_sheet *sheet, t_vector pos);
void	show_second_info(t_data *data, t_sheet *sheet, t_vector pos);

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
	t_property	i;

	info = NULL;
	i = -1;
	while (++i < NB_PROPERTIES)
	{
		if ((long)entity->sheet.properties & (long)((long)1 << i))
			add_to_str(&info, ft_strjoin(data->properties_tab[i], "  "));
	}
	to_put = strput(info, pos, (float)data->button_scale_size
			/ 1.5, 0xFFFFFFFF);
	if (to_put)
		to_put->bg = 0xAA000000;
	screen_string_put(data, to_put, 3);
	if (entity->sheet.description)
	{
		pos.y += data->button_scale_size;
		info = ft_vajoin("\"", entity->sheet.description, "\"", NULL);
		to_put = strput(info, pos, (float)data->button_scale_size
				/ 1.5, 0xFFFFFFFF);
		to_put->bg = 0xAA000000;
		screen_string_put(data, to_put, 3);
	}
}

void	show_check_info(t_data *data, t_entity *entity)
{
	t_sheet		*sheet;
	t_vector	pos;

	sheet = &entity->sheet;
	pos = vec(data->win_size.x / 6, data->win_size.y / 3);
	show_first_info(data, sheet, pos);
	pos.y += data->button_scale_size;
	show_second_info(data, sheet, pos);
	pos.x = data->win_size.x / 8;
	pos.y += data->button_scale_size;
	show_check_stats(data, sheet, pos);
	pos.x = data->win_size.x / 8;
	pos.y += data->button_scale_size;
	show_check_properties(data, entity, pos);
}

void	check_select(void *data_param, void *entity_param, t_spellinfo spell)
{
	t_data		*data;
	t_entity	*entity;

	data = data_param;
	entity = entity_param;
	if (!data->player.arrow)
		select_target(data);
	if (!confirm(data->player.active_button) \
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
	button->spellinfo.type = check_type;
	button->img = get_tex(data, "check_button");
	button->func = check_select;
	button->spellinfo.effect = NULL;
	button->name = "Check";
	button->description = "Get information from selected entity";
}
