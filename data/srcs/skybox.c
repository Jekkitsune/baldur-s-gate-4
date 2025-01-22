/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:42:41 by fparis            #+#    #+#             */
/*   Updated: 2025/01/21 18:32:52 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_tex_skybox(t_data *data, t_skybox *s)
{
	s->index = (int)(s->closest_card / (M_PI / 2));
	if (s->index == 4)
		s->index = 0;
	if (s->tiniest_gap >= 0)
	{
		s->left_tex = data->sky_box_tex[s->index];
		if (s->index == 3)
			s->index = -1;
		s->right_tex = data->sky_box_tex[s->index + 1];
	}
	else
	{
		s->right_tex = data->sky_box_tex[s->index];
		if (s->index == 0)
			s->index = 4;
		if (data->sky_box)
			s->left_tex = data->sky_box_tex[s->index - 1];
	}
}

void	skybox2(t_data *data, t_skybox *s, float tmp)
{
	tmp = data->player.angle - M_PI * 2;
	if (fabs(tmp) < fabs(s->tiniest_gap))
	{
		s->tiniest_gap = tmp;
		s->closest_card = M_PI * 2;
	}
	s->pixel_length = ((M_PI - (fabs(s->tiniest_gap) * 2)) \
		* (data->win_size.x - 1)) / M_PI;
	if (s->tiniest_gap > 0)
	{
		s->left_seg = vec(0, s->pixel_length);
		s->right_seg = vec(s->pixel_length + 1, data->win_size.x - 1);
	}
	else
	{
		s->right_seg = vec(data->win_size.x - 1 - s->pixel_length, \
			data->win_size.x - 1);
		s->left_seg = vec(0, s->right_seg.x - 1);
	}
	get_tex_skybox(data, s);
}

void	skybox(t_data *data, t_skybox *s)
{
	float		tmp;

	s->tiniest_gap = data->player.angle;
	s->closest_card = 0;
	tmp = data->player.angle - M_PI / 2;
	if (fabs(tmp) < fabs(s->tiniest_gap))
	{
		s->tiniest_gap = tmp;
		s->closest_card = M_PI / 2;
	}
	tmp = data->player.angle - M_PI;
	if (fabs(tmp) < fabs(s->tiniest_gap))
	{
		s->tiniest_gap = tmp;
		s->closest_card = M_PI;
	}
	tmp = data->player.angle - M_PI * 1.5;
	if (fabs(tmp) < fabs(s->tiniest_gap))
	{
		s->tiniest_gap = tmp;
		s->closest_card = M_PI * 1.5;
	}
	skybox2(data, s, tmp);
}
