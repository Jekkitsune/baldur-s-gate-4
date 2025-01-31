/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:36:32 by mbico             #+#    #+#             */
/*   Updated: 2025/01/30 21:55:50 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int	nbr;
	int	sign;

	nbr = 0;
	sign = 1;
	if (!nptr)
		return (0);
	while ((*nptr && *nptr == ' ') || (*nptr && *nptr >= 9 && *nptr <= 13))
		nptr ++;
	if (*nptr && (*nptr == '+' || *nptr == '-'))
	{
		if (*nptr == '-')
			sign = -1;
		nptr ++;
	}
	while (*nptr && *nptr >= '0' && *nptr <= '9')
	{
		nbr = nbr * 10 + (*nptr - '0');
		nptr ++;
	}
	nbr *= sign;
	return (nbr);
}
