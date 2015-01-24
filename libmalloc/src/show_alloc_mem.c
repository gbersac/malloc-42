/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 15:38:58 by gbersac           #+#    #+#             */
/*   Updated: 2015/01/23 14:15:40 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	show_alloc_mem(void)
{
	t_block	*iter;

	iter = first_heap(NULL);
	if (iter == NULL)
		printf("is null\n");
	while (iter != NULL)
	{
		if (iter->prev != NULL)
			printf("offset %zu\n", iter->data - iter->prev->data + iter->prev->size);
		printf("%p - %p : %zu octet ", iter->data,
				iter->data + iter->size,
				iter->size);
		if (iter->isFree)
			printf("freed");
		printf("\n");
		iter = iter->next;
	}
}

void	print_all(void)
{
	print_chain(first_heap(NULL));
}

void	print_chain(t_block *b)
{
	while (b != NULL)
	{
		// if (b->prev != NULL)
		// 	printf("offset %zu\n", b - b->prev + b->prev->size);
		print_block(b);
		b = b->next;
	}
}

void	print_block(t_block *b)
{
	if (b == NULL){
		printf("This block is NULL\n");
		return ;
	}
	printf("block[%zu]{add: %p, previous: ", b->size, b);
	if (b->prev == NULL)
		printf("NULL");
	else
		printf("%p", b->prev);
	printf(", next: ");
	if (b->next == NULL)
		printf("NULL");
	else
		printf("%p", b->next);
	printf("}");
	if (b->isFree)
		printf(" freed");
	printf("\n");
}
