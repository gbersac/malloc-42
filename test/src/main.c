/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 15:34:47 by gbersac           #+#    #+#             */
/*   Updated: 2015/01/23 19:35:41 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "malloc.h"

void	test_free()
{
	t_block	*b1 = malloc_b(100);
	t_block	*b2 = malloc_b(200);
	printf("\nbefore free\n");
	print_all();
	free(b1->data);
	printf("\nafter free\n");
	print_all();
	free(b2->data);
	printf("\nafter free\n");
	print_all();
	assert(b1->size == getpagesize() - BLOCK_SIZE);
}

void	test_malloc()
{
	void *p1 = malloc(100);
	void *p2 = malloc(200);
	void *p3 = malloc(300);
	printf("before free\n");
	print_all();
	printf("\n");

	free(p1);
	free(p2);
	memset(first_heap(NULL)->data, 'a', first_heap(NULL)->size);
	char *lastChar = ((char*)p3) - 1 - BLOCK_SIZE;
	printf("lc : #%c# at add: %p\n\n", *lastChar, lastChar);
	printf("after free\n");
	print_all();
}

void test_malloc_split()
{
	// t_block *p1 = malloc_b(getpagesize());
	// assert(p1->size == getpagesize() - BLOCK_SIZE);

	t_block *p2 = malloc_b(getpagesize() - BLOCK_SIZE);
	assert(p2->size == getpagesize() - BLOCK_SIZE);

	t_block *p3 = malloc_b(getpagesize() - BLOCK_SIZE - 1);
	assert(p3->size == getpagesize() - BLOCK_SIZE);

	t_block *p4 = malloc_b(getpagesize() - BLOCK_SIZE - 100 - BLOCK_SIZE);
	assert(p4->next && p4->next->size == 100 && p4->next->isFree == 1);
}

void test_malloc_search_freed_block()
{
	malloc(100);
	void *p2 = malloc(200);
	malloc(300);
	free(p2);
	void *p3 = malloc(200);
	assert(p2 == p3);
}

void	test_block_addr()
{
	printf("@ size %zu, int size %zu, size_t size %zu, size char[1] %zu\n",
			sizeof(void*),
			sizeof(int),
			sizeof(size_t),
			sizeof(char[1]));
	t_block	*b1 = malloc_b(100);
	print_block(b1);
	printf("@%p\n", b1);
	printf("@%p\n", b1->data);
	printf("%lu\n", (t_block*)b1->data - b1);
}

int		main()
{
	printf("size page %i size block struct %zu\n",
			getpagesize(),
			BLOCK_SIZE);
	test_block_addr();
	// test_malloc_split();
	// test_free();
	// test_malloc_search_freed_block();
	// test_malloc();
	return 0;
}
