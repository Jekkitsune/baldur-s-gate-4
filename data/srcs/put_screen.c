/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_screen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 21:34:36 by fparis            #+#    #+#             */
/*   Updated: 2025/01/16 20:24:32 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_strput	*strput(char *str, t_vector pos, float size, uint32_t color)
{
	t_strput	*to_put;

	if (!str)
		return (NULL);
	to_put = ft_calloc(sizeof(t_strput), 1);
	if (!to_put)
	{
		if (str)
			free(str);
		return (NULL);
	}
	to_put->str = str;
	to_put->pos.x = pos.x;
	to_put->pos.y = pos.y;
	to_put->size = size;
	to_put->color = color;
	return(to_put);
}

int	screen_string_put(t_data *data, t_strput *to_put, float time)
{
	t_list			*lst;

	if (!to_put)
		return (0);
	lst = ft_lstnew(to_put);
	if (!lst)
	{
		if (to_put->str)
			free(to_put->str);
		free(to_put);
		return (0);
	}
	if (time)
		to_put->duration = (float)time * 1000000.0;
	ft_lstadd_front(&data->string_to_put, lst);
	return (1);
}

void	remove_screen_info(t_strput **screen_info, t_strput *to_remove)
{
	int	i;

	if (!to_remove || !to_remove->duration)
		return ;
	i = 0;
	while (i < MAX_SCREEN_INFO && screen_info[i] != to_remove)
		i++;
	if (i >= MAX_SCREEN_INFO)
		return ;
	screen_info[i] = NULL;
}

void	clear_string_put(t_data *data, t_bool force)
{
	t_list			*lst;
	t_strput		*current;
	t_list			*tmp;

	lst = data->string_to_put;
	while (lst)
	{
		current = lst->content;
		lst = lst->next;
		current->duration -= data->frame_time;
		if (force || !current->duration || current->duration <= 0)
		{
			remove_screen_info(data->screen_info, current);
			tmp = ft_lstpop(&data->string_to_put, current);
			free(current->str);
			free(tmp->content);
			free(tmp);
		}
	}
}

void	put_all_strings(t_data *data)
{
	t_list		*lst;
	t_strput	*current_str;
	static float	size = 0;

	lst = data->string_to_put;
	while (lst)
	{
		current_str = lst->content; 
		if (current_str->size != size)
		{
			size = current_str->size;
			mlx_set_font_scale(data->mlx, data->win, DEFAULT_FONT, size);
		}
		mlx_string_put(data->mlx, data->win, current_str->pos.x,
			current_str->pos.y, current_str->color, current_str->str);
		lst = lst->next;
	}
	clear_string_put(data, false);
}

void	put_screen(t_data *data)
{
	int	i;
	int	j;

	if (!data->screen_display)
		data->screen_display = mlx_new_image(data->mlx, data->win_size.x, data->win_size.y);
	i = 0;
	while (i < data->win_size.y)
	{
		j = 0;
		while (j < data->win_size.x)
		{
			mlx_set_image_pixel(data->mlx, data->screen_display, j, i, data->screen_buffer[i][j]);
//			mlx_pixel_put(data->mlx, data->win, j, i, data->screen_buffer[i][j]); //ca empeche les str ;/
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->screen_display, 0, 0);
	put_all_strings(data);
}
