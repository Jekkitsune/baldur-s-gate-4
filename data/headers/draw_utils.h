/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:29:13 by fparis            #+#    #+#             */
/*   Updated: 2025/01/31 12:49:56 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_UTILS_H
# define DRAW_UTILS_H

# include "cub3d.h"

void	reverse_draw_vertical_line(t_data *data, t_vector p1, t_vector p2,
			t_linfo info);
void	reverse_draw_shallow(t_data *data, t_vector p1, t_vector p2,
			t_linfo info);
void	reverse_draw_deep(t_data *data, t_vector p1, t_vector p2, t_linfo info);

#endif