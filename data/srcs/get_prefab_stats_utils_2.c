/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prefab_stats_utils_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:48:47 by fparis            #+#    #+#             */
/*   Updated: 2025/01/22 01:19:32 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	prefab_size(t_entity *entity, char **splited)
{
	char	**splited_number;
	float	res;
	float	tmp;

	if (!ft_strncmp(splited[0], "SIZE",
			ft_strlen("SIZE")))
	{
		splited_number = ft_split(splited[1], '.');
		if (splited_number && splited_number[0] && splited_number[1])
		{
			res = ft_atoi(splited_number[0]);
			tmp = ft_atoi(splited_number[1]);
			while (tmp > 1)
				tmp /= 10.0;
			res += tmp;
			entity->size_scale = res;
		}
		ft_free_tab(splited_number);
		return (true);
	}
	return (false);
}

t_bool	set_default_actions(t_data *data, t_sheet *s, char **splited)
{
	int		i;
	void	(*button_init)(t_data *data, t_button *button);

	if (!ft_strncmp(splited[0], "ACTION", ft_strlen("ACTION")))
	{
		i = 0;
		while (i < NB_BUTTON && splited[i + 1] && ft_strcmp(splited[i + 1], \
"\n"))
		{
			button_init = get_button(data, splited[i + 1]);
			if (button_init)
				button_init(data, &s->buttons[i]);
			i++;
		}
		return (true);
	}
	return (false);
}
