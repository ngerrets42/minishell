/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alloc.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 14:29:26 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/11/15 11:00:34 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils/n_alloc.h"
#include <stdlib.h>

//	Sets memory to 0
void	*n_zalloc(size_t size)
{
	void	*mem;

	mem = malloc(size);
	if (!mem)
		return (NULL);
	n_memset(mem, size, 0);
	return (mem);
}

//	TO BE REMOVED, extremely unneccesary
//	Allocate amount * size
void	*n_zalloc_array(size_t amount, size_t size)
{
	return (n_zalloc(amount * size));
}

//	Allocates a new block of memory and moves old_size bytes from p
//	to the new allocation of size new_size
void	*n_realloc(void *p, size_t old_size, size_t new_size)
{
	void	*mem;

	mem = malloc(new_size);
	if (!mem || !p)
		return (mem);
	if (old_size > new_size)
		old_size = new_size;
	n_memcpy(mem, p, old_size);
	free(p);
	return (mem);
}

//	Frees every element of an array with free()
void	n_free_array(void *array, size_t count)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (i < count)
	{
		free(((void **)array)[i]);
		i++;
	}
	free(array);
}
