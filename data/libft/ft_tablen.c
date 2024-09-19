/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:40:56 by gmassoni          #+#    #+#             */
/*   Updated: 2024/09/12 21:41:45 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_tablen(char **tab)
{
	size_t	len;

	if (!tab)
		return (0);
	len = 0;
	while (tab[len])
		len++;
	return (len);
}
