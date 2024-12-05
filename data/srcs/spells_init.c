/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spells_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 03:47:16 by fparis            #+#    #+#             */
/*   Updated: 2024/12/04 18:17:20 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_spells_prefab(t_data *data)
{
	add_prefab(data, get_prefab_data(data, "selector"), ft_strjoin("selector", ""));
	add_prefab(data, get_prefab_data(data, "explosion"), ft_strjoin("explosion", ""));
	data->prefab_tab[data->nb_prefab - 1]->size_scale = 2;
	data->prefab_tab[data->nb_prefab - 1]->anim[get_anim_index(data->prefab_tab[data->nb_prefab - 1], "idle")].interval = 6;
}
