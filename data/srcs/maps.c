/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:58:54 by fparis            #+#    #+#             */
/*   Updated: 2025/01/16 23:45:21 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->size.y)
	{
		x = 0;
		while (x < map->size.x)
		{
			if (map->arr[x][y].type)
				printf("%c", map->arr[x][y].type);
			else
				printf(" ");
			x++;
		}
		printf("\n");
		y++;
	}
}

void	print_path(t_path *path)
{
	if (!path)
		printf("NONE");
	while (path)
	{
		printf("%d %d -> ", path->pos.x, path->pos.y);
		path = path->next;
	}
	printf("\n");
}
