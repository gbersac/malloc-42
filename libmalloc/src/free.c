/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 12:36:34 by gbersac           #+#    #+#             */
/*   Updated: 2015/01/29 14:44:35 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block	*fusion_block(t_block *beg)
{
	t_block	*end;

	end = beg;
	while (beg->prev != NULL && beg->prev->is_free)
		beg = beg->prev;
	while (end->next != NULL && end->next->is_free)
		end = end->next;
	if (beg == end)
	{
		beg->is_free = 1;
		return (beg);
	}
	beg->size = BDATA(end) + end->size - BDATA(beg);
	beg->next = end->next;
	beg->is_free = 1;
	return (beg);
}

void	check_page(t_block *b)
{
	t_page	*page;
	t_block	*first;

	page = block_parent_page(b);
	first = page->first;
	if (first != NULL &&
			first->is_free &&
			first->next == NULL)
		del_page(page);
}

void	free(void *ptr)
{
	t_block	*b;

	if (ptr == NULL)
		return ;
	b = search_ptr(ptr);
	if (b == NULL)
		return ;
	b = fusion_block(b);
	check_page(b);
}
