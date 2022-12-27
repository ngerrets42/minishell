/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_alloc.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 14:42:02 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/11/09 17:49:49 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef N_ALLOC_H
# define N_ALLOC_H

# include "n_mem.h"
# include <unistd.h>

typedef struct s_buffer
{
	void	*mem;
	size_t	max_size;
	size_t	curr_size;
}	t_buffer;

//	alloc.c
void		*n_zalloc(size_t size);
void		*n_zalloc_array(size_t amount, size_t size);
void		*n_realloc(void *p, size_t old_size, size_t new_size);
void		n_free_array(void *array, size_t count);

//	buffer.c
t_buffer	n_buffer_alloc(size_t size);
size_t		n_buffer_add(t_buffer *buffer, const void *data, size_t data_size);
ssize_t		n_buffer_write(t_buffer buffer, int fd);

#endif // N_ALLOC_H
