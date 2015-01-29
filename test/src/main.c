/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 15:34:47 by gbersac           #+#    #+#             */
/*   Updated: 2015/01/29 15:15:31 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "test.h"

void	test_free()
{
	t_block	*b1 = malloc_b(10);
	malloc_b(20);
	t_block	*b3 = malloc_b(30);
	// printf("\n###before free\n");
	// print_all();
	// printf("\n");

	// printf("\n###free1\n");
	free(BDATA(b1));
	// printf("###after free\n");
	// print_all();

	// printf("\n###free2\n");
	free(BDATA(b3));
	// printf("###after free\n");
	// print_all();

	// printf("\nassert %zu == %zu\n", b1->next->next->size, TINY_LENGTH - 60 - 4 * BLOCK_SIZE - PAGE_SIZE);
	assert(b1->next->next->size == TINY_LENGTH - 30 - 4 * BLOCK_SIZE - PAGE_SIZE);
}

void	test_malloc()
{
	t_block*	p1 = malloc_b(16);
	t_block*	p2 = malloc_b(32);
	t_block*	p3 = malloc_b(64);

	// printf("\n");
	// printf("%p == %p\n", BDATA(p1), (char*)p1 + BLOCK_SIZE + 1);
	assert(BDATA(p1) == (char*)p1 + BLOCK_SIZE + 1);
	// printf("%p == %p\n", BDATA(p2), (char*)p1 + p1->size + BLOCK_SIZE * 2 + 1);
	assert(BDATA(p2) == (char*)p1 + p1->size + BLOCK_SIZE * 2 + 1);
	// printf("%p == %p\n", BDATA(p3), (char*)p1 + p1->size + p2->size + BLOCK_SIZE * 3 + 1);
	assert(BDATA(p3) == (char*)p1 + p1->size + p2->size + BLOCK_SIZE * 3 + 1);

	malloc(TINY_MAX_ALLOC + 1);
	malloc(SMALL_MAX_ALLOC + 1);

	assert(first_page() != NULL &&
			first_page()->next != NULL &&
			first_page()->next->next != NULL);
	t_page *page2 = first_page()->next;
	t_page *page3 = first_page()->next->next;
	assert(page2->type == SMALL);
	assert(page3->type == LARGE);
	int i = 0;
	while (i < 50){
		malloc(TINY_MAX_ALLOC - 1);
		++i;
	}
	t_page *page4 = page3->next;
	assert(page4 != NULL);
	assert(page4->type == TINY);
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

void	test_realloc()
{
	t_block*	p2 = malloc_b(32);
	malloc(64);

	//test impossible realloc
	void *ptr1 = realloc(BDATA(p2), 33);
	assert(ptr1 != BDATA(p2) && p2->is_free);

	void *ptr2 = realloc(ptr1, 68);
	// printf("assert %p == %p\n", ptr2, ptr1);
	assert(ptr2 == ptr1);
}

void	test_parent_page()
{
	t_block	*b1 = malloc_b(TINY_MAX_ALLOC - 1);
	t_block	*b2 = malloc_b(SMALL_MAX_ALLOC - 1);

	t_page	*page1 = block_parent_page(b1);
	t_page	*page2 = block_parent_page(b2);
	// printf("block  %p\n", b1);
	// printf("assert %p == %p\n", page, first_page());
	assert(page1 == first_page() && page2 == first_page()->next);
}

void	test_free_munmap()
{
	void	*b1 = malloc(TINY_MAX_ALLOC - 1);
	void	*b2 = malloc(TINY_MAX_ALLOC - 1);

	free(b1);
	free(b2);
	assert(first_page() == NULL);
}

int		main()
{
	printf("size page %i size s_page %zu size s_block %zu\n",
			getpagesize(),
			PAGE_SIZE,
			BLOCK_SIZE);
	one_test(test_malloc, "malloc");
	one_test(test_free, "free");
	one_test(test_malloc_search_freed_block, "malloc_search_freed_block");
	one_test(test_realloc, "realloc");
	one_test(test_parent_page, "parent_page");
	one_test(test_free_munmap, "free_munmap");
	return (0);
}
