/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prefab_stats.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:36:56 by fparis            #+#    #+#             */
/*   Updated: 2025/01/15 17:24:54 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	remove_endl(char **splited);
t_bool	set_multiple(t_sheet *s, char **splited);
t_bool	set_stat(int *stat, char *compare, char **splited);
char	**get_next_stat(int fd);
t_type	get_type(char *type);
void	finish_gnl(int fd);

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

	if (!splited || !splited[0] || !splited[1]
		|| ft_strncmp(splited[0], "PROPERTIES", ft_strlen("PROPERTIES")))
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
		if (!set_basic_stats(s, splited) && !set_game_stat(s, splited)
			&& !set_specific(data, s, splited))
			set_properties(data, s, splited);
		ft_free_tab(splited);
		splited = get_next_stat(fd);
	}
	close(fd);
	s->hp = s->max_hp;
	if (!s->level)
		s->level = 1;
}
