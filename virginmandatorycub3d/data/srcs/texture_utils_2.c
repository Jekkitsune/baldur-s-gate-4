/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:22:09 by fparis            #+#    #+#             */
/*   Updated: 2025/01/16 19:22:22 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	*get_resized_free(t_texture *texture, int size)
{
	t_texture	*resized;

	if (!texture)
		return (NULL);
	resized = resize(texture, size);
	free_tex(texture);
	return (resized);
}
