/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_to_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:45:13 by fparis            #+#    #+#             */
/*   Updated: 2025/01/16 19:25:07 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strndup(char *s, int n);
char	*ft_ctos(char c);

char	*get_added(char c, va_list args)
{
	if (c == '%')
		return (ft_ctos('%'));
	if (c == 'c')
		return (ft_ctos(va_arg(args, int)));
	if (c == 's')
		return (ft_strdup(va_arg(args, char *)));
	if (c == 'd' || c == 'i')
		return (ft_itoa(va_arg(args, int)));
	return (NULL);
}

void	add_to_str(char **res, char *str)
{
	char	*to_free;

	if (!str || !ft_strlen(str))
		return ;
	if (!*res)
	{
		*res = ft_strdup(str);
		return ;
	}
	to_free = *res;
	*res = ft_strjoin(*res, str);
	free(to_free);
	free(str);
}

int	replace_oldest(t_strput **screen_info, t_list **string_to_put)
{
	int		i;
	int		min_i;
	long	min;
	long	current;
	t_list	*to_free;

	i = 1;
	min_i = 0;
	min = screen_info[0]->duration;
	while (i < MAX_SCREEN_INFO)
	{
		current = screen_info[i]->duration;
		if (current < min)
		{
			min_i = i;
			min = current;
		}
		i++;
	}
	to_free = ft_lstpop(string_to_put, screen_info[min_i]);
	free(((t_strput *)to_free->content)->str);
	free(to_free->content);
	free(to_free);
	screen_info[min_i] = NULL;
	return (min_i);
}

void	put_screen_info(t_data *data, char *str)
{
	t_strput		*to_put;
	unsigned int	i;
	t_vector		pos;

	printf("%s\n", str);
	i = 0;
	while (i < MAX_SCREEN_INFO && data->screen_info[i])
		i++;
	if (i >= MAX_SCREEN_INFO)
		i = replace_oldest(data->screen_info, &data->string_to_put);
	pos.x = data->minimap.pos.x;
	pos.y = data->minimap.pos.y * 2 + data->minimap.UI_size
		+ (data->button_scale_size / 2 * i);
	to_put = strput(str, pos, (float)data->button_scale_size / 2.0, 0xFF000000);
	if (screen_string_put(data, to_put, 20))
		data->screen_info[i] = to_put;
}

void	show_info(t_data *data, char *str, ...)
{
	int		i;
	char	*res;
	va_list	args;

	i = 0;
	res = NULL;
	va_start(args, str);
	while (str && str[i])
	{
		if (str[i] == '%')
		{
			add_to_str(&res, ft_strndup(str, i));
			add_to_str(&res, get_added(str[i + 1], args));
			if (str[i + 1])
			{
				str = &str[i + 2];
				i = -1;
			}
		}
		i++;
	}
	add_to_str(&res, ft_strndup(str, i));
	va_end(args);
	put_screen_info(data, res);
}
