/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 23:28:20 by fparis            #+#    #+#             */
/*   Updated: 2024/09/12 22:17:53 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	vec_sum(t_vector vec1, t_vector vec2)
{
	t_vector	res;

	res.x = vec1.x + vec2.x;
	res.y = vec1.y + vec2.y;
	return (res);
}

t_vector	vec_mult(t_vector vec, int mult)
{
	vec.x *= mult;
	vec.y *= mult;
	return (vec);
}

t_vector	vec_add(t_vector vec, int add)
{
	vec.x += add;
	vec.y += add;
	return (vec);
}

t_vector	vec(int x, int y)
{
	t_vector	res;

	res.x = x;
	res.y = y;
	return (res);
}

bool	vec_cmp(t_vector vec1, t_vector vec2)
{
	return (vec1.x == vec2.x && vec1.y == vec2.y);
}
