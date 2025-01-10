/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prefab_stats.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:36:56 by fparis            #+#    #+#             */
/*   Updated: 2025/01/10 14:32:06 by fparis           ###   ########.fr       */
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
	return (object);
}

void	finish_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
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
	if (!ft_strncmp(splited[0], compare, ft_strlen(compare)))
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
	else if (!ft_strncmp(splited[0], "SPELLSLOT", ft_strlen("SPELLSLOT")) && splited[2])
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

t_bool	set_specific(t_data *data, t_sheet *s, char **splited)
{
	if (!splited || !splited[0] || !splited[1])
		return (false);
	if (!ft_strncmp(splited[0], "CLASS", ft_strlen("CLASS")))
	{
		remove_endl(splited);
		s->class = get_class(data->class_lst, splited[1]);
		return (true);
	}
	else if (!ft_strncmp(splited[0], "DESCRIPTION", ft_strlen("DESCRIPTION")))
	{
		remove_endl(splited);
		s->description = ft_strdup(splited[1]);
		return (true);
	}
	else if (!ft_strncmp(splited[0], "TYPE", ft_strlen("TYPE")))
	{
		remove_endl(splited);
		s->type = get_type(splited[1]);
		return (true);
	}
	else
		return (set_multiple(s, splited));
}

t_bool	set_basic_stats(t_sheet *s, char **splited)
{
	if (set_stat(&s->stats[STR], "STR", splited))
		return (true);
	if (set_stat(&s->stats[DEX], "DEX", splited))
		return (true);
	if (set_stat(&s->stats[CON], "CON", splited))
		return (true);
	if (set_stat(&s->stats[INT], "INT", splited))
		return (true);
	if (set_stat(&s->stats[WIS], "WIS", splited))
		return (true);
	if (set_stat(&s->stats[CHA], "CHA", splited))
		return (true);
	if (set_stat(&s->saving[STR], "SAVE_STR", splited))
		return (true);
	if (set_stat(&s->saving[DEX], "SAVE_DEX", splited))
		return (true);
	if (set_stat(&s->saving[CON], "SAVE_CON", splited))
		return (true);
	if (set_stat(&s->saving[INT], "SAVE_INT", splited))
		return (true);
	if (set_stat(&s->saving[WIS], "SAVE_WIS", splited))
		return (true);
	if (set_stat(&s->saving[CHA], "SAVE_CHA", splited))
		return (true);
	return (false);
}

t_bool	set_game_stat(t_sheet *s, char **splited)
{
	if (set_stat(&s->max_hp, "HP", splited))
		return (true);
	if (set_stat(&s->pb, "PB", splited))
		return (true);
	if (set_stat(&s->ac, "AC", splited))
		return (true);
	if (set_stat(&s->nb_attack, "NB ATK", splited))
		return (true);
	if (set_stat(&s->atk_bonus, "ATK BONUS", splited))
		return (true);
	if (set_stat(&s->spell_bonus, "SPELL BONUS", splited))
		return (true);
	if (set_stat(&s->spell_dc, "SPELL DC", splited))
		return (true);
	if (set_stat(&s->weight, "WEIGHT", splited))
		return (true);
	if (set_stat(&s->carry, "CARRY", splited))
		return (true);
	if (set_stat(&s->speed, "SPEED", splited))
		return (true);
	return (false);
}

t_bool	set_properties(t_data *data, t_sheet *s, char **splited)
{
	int	i;

	if (!splited || !splited[0] || !splited[1] || ft_strncmp(splited[0], "PROPERTIES", ft_strlen("PROPERTIES")))
		return (false);
	remove_endl(splited);
	i = 1;
	while (splited[i])
	{
		s->properties |= get_property(data, splited[i]);
		i++;
	}
	return (true);
}

void	get_prefab_stat(t_data *data, t_entity *prefab, char *directory)
{
	int		fd;
	char	*path;
	char	**splited;
	t_sheet	*s;

	s = &prefab->sheet;
	path = ft_vajoin(directory, "/", "stats", NULL);
	fd = open(path, O_RDONLY);
	free(path);
	if (fd == -1)
		return ;
	splited = get_next_stat(fd);
	while (splited)
	{
		if (!set_basic_stats(s, splited) && !set_game_stat(s, splited) && !set_specific(data, s, splited))
			set_properties(data, s, splited);
		ft_free_tab(splited);
		splited = get_next_stat(fd);
	}
	close(fd);
	s->hp = s->max_hp;
	if (!s->level)
		s->level = 1;
}
