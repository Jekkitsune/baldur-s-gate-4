/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:22:54 by mbico             #+#    #+#             */
/*   Updated: 2024/10/17 20:48:08 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!new)
		return ;
	tmp = new;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = *lst;
	*lst = new;
}
