/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 20:15:40 by fparis            #+#    #+#             */
/*   Updated: 2024/11/30 12:43:30 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	angle_add(float angle, float add)
{
	angle += add;
	while (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	while (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

float	get_angle_diff(float angle1, float angle2)
{
	float	res;

	res = angle1 - angle2;
	res = fmod(res + M_PI, 2 * M_PI);
	if (res < 0)
		res += 2 * M_PI;
	res -= M_PI;
	return (res);
}
