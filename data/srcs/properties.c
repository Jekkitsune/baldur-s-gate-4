/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:01:11 by fparis            #+#    #+#             */
/*   Updated: 2025/01/16 20:58:57 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_property	get_property(t_data *data, char *name)
{
	int	i;

	(void)data; //a changer!!
	i = 0;
	while (i < NB_PROPERTIES)
	{
		if (!ft_strcmp(PROPERTIES_TAB[i], name))
			return (1 << i);
		i++;
	}
	return (0);
}

t_bool	check_properties(t_property properties, t_property check)
{
	return ((properties & check) == check);
}
