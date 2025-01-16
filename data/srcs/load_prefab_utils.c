/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_prefab_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 23:34:52 by fparis            #+#    #+#             */
/*   Updated: 2025/01/15 23:36:14 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
