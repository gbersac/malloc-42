/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_new_block.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/27 17:56:45 by gbersac           #+#    #+#             */
/*   Updated: 2015/01/28 21:13:21 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_page	*alloc_new_page(size_t block_size)
{
	t_page	*to_return;
	size_t	page_len;

	page_len = page_length(block_size);
	to_return = (t_page*)mmap(NULL,
			page_len,
			PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON,
			-1,
			0);
	init_page(to_return, page_len - PAGE_SIZE, block_size);
	add_page(to_return);
	return (to_return);
}

t_block	*insert_block_inside_new_page(t_page *new_page, size_t block_size)
{
	t_block	*new_block;

	new_block = (t_block*)PDATA(new_page);
	init_block(new_block, block_size);
	if (new_page->type != LARGE)
		split_block(new_block, page_length_2(new_page->size) - BLOCK_SIZE);
	new_page->first = new_block;
	return (new_block);
}

t_block	*alloc_new_block(size_t block_size)
{
	t_block	*new_block;
	t_page	*new_page;

	new_page = alloc_new_page(block_size);
	new_block = insert_block_inside_new_page(new_page, block_size);
	return (new_block);
}
