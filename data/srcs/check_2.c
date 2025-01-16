/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:59:32 by fparis            #+#    #+#             */
/*   Updated: 2025/01/16 21:07:45 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*stat_name_nb(char *name, int nb);

void	show_check_stats(t_data *data, t_sheet *sheet, t_vector pos)
{
	t_strput	*to_put;
	char		*info;

	info = NULL;
	add_to_str(&info, stat_name_nb("STR", sheet->stats[STR]));
	add_to_str(&info, stat_name_nb("DEX", sheet->stats[DEX]));
	add_to_str(&info, stat_name_nb("CON", sheet->stats[CON]));
	add_to_str(&info, stat_name_nb("INT", sheet->stats[INT]));
	add_to_str(&info, stat_name_nb("WIS", sheet->stats[WIS]));
	add_to_str(&info, stat_name_nb("CHA", sheet->stats[CHA]));
	to_put = strput(info, pos, (float)data->button_scale_size
			/ 1.5, 0xFFFFFFFF);
	screen_string_put(data, to_put, 3);
}

void	show_first_info(t_data *data, t_sheet *sheet, t_vector pos)
{
	char		*info;
	t_strput	*to_put;

	info = NULL;
	add_to_str(&info, ft_vajoin("name: ", sheet->name, "  ", NULL));
	if (sheet->class)
		add_to_str(&info, ft_vajoin("class: ", sheet->class->name, "  ", NULL));
	add_to_str(&info, stat_name_nb("AC", sheet->ac));
	add_to_str(&info, stat_name_nb("speed", sheet->speed));
	add_to_str(&info, stat_name_nb("weight", sheet->weight));
	add_to_str(&info, stat_name_nb("carry", sheet->carry));
	to_put = strput(info, pos, (float)data->button_scale_size
			/ 1.5, 0xFFFFFFFF);
	screen_string_put(data, to_put, 3);
}

void	show_second_info(t_data *data, t_sheet *sheet,
	t_vector pos)
{
	char		*info;
	t_strput	*to_put;

	info = NULL;
	add_to_str(&info, stat_name_nb("level", sheet->level));
	add_to_str(&info, stat_name_nb("PB", sheet->pb));
	add_to_str(&info, stat_name_nb("atk bonus", sheet->atk_bonus));
	add_to_str(&info, stat_name_nb("spell bonus", sheet->spell_bonus));
	add_to_str(&info, stat_name_nb("spell DC", sheet->spell_dc));
	to_put = strput(info, pos, (float)data->button_scale_size
			/ 1.5, 0xFFFFFFFF);
	screen_string_put(data, to_put, 3);
}
