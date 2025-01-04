/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_prefab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:22:10 by fparis            #+#    #+#             */
/*   Updated: 2025/01/02 18:45:56 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

t_animation	*add_anim(t_animation **tab, t_animation *new, int *nb_anim)
{
	t_animation	*res;

	if (!tab)
	{
		*tab = new;
		return (new);
	}
	if (!new)
		return (*tab);
	res = ft_calloc(*nb_anim + 1, sizeof(t_animation));
	ft_memcpy(res, *tab, *nb_anim * sizeof(t_animation));
	ft_memcpy(&(res[*nb_anim]), new, sizeof(t_animation));
	if (!res)
		return (*tab);
	free(*tab);
	*nb_anim += 1;
	*tab = res;
	return (res);
}

int	get_anim_size(char *path)
{
	int		res;
	char	*str;
	int		fd;
	int		i;
	int		nb_frame;

	str = ft_calloc((ft_strlen(path) + 1), sizeof(char));
	if (!str)
		return (0);
	ft_strlcpy(str, path, ft_strlen(path) + 1);
	nb_frame = ft_strlen(path) - 6;
	i = 1;
	fd = open(str, O_RDONLY);
	while (fd != -1)
	{
		i++;
		close(fd);
		if (i >= 100 && i % 100 == 0)
			str[nb_frame - 1] = '0' + i % 1000 / 100;
		str[nb_frame] = '0' + (i % 100 / 10);
		str[nb_frame + 1] = '0' + i % 10;
		fd = open(str, O_RDONLY);
	}
	free(str);
	return (i - 1);
}

int	try_format(char **str, char *format)
{
	char	*test;
	int		anim_size;

	test = ft_strjoin(*str, format);
	anim_size = get_anim_size(test);
	if (anim_size)
	{
		free(*str);
		*str = test;
		return (anim_size);
	}
	free(test);
	return (0);
}

int	check_anim_existence(char **str)
{
	char	*test;
	int		anim_size;

	anim_size = try_format(str, ".png");
	if (anim_size)
		return (anim_size);
	anim_size = try_format(str, ".jpg");
	if (anim_size)
		return (anim_size);
	anim_size = try_format(str, ".bmp");
	if (anim_size)
		return (anim_size);
	return (0);
}

t_bool	try_one_face(t_data *data, t_entity *entity, char *base_str, char *face)
{
	int			anim_size;
	char		*str;
	t_animation	anim;

	str = NULL;
	str = ft_vajoin(base_str, face, "01", NULL);
	anim_size = check_anim_existence(&str);
	if (anim_size)
	{
		init_anim(data, &anim, anim_size, str);
		free(str);
		add_anim(&entity->anim, &anim, &entity->nb_anim);
		return (true);
	}
	free(str);
	return (false);
}

void	set_anim_info(t_animation *anim, char *name, int interval)
{
	if (!anim)
		return ;
	anim->name = name;
	anim->interval = interval;
}

t_entity	*try_all_faces(t_data *data, t_entity *entity, char *directory, char *name)
{
	char		*base_str;

	base_str = ft_vajoin(directory, "/", name, NULL);
	if (try_one_face(data, entity, base_str, ""))
		set_anim_info(&entity->anim[entity->nb_anim - 1], ft_strjoin(name, ""), 10);
	if (try_one_face(data, entity, base_str, "_sidel"))
		set_anim_info(&entity->anim[entity->nb_anim - 1], ft_strjoin(name, "_sidel"), 10);
	if (try_one_face(data, entity, base_str, "_back"))
		set_anim_info(&entity->anim[entity->nb_anim - 1], ft_strjoin(name, "_back"), 10);
	if (try_one_face(data, entity, base_str, "_sider"))
		set_anim_info(&entity->anim[entity->nb_anim - 1], ft_strjoin(name, "_sider"), 10);
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

t_entity	*get_prefab_data(t_data *data, char *directory)
{
	t_entity	*entity;

	entity = ft_calloc(sizeof(t_entity), 1);
	if (!entity)
		return (NULL);
	entity->size_scale = 1;
	entity->sheet.alive = true;
	entity->offset = vecf(0, 0);
	entity->pos = vec(-1, -1);
	entity->tex[0] = data->wall_tex[0];
	set_entity_tex(entity, data->wall_tex[0], data->wall_tex[0], data->wall_tex[0]);
	entity->behavior.func = ft_nothing;
	entity->anim = NULL;
	try_all_faces(data, entity, directory, "idle");
	try_all_faces(data, entity, directory, "walk");
	try_all_faces(data, entity, directory, "melee");
	try_all_faces(data, entity, directory, "range");
	try_all_faces(data, entity, directory, "select");
	try_all_faces(data, entity, directory, "cast");
	try_all_faces(data, entity, directory, "dead");
	entity->sheet.portrait = get_resized_free(data, get_portrait(data, directory), data->button_scale_size);
	return (entity);
}
