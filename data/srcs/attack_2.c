/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 05:18:42 by fparis            #+#    #+#             */
/*   Updated: 2025/01/28 23:02:11 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_hunter_mark(t_data *data, t_spellinfo *spell);

void	atk_dmg(t_data *data, t_spellinfo *spell, int atk, int rand_res)
{
	if (!spell->target || !spell->caster)
		return ;
	if (atk >= spell->target->sheet.ac)
	{
		show_info(data, "%s hit (%d) %s (%d)", spell->caster->sheet.name, atk,
			spell->target->sheet.name, spell->target->sheet.ac);
		if (spell->target->sheet.properties & paralyzed
			&& get_dist(spell->caster->pos, spell->target->pos) < 2)
			spell->nb *= 2;
		printf("rolled dmg: %d\n", rand_res);
		if (spell->caster->sheet.properties & sharp_shooter)
			spell->nb += 10;
		damage(data, spell->target, spell->nb);
		if (spell->target->sheet.properties & hellish_rebuke)
			hellish_rebuke_effect(data, spell->target, spell->caster);
		if (spell->target->sheet.properties & hunter_marked)
			check_hunter_mark(data, spell);
	}
	else
		show_info(data, "%s missed (%d) %s (%d)", spell->caster->sheet.name,
			atk, spell->target->sheet.name, spell->target->sheet.ac);
}

int	advantage(t_data *data, t_entity *caster, t_entity *target)
{
	int	advantage;

	advantage = 0;
	if (!target || !caster || target == caster)
		return (0);
	if ((!(caster->sheet.properties & true_sight)
		&& (caster->sheet.properties & blinded
		|| target->sheet.properties & invisible))
		|| target->sheet.properties & dodge
		|| (!(caster->sheet.properties & close_shooter)
		&& caster->sheet.properties & range
		&& get_dist(caster->pos, target->pos) < 2))
		advantage -= 1;
	else if ((!(target->sheet.properties & true_sight)
		&& target->sheet.properties & blinded)
		|| caster->sheet.properties & invisible)
		advantage += 1;
	if (target->sheet.properties & reckless_atk
		|| caster->sheet.properties & reckless_atk
		|| target->sheet.properties & (restrained | paralyzed | hypnotized
		| stunned)
		|| (is_menaced(data, target, caster)
		&& caster->sheet.properties & menaced_advantage))
		advantage += 1;
	return (advantage);
}

int	get_crit_nb(t_entity *caster)
{
	int	res;

	res = 20;
	if (!caster)
		return (res);
	if (caster->sheet.properties & crit_1)
		res -= 1;
	if ((caster->sheet.properties & crit_3))
		res -= 3;
	return (res);
}

int	roll_atk(t_data *data, t_spellinfo *spell, int atk_bonus)
{
	int	atk;
	int	has_advantage;

	atk = roll_one(20, 1);
	has_advantage = advantage(data, spell->caster, spell->target);
	if (has_advantage == 1)
		atk = ft_max(atk, roll_one(20, 1));
	else if (has_advantage == -1)
		atk = ft_min(atk, roll_one(20, 1));
	if (atk >= get_crit_nb(spell->caster))
	{
		show_info(data, "%s got a critical hit!", spell->caster->sheet.name);
		spell->nb *= 2;
		atk = 200;
	}
	if (atk <= 1)
	{
		show_info(data, "%s got a critical fail...", spell->caster->sheet.name);
		atk = -200;
	}
	atk += atk_bonus;
	if (spell->caster->sheet.properties & sharp_shooter)
		atk -= 5;
	return (atk);
}

t_bool	saving_throw(t_data *data, t_entity *entity, int stat, int dc)
{
	int	result;
	int	rand_result;

	rand_result = roll_one(20, 1);
	result = rand_result + entity->sheet.saving[stat];
	if (result >= dc)
	{
		show_info(data, "%s succeeded (%d + %d) a %s saving throw of dc (%d)", \
		entity->sheet.name, rand_result, entity->sheet.saving[stat], \
		stat_to_str(stat), dc);
		return (true);
	}
	show_info(data, "%s failed (%d + %d) a %s saving throw of dc (%d)", \
	entity->sheet.name, rand_result, entity->sheet.saving[stat], \
	stat_to_str(stat), dc);
	return (false);
}
