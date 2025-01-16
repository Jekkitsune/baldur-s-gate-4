/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_to_str_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:24:24 by fparis            #+#    #+#             */
/*   Updated: 2025/01/16 19:24:40 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strndup(char *s, int n)
{
	char	*res;
	int		size;
	int		i;

	size = ft_strlen(s);
	if (!size || n <= 0)
		return (NULL);
	if (size > n)
		size = n;
	res = ft_calloc(sizeof(char), size + 1);
	if (!res)
		return (res);
	i = 0;
	while (i < size)
	{
		res[i] = s[i];
		i++;
	}
	return (res);
}

char	*ft_ctos(char c)
{
	char	*res;

	res = ft_calloc(sizeof(char), 2);
	if (!res)
		return (res);
	res[0] = c;
	return (res);
}
