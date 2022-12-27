/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_protect.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 14:31:13 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/07 14:05:48 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef N_PROTECT_H
# define N_PROTECT_H

typedef void	(*t_protect_f)(void);

void		n_error_and_exit(void);
t_protect_f	n_protect_setf(t_protect_f func);
void		*n_protect(void *ptr);

#endif // N_PROTECT_H
