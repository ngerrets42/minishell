/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/24 14:59:20 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/11/28 14:29:43 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int	static_absi(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		digits;
	int		nbr;
	int		negative;

	digits = 1;
	nbr = n;
	while (nbr / 10 != 0)
	{
		nbr /= 10;
		digits++;
	}
	negative = (n < 0);
	result = malloc(sizeof(char) * (digits + negative + 1));
	if (result == NULL)
		return (NULL);
	result[0] = '-';
	result[digits + negative] = '\0';
	while (digits > 0)
	{
		result[digits - 1 + negative] = '0' + static_absi(n % 10);
		n /= 10;
		digits--;
	}
	return (result);
}
