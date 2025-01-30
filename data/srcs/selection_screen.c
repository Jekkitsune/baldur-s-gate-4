/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_screen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 06:26:58 by gmassoni          #+#    #+#             */
/*   Updated: 2025/01/30 09:41:29 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_bg(t_data *data, int size, t_vector pos, uint32_t color)
{
	int	i;
	int	j;

	i = pos.x;
	while (i < pos.x + size)
	{
		j = pos.y;
		while (j < pos.y + size)
		{
			data->screen_buffer[j][i] = color;
			j++;
		}
		i++;
	}
}

int	is_selected(t_data *data, char *class, t_vector pos, int size)
{
	t_vector	mouse;
	
	mlx_mouse_get_pos(data->mlx, &mouse.x, &mouse.y);
	if (in_party_name(data, class))
		return (2);
	else if (mouse.x < pos.x || mouse.x > pos.x + size
		|| mouse.y < pos.y || mouse.y > pos.y + size)
		return (0);
	else
		return (1);
}

void	draw_border(t_data *data, t_vector pos, int size, uint32_t color)
{
	int	i;
	int	j;

	i = pos.x - 2;
	while (i < pos.x + size + 2)
	{
		j = pos.y - 2;
		while (j < pos.y + size + 2)
		{
			ft_pixel_put(data, j, i, color);
			j++;
		}
		i++;
	}
}

void	print_class(t_data *data, t_vector pos, char *class, int index)
{
	t_entity	*entity;
	t_texture	*tex;
	int			size;
	int			anim_index;
	t_bool		selected;
	t_strput	*to_put;

	size = data->win_size.y * 0.35;
	entity = get_prefab(data, class);
	if (!entity)
		return ;
	selected = is_selected(data, class, pos, size);
	if (!selected)
		anim_index = get_anim_index(entity, "idle");
	else
		anim_index = get_anim_index(entity, "select");
	if (anim_index == -1)
		return ;
	tex = resize(entity->anim[anim_index].tab[index % entity->anim[anim_index].size], size);
	if (!tex)
		return ;
	if (!selected)
		draw_bg(data, size, pos, 0xFF232323);
	else if (selected == 1)
	{
		draw_border(data, pos, size, 0xFFFFFFFF);
		draw_bg(data, size, pos, 0xFF303030);
	}
	else
	{
		draw_border(data, pos, size, 0xFFE6C302);
		draw_bg(data, size, pos, 0xFF353535);
	}
	show_tex(data, tex, pos);
	to_put = strput(ft_strdup(entity->sheet.name), vec(pos.x, pos.y + size + 20), data->button_scale_size / 2, 0xFFFFFFFF);
	screen_string_put(data, to_put, 0);
	free_tex(tex);
}

void	start_button(t_data *data, t_vector size, t_vector pos)
{
	int			i;
	int			j;
	uint32_t	color;
	t_strput	*to_put;

	color = 0xFF232323;
	if (ft_lstsize(data->round_manager.party) == 4)
		color = 0xFF008000;
	i = pos.x - 1;
	while (++i < pos.x + size.x)
	{
		j = pos.y - 1;
		while (++j < pos.y + size.y)
			ft_pixel_put(data, j, i, color);
	}
	to_put = strput(ft_strdup("start"), vec(pos.x + (size.x / 2), pos.y + (size.y / 1.5)), data->button_scale_size / 2, 0xFF000000);
	to_put->centered = true;
	screen_string_put(data, to_put, 0);
}

void    selection_screen(t_data *data)
{
	t_vector			it;
	static unsigned int	nb = 0;
	static unsigned int	nb2 = 0;	

	it.x = 0;
	while (it.x < data->win_size.x)
	{
		it.y = 0;
		while (it.y < data->win_size.y)
		{
			data->screen_buffer[it.y][it.x] = 0xFF353535;
			it.y++;
		}
		it.x++;
	}
	nb2++;
	if (nb2 > 5)
	{
		nb2 = 0;
		nb++;
	}
	print_class(data, vec(data->win_size.x * 0.1, data->win_size.y * 0.1), "barbarian", nb);
	print_class(data, vec(data->win_size.x * 0.4, data->win_size.y * 0.55), "rogue", nb);
	print_class(data, vec(data->win_size.x * 0.4, data->win_size.y * 0.1), "warlock", nb);
	print_class(data, vec(data->win_size.x * 0.1, data->win_size.y * 0.55), "wizard", nb);
	print_class(data, vec(data->win_size.x * 0.7, data->win_size.y * 0.1), "monk", nb);
	print_class(data, vec(data->win_size.x * 0.7, data->win_size.y * 0.55), "ranger", nb);
	start_button(data, vec(data->win_size.x * 0.06, data->win_size.y * 0.06), vec(data->win_size.x * 0.92, data->win_size.y * 0.03));
	put_screen(data);
}
