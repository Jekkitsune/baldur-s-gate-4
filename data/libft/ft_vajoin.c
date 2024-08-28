/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vajoin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:01:01 by fparis            #+#    #+#             */
/*   Updated: 2024/05/07 16:26:25 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_vajoin(char *str, ...)
{
	va_list	args;
	char	*char_arg;
	char	*res;
	char	*new_str;

	va_start(args, str);
	char_arg = va_arg(args, char *);
	if (!char_arg)
		return (str);
	new_str = ft_strjoin(str, char_arg);
	res = new_str;
	char_arg = va_arg(args, char *);
	while (char_arg && new_str)
	{
		new_str = ft_strjoin(res, char_arg);
		free(res);
		res = new_str;
		char_arg = va_arg(args, char *);
	}
	return (res);
}
