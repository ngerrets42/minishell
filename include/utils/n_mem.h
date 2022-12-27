/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_mem.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 14:31:42 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/11/30 13:03:09 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef N_MEM_H
# define N_MEM_H

# include <stddef.h>

//	A byte is 8 bits (unsigned int of size 1)
typedef __UINT8_TYPE__	t_byte;

//	memory.c
void	*n_memset(void *p, size_t size, t_byte set);
void	*n_memcpy(void *dst, const void *src, size_t size);
void	*n_memdup(const void *src, size_t size);
void	*n_memfind(void *p, size_t size, t_byte find);

#endif // N_MEM_H
