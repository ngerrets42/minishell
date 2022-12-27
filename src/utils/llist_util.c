/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   llist_util.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 11:04:17 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/11/15 11:01:10 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils/llist.h"

size_t	llist_size(t_llist *lst)
{
	size_t	count;
	t_llist	*current;

	if (lst == NULL)
		return (0);
	count = 1;
	current = lst;
	while (current->next != NULL)
	{
		count++;
		current = (t_llist *)current->next;
	}
	return (count);
}

t_llist	*llist_last(t_llist *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	llist_add_back(t_llist **lst, t_llist *new)
{
	t_llist	*last;

	if (lst == NULL)
		return ;
	last = llist_last(*lst);
	if (last != NULL)
		last->next = new;
	else
		*lst = new;
}
