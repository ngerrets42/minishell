/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/24 14:58:49 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/11/30 15:25:03 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int	ft_atoi(const char *str)
{
	int		negative;
	int		nbr;
	size_t	i;

	negative = 1;
	nbr = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
		negative = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (nbr * negative);
		nbr *= 10;
		nbr += str[i] - '0';
		i++;
	}
	return (nbr * negative);
}
