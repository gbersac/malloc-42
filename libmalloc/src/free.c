/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 12:36:34 by gbersac           #+#    #+#             */
/*   Updated: 2015/01/23 19:39:55 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block	*ptr_is_valid(void *ptr)
{
	t_block	*b;

	b = first_heap(NULL);
	while (b->next != NULL)
	{
		if (BDATA(b) == ptr)
		{
			return b;
		}
		b = b->next;
	}
	return NULL;
}

t_block	*fusion_block(t_block *beg)
{
	t_block	*end;

	end = beg;
	while (beg->prev != NULL && beg->prev->isFree)
		beg = beg->prev;
	while (end->next != NULL && end->next->isFree)
		end = end->next;
	if (beg == end)
	{
		beg->isFree = 1;
		return (beg);
	}
	printf("fusion\n");
	print_block(beg);
	print_block(end);
	printf("data             %p\n", BDATA(end));
	printf("end point %p\n", BDATA(end) + end->size);
	beg->size = BDATA(end) + end->size - BDATA(beg);
	beg->next = end->next;
	beg->isFree = 1;
	if (beg->next == NULL)
		last_heap(beg);
	return (beg);
}

void	free(void *ptr)
{
	t_block	*b;

	if (ptr == NULL)
		return ;
	b = ptr_is_valid(ptr);
	if (b == NULL)
		return ;
	b = fusion_block(b);
}

