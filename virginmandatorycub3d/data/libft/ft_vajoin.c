/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vajoin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:01:01 by fparis            #+#    #+#             */
/*   Updated: 2025/01/03 18:53:42 by fparis           ###   ########.fr       */
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
	{
		va_end(args);
		return (str);
	}
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
	va_end(args);
	return (res);
}
