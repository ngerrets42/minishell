/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   memory.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 14:28:30 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/11/29 17:22:46 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils/n_mem.h"
#include <stdlib.h>

void	*n_memset(void *p, size_t size, t_byte set)
{
	while (size > 0)
	{
		*((t_byte *)p + size - 1) = set;
		size--;
	}
	return (p);
}

void	*n_memcpy(void *dst, const void *src, size_t size)
{
	while (size > 0)
	{
		*((t_byte *)dst + size - 1) = *((t_byte *)src + size - 1);
		size--;
	}
	return (dst);
}

void	*n_memdup(const void *src, size_t size)
{
	void	*mem;

	mem = malloc(size);
	if (!mem)
		return (NULL);
	n_memcpy(mem, src, size);
	return (mem);
}

//	find byte in memory starting at p, ending at p + size
//	returns NULL if not found.
void	*n_memfind(void *p, size_t size, t_byte find)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (*((t_byte *)p + i) == find)
			return (p + i);
	}
	return (NULL);
}
