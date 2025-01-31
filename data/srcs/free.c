/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 23:25:12 by fparis            #+#    #+#             */
/*   Updated: 2025/01/31 11:59:15 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tex_lst(t_data *data);
void	free_all_maps(t_data *data);
void	free_properties_tab(t_data *data);

void	free_tex(t_texture *tex)
{
	int	i;

	i = 0;
	if (!tex)
		return ;
	if (tex->name)
		free(tex->name);
	if (tex->tab)
	{
		while (i < tex->size)
		{
			if (tex->tab[i])
				free(tex->tab[i]);
			i++;
		}
		free(tex->tab);
	}
	free(tex);
}

void	free_minimap(t_data *data)
{
	int	i;

	i = 0;
	if (data->minimap.img)
		mlx_destroy_image(data->mlx, data->minimap.img);
	while (i < data->minimap.chunk_size)
	{
		free(data->minimap.chunk[i]);
		i++;
	}
	free(data->minimap.chunk);
	data->minimap.chunk = NULL;
}

void	free_prefab_tab(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_prefab)
	{
		free_prefab_entity(data, data->prefab_tab[i]);
		i++;
	}
	if (data->prefab_tab)
		free(data->prefab_tab);
	data->prefab_tab = NULL;
}

void	free_data(t_data *data)
{
	int		i;

	free_button_lst(data);
	free_all_maps(data);
	free_prefab_tab(data);
	free_minimap(data);
	free_tex_lst(data);
	free_visible_lst(data);
	clear_string_put(data, true);
	ft_lstclear(&data->timer_effect, free);
	ft_lstclear(&data->class_lst, free);
	if (data->screen_display)
		mlx_destroy_image(data->mlx, data->screen_display);
	i = 0;
	while (i < data->win_size.y)
	{
		free(data->screen_buffer[i]);
		i++;
	}
	free(data->screen_buffer);
	free_properties_tab(data);
}

void	exit_free(t_data *data, char *error)
{
	free_data(data);
	ft_putstr_fd("Cub3d error: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	exit(1);
}
