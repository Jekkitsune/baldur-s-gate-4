/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:04:45 by fparis            #+#    #+#             */
/*   Updated: 2025/01/28 19:38:01 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_wizard_class(t_data *data);
void	init_barbarian_class(t_data *data);
void	init_warlock_class(t_data *data);
void	init_rogue_class(t_data *data);
void	init_monk_class(t_data *data);
void	init_ranger_class(t_data *data);

void	init_all_classes(t_data *data)
{
	init_wizard_class(data);
	init_barbarian_class(data);
	init_warlock_class(data);
	init_rogue_class(data);
	init_monk_class(data);
	init_ranger_class(data);
}
