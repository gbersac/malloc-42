/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 12:36:45 by gbersac           #+#    #+#             */
/*   Updated: 2015/01/29 15:21:03 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	split_block(t_block *b, size_t mem_width)
{
	t_block	*nb;

	if (b->size + BLOCK_SIZE == mem_width)
		return ;
	if (mem_width < b->size + BLOCK_SIZE * 2)
	{
		b->size = mem_width - BLOCK_SIZE;
		return ;
	}
	nb = (t_block*)(BDATA(b) + b->size - 1);
	init_block(nb, mem_width - BLOCK_SIZE * 2 - b->size);
	nb->next = b->next;
	b->next = nb;
	nb->prev = b;
	nb->is_free = 1;
}

t_block *search_freed_block_in_page(t_page *p, size_t size)
{
	t_block		*b;

	b = p->first;
	while (b != NULL && !(b->is_free && b->size >= size))
		b = b->next;
	return (b);
}

t_block *search_freed_block(size_t size)
{
	t_page		*page;
	t_block		*b;
	size_t		mem_width;
	t_page_type	mal_type;

	mal_type = page_type(size);
	page = first_page();
	b = NULL;
	while (page != NULL)
	{
		if (page->type == mal_type)
			b = search_freed_block_in_page(page, size);
		if (b != NULL)
			break ;
		page = page->next;
	}
	if (b == NULL)
		return (NULL);
	mem_width = b->size + BLOCK_SIZE;
	b->size = size;
	split_block(b, mem_width);
	b->is_free = 0;
	return (b);
}

void	*malloc_b(size_t size)
{
	t_block *b;

	b = search_freed_block(size);
	if (b == NULL)
		b = alloc_new_block(size);
	if (b == NULL)
		return (NULL);
	return (b);
}

void	*malloc(size_t size)
{
	t_block	*b;

	b = malloc_b(size);
	return (BDATA(b));
}
