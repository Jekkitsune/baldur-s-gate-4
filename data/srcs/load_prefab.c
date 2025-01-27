/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_prefab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:22:10 by fparis            #+#    #+#             */
/*   Updated: 2025/01/25 07:03:49 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	try_one_face(t_data *data, t_entity *entity, char *base_str,
			char *face);

// void	*ft_memjoin_free(void *m1, void *m2, size_t size1, size_t size2)
// {
// 	void	*res;

// 	if (!m1 && m2)
// 		return (m2);
// 	if (!m2 || !size1 || !size2)
// 		return (m1);
// 	res = ft_calloc(size1 + size2, 1);
// 	ft_memcpy(res, m1, size1);
// 	ft_memcpy(&(res[size1]), m2, size2);
// 	free(m2);
// 	if (!res)
// 		return (m1);
// 	free(m1);
// 	return (res);
// }

void	set_anim_info(t_animation *anim, char *name, int interval)
{
	if (!anim)
		return ;
	anim->name = name;
	anim->interval = interval;
}

t_entity	*try_all_faces(t_data *data, t_entity *entity, char *directory,
	char *name)
{
	char		*base_str;

	base_str = ft_vajoin(directory, "/anim/", name, NULL);
	if (try_one_face(data, entity, base_str, ""))
		set_anim_info(&entity->anim[entity->nb_anim - 1],
			ft_strjoin(name, ""), 10);
	if (try_one_face(data, entity, base_str, "_sidel"))
		set_anim_info(&entity->anim[entity->nb_anim - 1],
			ft_strjoin(name, "_sidel"), 10);
	if (try_one_face(data, entity, base_str, "_back"))
		set_anim_info(&entity->anim[entity->nb_anim - 1],
			ft_strjoin(name, "_back"), 10);
	if (try_one_face(data, entity, base_str, "_sider"))
		set_anim_info(&entity->anim[entity->nb_anim - 1],
			ft_strjoin(name, "_sider"), 10);
	free(base_str);
	return (entity);
}

t_texture	*get_portrait(t_data *data, char *directory)
{
	char		*path;
	t_texture	*tex;

	path = ft_strjoin(directory, "/portrait.png");
	tex = path_to_tex(data, path);
	free(path);
	if (tex)
		return (tex);
	path = ft_strjoin(directory, "/portrait.jpg");
	tex = path_to_tex(data, path);
	free(path);
	if (tex)
		return (tex);
	path = ft_strjoin(directory, "/portrait.bmp");
	tex = path_to_tex(data, path);
	free(path);
	if (tex)
		return (tex);
	return (NULL);
}

void	get_all_anim(t_data *data, t_entity *entity, char *directory)
{
	entity->anim = NULL;
	try_all_faces(data, entity, directory, "idle");
	try_all_faces(data, entity, directory, "walk");
	try_all_faces(data, entity, directory, "melee");
	try_all_faces(data, entity, directory, "range");
	try_all_faces(data, entity, directory, "select");
	try_all_faces(data, entity, directory, "cast");
	try_all_faces(data, entity, directory, "dead");
	if (!entity->anim)
	{
		free_prefab_entity(data, entity);
		ft_putstr_fd(directory, 2);
		exit_free(data, " prefab does not have any anim");
	}
}

t_entity	*get_prefab_data(t_data *data, char *directory)
{
	t_entity	*entity;

	entity = ft_calloc(sizeof(t_entity), 1);
	if (!entity)
		return (NULL);
	entity->size_scale = 1;
	entity->offset = vecf(0, 0);
	entity->pos = vec(-1, -1);
	entity->tex[0] = data->wall_tex[0];
	set_entity_tex(entity, data->wall_tex[0], data->wall_tex[0],
		data->wall_tex[0]);
	get_all_anim(data, entity, directory);
	entity->sheet.portrait = get_resized_free(get_portrait(data, directory),
			data->button_scale_size);
	entity->sheet.nb_attack = 1;
	get_prefab_stat(data, entity, directory);
	if (entity->sheet.type == living)
		entity->sheet.alive = true;
	return (entity);
}
