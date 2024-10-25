/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:14:32 by fparis            #+#    #+#             */
/*   Updated: 2024/10/25 23:08:39 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_entity	*create_entity(t_data *data, t_vector pos, char typ, t_texture *tex)
{
	t_entity	*entity;
	t_list		*new_lst;

	if (pos.x < 0 || pos.x > data->current_map->size.x || pos.y < 0
		|| pos.y > data->current_map->size.y)
		return (NULL);
	entity = ft_calloc(sizeof(t_entity), 1);
	if (!entity)
		return (NULL);
	new_lst = ft_lstnew(entity);
	if (!new_lst)
	{
		free(entity);
		return (NULL);
	}
	entity->id = entity;
	entity->nb_impact = 0;
	entity->offset = vecf(0, 0);
	entity->pos = pos;
	entity->tex = tex;
	entity->type = typ;
	ft_lstadd_front(&data->current_map->arr[pos.x][pos.y].entities, new_lst);
	return (entity);
}

void	destroy_entity(t_data *data, t_entity *entity)
{
	t_list	*tmp;

	if (entity->pos.x >= 0 && entity->pos.x < data->current_map->size.x
		&& entity->pos.y >= 0 && entity->pos.y < data->current_map->size.y)
	{
		tmp = data->current_map->arr[entity->pos.x][entity->pos.y].entities;
		while (tmp && tmp->content != entity->id)
			tmp = tmp->next;
		if (tmp)
			ft_lstdelone(tmp, free);
	}
	else
		free(entity);
}

float	get_obj_x(t_data *data, t_vectorf pos, t_vectorf p_pos)
{
	float	obj_angle;
	float	angle_diff;
	float	x;

	obj_angle = atan2(p_pos.y - pos.y, pos.x - p_pos.x);
	angle_diff = -obj_angle - data->player.angle;
	if (fabs(angle_diff) > M_PI)
		angle_diff = ((2 * M_PI) - angle_diff) * -1;
	if (fabs(fabs(fmod(angle_diff, 2 * M_PI)) - M_PI) < M_PI / 2)
		return (data->win_size.x);
	x = tan(angle_diff) * (WIDTH / 2) + (WIDTH / 2);
	//printf("obj: %f, player: %f, angle_diff: %f\n%f\n", obj_angle, data->player.angle, angle_diff, x);
	return (x);
}

float	get_obj_y(t_data *data, t_vectorf true_pos, t_vectorf p_pos, t_vector *i)
{
	float	slope;
	float	size;
	float	distance;

	slope = data->player.camera_plane.y / data->player.camera_plane.x;
	slope = tan(angle_add(data->player.angle, -(M_PI / 2)));
	distance = fabs(((p_pos.y - true_pos.y) * -1) - (slope * (true_pos.x - p_pos.x))) / sqrt(slope * slope + 1.0);
	// if (size / (data->scale * 2) == 0)
	// 	return ;
	//printf("distance:%f, f:%f, slope:%f\n", distance, fabs(p_pos.y - true_pos.y - (slope * (true_pos.x - p_pos.x))), slope);
	//printf("f:fabs(%f - (%f * (%f)))\n", ((p_pos.y - true_pos.y) * -1), slope, true_pos.x - p_pos.x);
	size = (data->win_size.y / (distance / (data->scale * 2)));
	//i->x = ft_max(0, (data->win_size.y / 2) - (size / 2));
	//i->y = ft_min(data->win_size.y, (data->win_size.y / 2) + (size / 2));
	i->x = (data->win_size.y / 2) - (size / 2);
	i->y = (data->win_size.y / 2) + (size / 2);
	i->x += data->player.pitch + (data->player.height / distance);
	i->y += data->player.pitch + (data->player.height / distance);
	return (distance);
}

void	draw_thing_tex(t_data *data, t_vector lim_x, t_vector lim_y, t_texture *tex, int distance)
{
	t_vector	i;
	int			size_x;
	int			size_y;
	int			i_tab;

	size_x = lim_x.y - lim_x.x;
	size_y = lim_y.y - lim_y.x;
	i.x = ft_max(lim_x.x, 0);
	while (i.x < lim_x.y && i.x < data->win_size.x)
	{
		if (((i.x * NB_RAYS) / WIDTH) < NB_RAYS && ((i.x * NB_RAYS) / WIDTH) > 0 && data->player.vision[(i.x * NB_RAYS) / WIDTH].length < distance)
		{
			i.x++;
			continue ;
		}
		i.y = ft_max(lim_y.x, 0);
		i_tab = (i.x - lim_x.x) * tex->size / size_x;
		while (i.y < lim_y.y && i.y < data->win_size.y)
		{
			ft_pixel_put(data, i.y, i.x, tex->tab[i_tab][(i.y - lim_y.x) * tex->size / size_y]);
			i.y++;
		}
		i.x++;
	}	
}

void	draw_thing(t_data *data, t_vector pos, t_vectorf offset, t_texture *tex)
{
	t_vectorf	true_pos;
	t_vectorf	p_pos;
	t_vector	x;
	t_vector	i;
	float		distance;

	if (!tex || !tex->tab)
		return ;
	true_pos.x = (pos.x) * (data->scale * 2) + (offset.x + data->scale);
	true_pos.y = (pos.y) * (data->scale * 2) + (offset.y + data->scale);
	p_pos.x = data->player.pos.x * (data->scale * 2) + (data->player.offset.x + data->scale);
	p_pos.y = data->player.pos.y * (data->scale * 2) + (data->player.offset.y + data->scale);
	x.x = get_obj_x(data, true_pos, p_pos);
	distance = get_obj_y(data, true_pos, p_pos, &i);
	if (x.x == data->win_size.x)
		return ;
	x.y = WIDTH / distance * (data->scale * 2);
	x.x = x.x - (x.y / 2);
	x.y = x.x + x.y;
	draw_thing_tex(data, x, i, tex, distance);
}

void	draw_entity(t_data *data, t_entity *entity)
{
	if (entity->draw_x.x == data->win_size.x)
		return ;
	draw_thing_tex(data, entity->draw_x, entity->draw_y, entity->tex, entity->distance);
}

void	calculate_entity_info(t_data *data, t_entity *entity)
{
	t_vectorf	p_pos;

	entity->true_pos.x = (entity->pos.x) * (data->scale * 2) + (entity->offset.x + data->scale);
	entity->true_pos.y = (entity->pos.y) * (data->scale * 2) + (entity->offset.y + data->scale);
	p_pos.x = data->player.pos.x * (data->scale * 2) + (data->player.offset.x + data->scale);
	p_pos.y = data->player.pos.y * (data->scale * 2) + (data->player.offset.y + data->scale);
	entity->draw_x.x = get_obj_x(data, entity->true_pos, p_pos);
	entity->distance = get_obj_y(data, entity->true_pos, p_pos, &entity->draw_y);
	if (entity->draw_x.x == data->win_size.x)
		return ;
	entity->draw_x.y = WIDTH / entity->distance * (data->scale * 2);
	entity->draw_x.x = entity->draw_x.x - (entity->draw_x.y / 2);
	entity->draw_x.y = entity->draw_x.x + entity->draw_x.y;
}

void	draw_entities(t_data *data)
{
	t_list		*i;
	t_entity	*entity;
	t_list		*to_free;

	i = data->player.visible_entities;
	while (i)
	{
		entity = i->content;
		if (entity && entity->nb_impact)
		{
			draw_entity(data, entity);
			entity->nb_impact = 0;
		}
		to_free = i;
		i = i->next;
		free(to_free);
	}
	data->player.visible_entities = NULL;
}
