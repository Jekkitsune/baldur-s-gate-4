/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_screen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 21:34:36 by fparis            #+#    #+#             */
/*   Updated: 2024/12/13 18:26:51 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_strput	*strput(char *str, t_vector pos, float size, uint32_t color)
{
	t_strput	*to_put;

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

void	screen_string_put(t_data *data, t_strput *to_put)
{
	t_list	*lst;

	if (!to_put)
		return ;
	lst = ft_lstnew(to_put);
	if (!lst)
	{
		if (to_put->str)
			free(to_put->str);
		free(to_put);
		return ;
	}
	ft_lstadd_front(&data->string_to_put, lst);
}

void	clear_string_put(t_data *data)
{
	t_list	*lst;
	t_list	*to_free;

	lst = data->string_to_put;
	while (lst)
	{
		if (((t_strput *)lst->content)->str)
			free(((t_strput *)lst->content)->str);
		free(lst->content);
		to_free = lst;
		lst = lst->next;
		free(to_free);
	}
	data->string_to_put = NULL;
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
	clear_string_put(data);
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
