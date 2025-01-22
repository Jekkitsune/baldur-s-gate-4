/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_vision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:42:41 by fparis            #+#    #+#             */
/*   Updated: 2025/01/22 02:25:04 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_upper_walls(t_data *data, float diff, t_impact *ray, int i);

void	draw_fog_wall(t_data *data, int x, t_vector pos, uint32_t color)
{
	int	i;

	i = 0;
	i = ft_max(pos.x, i);
	while (i < pos.y && i < data->win_size.y)
	{
		if (i >= 0)
			ft_pixel_put(data, i, x, color);
		i++;
	}
}

void	draw_fog(t_data *data, float diff, t_impact *ray, int i)
{
	int			i2;
	int			size;
	t_vector	posy;

	if (ray->fog_length <= 0)
		return ;
	size = (data->win_size.y / (ray->fog_length / (data->scale * 2)));
	posy.x = (data->win_size.y - size) / 2;
	posy.y = (data->win_size.y + size) / 2;
	i2 = 0;
	while (i2 < diff)
	{
		draw_fog_wall(data, i * diff + i2, vec(posy.x + data->player.pitch \
		+ (data->player.height / ray->fog_length), posy.y + data->player.pitch \
		+ (data->player.height / ray->fog_length)), ray->fog_color);
		i2++;
	}
}

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
	draw_upper_walls(data, diff, ray, i);
}

void	show_environment(t_data *data)
{
	float		diff;
	int			i;

	if (data->floor && data->player.height >= -5000)
		show_floor(data);
	if (data->ceiling && data->player.height <= 5000)
		show_ceiling(data);
	i = 0;
	diff = (float)data->win_size.x / (float)NB_RAYS;
	while (i < NB_RAYS)
	{
		draw_ray(data, diff, &data->player.vision[i], i);
		i++;
	}
	draw_entities(data);
	i = 0;
	while (i < NB_RAYS)
	{
		draw_fog(data, diff, &data->player.vision[i], i);
		i++;
	}
}

void	show_screen(t_data *data)
{
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
	}
	show_health_bar(data);
	show_minimap(data);
	put_screen(data);
}
