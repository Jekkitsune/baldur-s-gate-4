/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_element_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 22:15:29 by gmassoni          #+#    #+#             */
/*   Updated: 2025/01/15 17:15:04 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_add_element_tab(char **tab, char *str)
{
	int		len;
	char	**res;

	len = ft_tablen(tab);
	res = ft_calloc(len + 2, sizeof(char *));
	if (res == NULL)
	{
		free(tab);
		return (NULL);
	}
	ft_tabcpy(res, tab);
	free(tab);
	res[len] = str;
	res[len + 1] = NULL;
	return (res);
}
