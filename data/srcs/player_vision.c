/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_vision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:42:41 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 02:17:50 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_upper_walls(t_data *data, float diff, t_impact *ray, int i);

void	draw_ray(t_data *data, float diff, t_impact *ray, int i)
{
	int			i2;
	int			size;
	t_vector	posy;

	if (ray->face == 0)
		return ;
	if (ray->length <= 0)
		size = 0;
	else
		size = (data->win_size.y / (ray->length / (data->scale * 2)));
	posy.x = (data->win_size.y - size) / 2;
	posy.y = (data->win_size.y + size) / 2;
	i2 = 0;
	while (i2 < diff)
	{
		draw_wall(data, i * diff + i2, vec(posy.x + data->player.pitch \
		+ (data->player.height / ray->length), posy.y + data->player.pitch \
		+ (data->player.height / ray->length)), ray);
		i2++;
	}
}

void	show_environment(t_data *data)
{
	float		diff;
	int			i;
	t_bool		draw_up_wall;

	if (data->player.height >= -5000)
		show_floor(data);
	if (data->player.height <= 5000)
		show_ceiling(data);
	i = 0;
	diff = (float)data->win_size.x / (float)NB_RAYS;
	draw_up_wall = false;
	if (in_bound(data->current_map, data->player.pos)
		&& !data->current_map->arr[data->player.pos.x][data->player.pos.y].\
		upper_wall)
		draw_up_wall = true;
	while (i < NB_RAYS)
	{
		draw_ray(data, diff, &data->player.vision[i], i);
		if (draw_up_wall)
			draw_upper_walls(data, diff, &data->player.vision[i], i);
		i++;
	}
	draw_entities_fog(data, diff);
}

void	show_screen(t_data *data)
{
	get_all_rays(data);
	show_environment(data);
	show_party_icon(data);
	show_participants_icon(data);
	if (data->player.possession && data->player.possession->possess_control
		&& is_turn(data, data->player.possession))
	{
		draw_possession_button(data, data->player.possession->sheet.buttons);
		draw_all_actions_box(data, data->player.possession);
		show_end_turn_button(data);
		if (data->player.possession->sheet.inventory_open)
			draw_inventory(data, data->player.possession->sheet.inventory);
		else
			data->player.shop_mode = false;
	}
	show_health_bar(data);
	show_minimap(data);
	put_screen(data);
}
