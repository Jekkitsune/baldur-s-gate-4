/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:14:32 by fparis            #+#    #+#             */
/*   Updated: 2024/11/30 12:43:25 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_list	*ft_lstpop(t_list **lst_start, void *check)
{
	t_list	*i;
	t_list	*tmp;

	if (!lst_start || !*lst_start)
		return (NULL);
	i = *lst_start;
	if (i->content == check)
	{
		*lst_start = i->next;
		return (i);
	}
	while (i->next && i->next->content != check)
		i = i->next;
	tmp = i;
	i = i->next;
	if (!i)
		return (NULL);
	tmp->next = i->next;
	return (i);
}

int	ft_inlst(t_list *lst, void *check)
{
	t_list	*i;

	i = lst;
	while (i)
	{
		if (i->content == check)
			return (1);
		i = i->next;
	}
	return (0);
}

t_entity	*set_entity_tex(t_entity *entity, t_texture *tex2, t_texture *tex3, t_texture *tex4)
{
	entity->tex[1] = tex2;
	entity->tex[2] = tex3;
	entity->tex[3] = tex4;
	return (entity);
}

t_entity	*create_entity(t_data *data, t_vector pos, t_texture *tex)
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
	entity->size_scale = 1;
	entity->sheet.alive = 1;
	entity->visible = true;
	entity->offset = vecf(0, 0);
	entity->pos = pos;
	entity->tex[0] = tex;
	set_entity_tex(entity, tex, tex, tex);
	entity->behavior = ft_nothing;
	ft_lstadd_front(&data->current_map->arr[pos.x][pos.y].entities, new_lst);
	return (entity);
}

void	destroy_entity(t_data *data, t_entity *entity)
{
	t_list	*tmp;

	printf("try to destroy %p\n", entity);
	if (!entity)
		return ;
	if (data->player.possession == entity)
		unpossess(data);
	if (data->player.arrow == entity)
		data->player.arrow = NULL;
	if (entity->active)
		destroy_active(data, entity);
	if (in_bound(*data->current_map, entity->pos))
	{
		tmp = ft_lstpop(&data->current_map->arr[entity->pos.x][entity->pos.y].entities, entity);
		if (tmp)
			free(tmp);
	}
	if (entity->sheet.name)
		free(entity->sheet.name);
	free(entity);
	printf("successfully destroyed\n");
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
	while (tex && i.x < lim_x.y && i.x < data->win_size.x)
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
	int		face;
	float	angle_diff;

	if (entity->draw_x.x == data->win_size.x)
		return ;
	angle_diff = get_angle_diff(data->player.angle, entity->angle);
	if (angle_diff >= -(M_PI / 4) && angle_diff < M_PI / 4)
		face = 2;
	else if (angle_diff >= M_PI / 4 && angle_diff < (3 * M_PI) / 4)
		face = 1;
	else if (angle_diff >= (3 * M_PI) / 4 || angle_diff < -((3 * M_PI) / 4))
		face = 0;
	else if (angle_diff >= -((3 * M_PI) / 4) && angle_diff < -(M_PI / 4))
		face = 3;
	draw_thing_tex(data, entity->draw_x, entity->draw_y, get_correct_tex(entity, face), entity->distance);
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
	entity->draw_y.x -= (entity->draw_y.y - entity->draw_y.x) * (entity->size_scale - 1);
	if (entity->draw_x.x == data->win_size.x)
		return ;
	entity->draw_x.y = (WIDTH / entity->distance * (data->scale * 2)) * entity->size_scale;
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
		data->player.visible_entities = i;
	}
	data->player.visible_entities = NULL;
}

void	move_entity(t_data *data, t_entity *entity, t_vectorf move)
{
	t_vector	last_pos;
	t_list		*entity_lst;

	last_pos = entity->pos;
	entity->offset.x += move.x;
	entity->offset.y += move.y;
	correct_pos(data, &entity->pos, &entity->offset);
	if (entity->pos.x != last_pos.x || entity->pos.y != last_pos.y)
	{
		if (in_bound(*data->current_map, last_pos))
		{
			entity_lst = ft_lstpop(&data->current_map->arr[last_pos.x][last_pos.y].entities, entity);
			if (entity_lst && in_bound(*data->current_map, entity->pos))
			{
				entity_lst->next = NULL;
				ft_lstadd_back(&data->current_map->arr[entity->pos.x][entity->pos.y].entities, entity_lst);
				return ;
			}
		}
		destroy_entity(data, entity);
	}
}

void	teleport_entity(t_data *data, t_entity *entity, t_vector pos, t_vectorf offset)
{
	t_vector	last_pos;
	t_list		*entity_lst;

	last_pos = entity->pos;
	entity->pos = pos;
	entity->offset = offset;
	correct_pos(data, &entity->pos, &entity->offset);
	if (entity->pos.x != last_pos.x || entity->pos.y != last_pos.y)
	{
		if (in_bound(*data->current_map, last_pos))
		{
			entity_lst = ft_lstpop(&data->current_map->arr[last_pos.x][last_pos.y].entities, entity);
			if (entity_lst && in_bound(*data->current_map, entity->pos))
			{
				entity_lst->next = NULL;
				ft_lstadd_back(&data->current_map->arr[entity->pos.x][entity->pos.y].entities, entity_lst);
				return ;
			}
		}
		destroy_entity(data, entity);
	}
}
