/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:04:45 by fparis            #+#    #+#             */
/*   Updated: 2025/01/15 20:05:25 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_class(t_list **class_lst, t_class *class);

void	init_wizard_class(t_data *data)
{
	t_class	*class;

	class = ft_calloc(sizeof(t_class), 1);
	if (!class)
		return ;
	class->name = "wizard";
	init_fireball_button(data, &class->level[0].buttons[0]);
	add_class(&data->class_lst, class);
}

void	init_all_classes(t_data *data)
{
	init_wizard_class(data);
}
