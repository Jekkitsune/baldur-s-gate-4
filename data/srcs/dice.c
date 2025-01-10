/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dice.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:54:31 by fparis            #+#    #+#             */
/*   Updated: 2025/01/10 20:07:36 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_dice_average(t_dice dice)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (i < NB_DICE)
	{
		res += (dice[i] * index_dice(i) + dice[i]) / 2;
		i++;
	}
	return (res);
}

t_bool	has_dice(t_dice dice)
{
	int	i;

	i = 0;
	while (i < NB_DICE)
	{
		if (dice[i++])
			return (true);
	}
	return (false);
}

int	dice_i(int dice)
{
	if (dice == 1)
		return (D1);
	if (dice == 4)
		return (D4);
	if (dice == 6)
		return (D6);
	if (dice == 8)
		return (D8);
	if (dice == 10)
		return (D10);
	if (dice == 12)
		return (D12);
	if (dice == 20)
		return (D20);
	if (dice == 100)
		return (D100);
	return (-1);
}

int	index_dice(int i)
{
	if (i == D1)
		return (1);
	if (i == D4)
		return (4);
	if (i == D6)
		return (6);
	if (i == D8)
		return (8);
	if (i == D10)
		return (10);
	if (i == D12)
		return (12);
	if (i == D20)
		return (20);
	if (i == D100)
		return (100);
	return (-1);
}

void	set_dice(t_dice to_set, int dice, int nb)
{
	int	i;

	i = 0;
	while (i < NB_DICE)
	{
		to_set[i] = 0;
		i++;
	}
	if (dice > 0 && dice < NB_DICE)
		to_set[dice] = nb;
}

void	copy_dice(t_dice to_set, t_dice copy)
{
	int	i;

	i = 0;
	while (i < NB_DICE)
	{
		to_set[i] = copy[i];
		i++;
	}
}

void	add_dice(t_dice adder, t_dice added)
{
	int	i;

	i = 0;
	while (i < NB_DICE)
	{
		adder[i] += added[i];
		i++;
	}
}

int	roll_one(int dice, int nb)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (i < nb)
	{
		res += rand() % dice + 1;
		i++;
	}
	return (res);
}

int	roll(t_dice dice)
{
	int	result;

	result = 0;
	if (dice[D1])
		result += dice[D1];
	if (dice[D4])
		result += roll_one(4, dice[D4]);
	if (dice[D6])
		result += roll_one(6, dice[D6]);
	if (dice[D8])
		result += roll_one(8, dice[D8]);
	if (dice[D10])
		result += roll_one(10, dice[D10]);
	if (dice[D12])
		result += roll_one(12, dice[D12]);
	if (dice[D20])
		result += roll_one(20, dice[D20]);
	if (dice[D100])
		result += roll_one(100, dice[D100]);
	return (result);
}
