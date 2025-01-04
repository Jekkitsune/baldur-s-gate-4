/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dice.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:54:31 by fparis            #+#    #+#             */
/*   Updated: 2024/12/18 16:54:53 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_dice(t_dice adder, t_dice added)
{
	int	i;

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
