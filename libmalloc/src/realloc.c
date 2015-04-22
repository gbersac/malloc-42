/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 12:36:54 by gbersac           #+#    #+#             */
/*   Updated: 2015/04/22 15:23:52 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block	*fusion(t_block *block, size_t size)
{
	t_block	*next;

	if (block == NULL)
		return (NULL);
	next = block->next;
	if (next == NULL ||
			!next->is_free ||
			next->size + BLOCK_SIZE + block->size < size)
		return (NULL);
	block->size = size;
	block->next = next->next;
	split_block(block, next + next->size + PAGE_SIZE - block);
	return (block);
}

void	*return_default(t_block *b, size_t size)
{
	void	*to_return;

	to_return = malloc(size);
	if (b != NULL)
	{
		b->is_free = 1;
		ft_memcpy(to_return, BDATA(b), size);
	}
	return (to_return);
}

void	*realloc(void *ptr, size_t size)
{
	t_block	*b;
	t_block	*ret;

	if (ptr == NULL)
		return (return_default(NULL, size));
	b = search_ptr(ptr);
	if (b == NULL)
		return (NULL);
	ret = fusion(b, size);
	if (ret == NULL)
		return (return_default(b, size));
	return (ptr);
}
