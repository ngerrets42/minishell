/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   llist.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 11:11:15 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/11/09 17:48:29 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LLIST_H
# define LLIST_H

# include <stdlib.h>

typedef struct s_llist
{
	void			*content;
	struct s_llist	*next;
}	t_llist;

//	function type that can be run on llist content
typedef void	(*t_contentf)(void*);

//	llist_mem.c
t_llist	*llist_new(void *content);
void	llist_del(t_llist *lst, t_contentf del_func);
void	llist_clear(t_llist **lst, t_contentf del_func);

//	llist_util.c
size_t	llist_size(t_llist *lst);
t_llist	*llist_last(t_llist *lst);
void	llist_add_back(t_llist **lst, t_llist *new);

#endif	//	LLIST_H