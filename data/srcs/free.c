/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 23:25:12 by fparis            #+#    #+#             */
/*   Updated: 2024/10/10 23:37:53 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tex(t_texture *tex)
{
	int	i;

	i = 0;
	if (!tex)
		return ;
	if (tex->tab)
	{
		while (i < tex->size)
		{
			if (tex->tab[i])
				free(tex->tab[i]);
			i++;
		}
		free(tex->tab);
	}
	free(tex);
}

void	free_map(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < map->size.x)
	{
		while (y < map->size.y)
		{
			ft_lstclear(&map->arr[x][y].entities, free);
			y++;
		}
		free(map->arr[x]);
		x++;
	}
	free(map->arr);
	free(map);
}
