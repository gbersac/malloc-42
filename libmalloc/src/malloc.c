/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 12:36:45 by gbersac           #+#    #+#             */
/*   Updated: 2015/01/23 19:43:50 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	split_block(t_block *b, size_t mem_width)
{
	t_block	*nb;

	if (b->size + BLOCK_SIZE == mem_width)
		return ;
	if (mem_width < b->size + BLOCK_SIZE * 2){
		b->size = mem_width - BLOCK_SIZE;
		return ;
	}
	nb = (t_block*)(BDATA(b) + BLOCK_SIZE + b->size);
	printf("ici last\n");
	init_block(nb, mem_width - BLOCK_SIZE * 2  - b->size);
	nb->next = b->next;
	b->next = nb;
	nb->prev = b;
	nb->isFree = 1;
}

t_block *search_freed_block(size_t size)
{
	t_block	*b;
	size_t	mem_width;

	b = first_heap(NULL);
	while (b != NULL && !(b->isFree && b->size >= size))
		b = b->next;
	if (b == NULL)
		return (NULL);
	mem_width = b->size + BLOCK_SIZE;
	b->size = size;
	split_block(b, mem_width);
	b->isFree = 0;
	return (b);
}

size_t	size_page(size_t size)
{
	size_t	to_return;
	size_t	min;

	to_return = getpagesize();
	min = (size + BLOCK_SIZE);
	while (to_return < min)
		to_return *= 2;
	return to_return;
}

t_block	*alloc_new_block(size_t size)
{
	t_block	*b;
	size_t	len;

	len = size_page(size);
	b = (t_block*)mmap(NULL,
			len,
			PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON,
			-1,
			0);
	init_block(b, size);
	split_block(b, len);
	printf("ici\n");

	//append block at the end
	if (first_heap(NULL) == NULL)
	{
		first_heap(b);
		last_heap(b);
	}
	else
	{
		b->prev = last_heap(NULL);
		last_heap(NULL)->next = b;
		last_heap(b);
	}
	return (b);
}

void	*malloc_b(size_t size)
{
	t_block *b;

	b = search_freed_block(size);
	printf("ici\n");
	if (b == NULL)
		b = alloc_new_block(size);
	if (b == NULL)
		return NULL;
	return (b);
}

void	*malloc(size_t size)
{
	t_block	*b;

	b = malloc_b(size);
	return (BDATA(b));
}
