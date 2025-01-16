/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:27:28 by fparis            #+#    #+#             */
/*   Updated: 2025/01/16 19:22:20 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	*new_texture(int size)
{
	t_texture	*res;
	int			i;

	res = ft_calloc(sizeof(t_texture), 1);
	if (!res)
		return (NULL);
	res->size = size;
	res->tab = ft_calloc(sizeof(uint32_t *), res->size);
	i = 0;
	while (res->tab && i < res->size)
	{
		res->tab[i] = ft_calloc(sizeof(uint32_t), res->size);
		if (!res->tab[i])
			break ;
		i++;
	}
	if (i < res->size)
	{
		free_tex(res);
		return (NULL);
	}
	return (res);
}

void	print_col(uint32_t col)
{
	uint32_t	alpha;
	uint32_t	red;
	uint32_t	green;
	uint32_t	blue;

	alpha = col >> 24;
	red = ((col & 0x00FF0000) >> 16);
	green = ((col & 0x0000FF00) >> 8);
	blue = (col & 0x000000FF);
	printf("%X-> A:%x, R:%x, G:%x, B:%x\n", col, alpha, red, green, blue);
}

t_texture	*img_to_tex(t_data *data, void *img, t_vector size)
{
	int			new_size;
	t_vector	i;
	t_texture	*res;

	new_size = ft_min(size.x, size.y);
	res = new_texture(new_size);
	if (!res)
		return (NULL);
	i.y = 0;
	while (i.y < new_size)
	{
		i.x = 0;
		while (i.x < new_size)
		{
			res->tab[i.x][i.y] = mlx_get_image_pixel(data->mlx, img, i.x, i.y);
			i.x++;
		}
		i.y++;
	}
	return (res);
}

t_texture	*path_to_tex(t_data *data, char *path)
{
	int			fd;
	t_texture	*res;
	void		*img;
	t_vector	size;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	close(fd);
	img = NULL;
	if (!ft_strcmp(path + ft_strlen(path) - 4, ".png"))
		img = mlx_png_file_to_image(data->mlx, path, &size.x, &size.y);
	else if (!ft_strcmp(path + ft_strlen(path) - 4, ".jpg"))
		img = mlx_jpg_file_to_image(data->mlx, path, &size.x, &size.y);
	else if (!ft_strcmp(path + ft_strlen(path) - 4, ".bmp"))
		img = mlx_bmp_file_to_image(data->mlx, path, &size.x, &size.y);
	if (!img)
		return (NULL);
	res = img_to_tex(data, img, size);
	if (img)
		mlx_destroy_image(data->mlx, img);
	return (res);
}

void	show_tex(t_data *data, t_texture *tex, t_vector pos)
{
	t_vector	i;

	if (!tex)
		return ;
	i.y = 0;
	while (i.y < tex->size)
	{
		i.x = 0;
		while (i.x < tex->size)
		{
			ft_pixel_put(data, pos.y + i.y, pos.x + i.x, tex->tab[i.x][i.y]);
			i.x++;
		}
		i.y++;
	}
}
