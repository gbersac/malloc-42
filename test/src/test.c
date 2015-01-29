/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/28 14:08:14 by gbersac           #+#    #+#             */
/*   Updated: 2015/01/29 15:08:12 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	one_test(void (*fct)(), char *str)
{
	fct();
	free_all();
	printf("OK %s\n", str);
}

void	print_block(t_block *b)
{
	if (b == NULL){
		printf("This block is NULL\n");
		return ;
	}
	printf("block[%5zu]{@ %p, prev: ", b->size, b);
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
	if (b->is_free)
		printf(" freed");
	printf("\n");
}

void	show_page(t_page *page)
{
	t_block	*iter;

	printf("Page %p, type ", page);
	if (page->type == TINY)
		printf("TINY");
	if (page->type == SMALL)
		printf("SMALL");
	if (page->type == LARGE)
		printf("LARGE");
	printf("\n");
	iter = page->first;
	while (iter != NULL)
	{
		print_block(iter);
		iter = iter->next;
	}
}

void	print_all(void)
{
	t_page	*iter;

	iter = first_page();
	if (iter == NULL)
		printf("No allocation\n");
	while (iter != NULL)
	{
		show_page(iter);
		iter = iter->next;
	}
}
