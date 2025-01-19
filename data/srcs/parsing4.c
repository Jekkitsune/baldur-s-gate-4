/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:09:45 by gmassoni          #+#    #+#             */
/*   Updated: 2025/01/10 11:25:40 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_textures(t_texture *default_tex[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!default_tex[i])
			return (false);
		i++;
	}
	return (true);
}

bool	format_test(char *name)
{
	size_t	len;

	len = ft_strlen(name);
	if (len < 5)
		return (false);
	if (name[len - 1] != 'b' || name[len - 2] != 'u' || name[len - 3] != 'c'
		|| name[len - 4] != '.')
		return (false);
	return (true);
}

bool	special_atoi(char *str, int *res)
{
	int	i;

	i = 0;
	*res = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		*res = (10 * *res) + str[i] - '0';
		i++;
	}
	return (true);
}

void	get_hexa(char hexa[2], int value)
{
	char	*base;

	base = "0123456789ABCDEF";
	hexa[0] = base[value / 16];
	hexa[1] = base[value % 16];
}
