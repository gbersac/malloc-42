/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 14:54:55 by gbersac           #+#    #+#             */
/*   Updated: 2015/01/29 15:19:49 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		init_block(void *ptr, size_t s)
{
	t_block	*tb;

	if (ptr == NULL)
		return ;
	tb = (t_block*)ptr;
	tb->size = s;
	tb->next = NULL;
	tb->prev = NULL;
	tb->is_free = 0;
}

t_block		*get_block_from_ptr(void *data)
{
	t_block	*b;

	b = (t_block*)(((char*)data) - BLOCK_SIZE + 4);
	return (b);
}

t_page		*block_parent_page(t_block *b)
{
	t_page	*iter;

	if (b == NULL)
		return (NULL);
	iter = first_page();
	while ((void*)iter < (void*)b)
	{
		if ((void*)iter < (void*)b && PDATA(iter) + iter->size > (void*)b)
			return (iter);
		iter = iter->next;
	}
	return (NULL);
}

void		init_page(void *ptr, t_page_type size, size_t block_size)
{
	t_page	*page;

	page = (t_page*)ptr;
	page->type = page_type(block_size);
	page->size = size;
	page->prev = NULL;
	page->next = NULL;
	page->first = NULL;
}
