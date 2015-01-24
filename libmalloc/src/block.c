/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 14:54:55 by gbersac           #+#    #+#             */
/*   Updated: 2015/01/23 19:47:14 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block	*first_heap(t_block *set)
{
	static t_block*	first = NULL;

	if (set != NULL)
		first = set;
	return first;
}

t_block	*last_heap(t_block *set)
{
	static t_block*	last = NULL;

	if (set != NULL){
		while (set->next != NULL)
			set = set->next;
		last = set;
	}
	return last;
}

void	init_block(void *ptr, size_t s)
{
	t_block	*tb;

	if (ptr == NULL)
		return ;
	tb = (t_block*)ptr;
	printf("ici last++ %p\n", ptr);
	tb->size = s;
	tb->next = NULL;
	tb->prev = NULL;
	tb->isFree = 0;
}

t_block	*get_block_from_ptr(void *data)
{
	t_block	*b;

	b = (t_block*)(((char*)data) - BLOCK_SIZE + 4);
	return (b);
}
