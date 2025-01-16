/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:43:30 by fparis            #+#    #+#             */
/*   Updated: 2025/01/15 20:43:57 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpop(t_list **lst_start, void *check)
{
	t_list	*i;
	t_list	*tmp;

	if (!lst_start || !*lst_start)
		return (NULL);
	i = *lst_start;
	if (i->content == check)
	{
		*lst_start = i->next;
		return (i);
	}
	while (i->next && i->next->content != check)
		i = i->next;
	tmp = i;
	i = i->next;
	if (!i)
		return (NULL);
	tmp->next = i->next;
	return (i);
}
