/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 22:20:14 by gmassoni          #+#    #+#             */
/*   Updated: 2024/10/11 03:46:12 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tabcpy(char **dst, char **src)
{
	int	i;

	i = 0;
	while (dst && src && src[i])
	{
		dst[i] = src[i];
		i++;
	}
}

void	ft_tablcpy(char **dst, char **src, size_t size)
{
	size_t	i;

	i = 0;
	while (dst && src && i < size)
	{
		dst[i] = src[i];
		i++;
	}
}
