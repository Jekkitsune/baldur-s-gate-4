/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prefab_stats_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:18:24 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 23:14:05 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_type	get_type(char *type)
{
	if (!ft_strcmp(type, "weapon_1"))
		return (weapon_1);
	if (!ft_strcmp(type, "weapon_2"))
		return (weapon_2);
	if (!ft_strcmp(type, "head"))
		return (head);
	if (!ft_strcmp(type, "body"))
		return (body);
	if (!ft_strcmp(type, "hands"))
		return (hands);
	if (!ft_strcmp(type, "feet"))
		return (feet);
	if (!ft_strcmp(type, "living"))
		return (living);
	if (!ft_strcmp(type, "object"))
		return (object);
	if (!ft_strcmp(type, "consumable"))
		return (consumable);
	if (!ft_strcmp(type, "gold"))
		return (gold);
	if (!ft_strcmp(type, "tavern"))
		return (tavern);
	return (object);
}

char	**get_next_stat(int fd)
{
	char	*line;
	char	**splited;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	splited = ft_split(line, ':');
	free(line);
	if (!splited || !splited[0] || !splited[1])
	{
		ft_free_tab(splited);
		finish_gnl(fd);
		return (NULL);
	}
	return (splited);
}

t_bool	set_stat(int *stat, char *compare, char **splited)
{
	if (!splited || !splited[0] || !splited[1])
		return (false);
	if (!ft_strcmp(splited[0], compare))
	{
		*stat = ft_atoi(splited[1]);
		return (true);
	}
	return (false);
}

t_bool	set_multiple(t_sheet *s, char **splited)
{
	int	i;

	if (!ft_strncmp(splited[0], "DICE", ft_strlen("DICE")) && splited[2])
	{
		i = dice_i(ft_atoi(splited[1]));
		if (i != -1)
			s->dice_dmg[i] = ft_atoi(splited[2]);
		return (true);
	}
	else if (!ft_strncmp(splited[0], "SPELLSLOT",
			ft_strlen("SPELLSLOT")) && splited[2])
	{
		i = ft_atoi(splited[1]) - 1;
		if (i >= 0 && i < SPELL_MAX_LV)
			s->spell_slot[i] = ft_atoi(splited[2]);
		return (true);
	}
	return (false);
}

void	remove_endl(char **splited)
{
	int	i;
	int	i2;

	if (!splited || !splited[0] || !splited[1])
		return ;
	i = 0;
	while (splited[i + 1])
		i++;
	i2 = 0;
	while (splited[i][i2])
	{
		if (splited[i][i2] == '\n')
			splited[i][i2] = '\0';
		i2++;
	}
}
