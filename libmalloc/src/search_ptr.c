/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/28 16:47:30 by gbersac           #+#    #+#             */
/*   Updated: 2015/01/28 16:48:16 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block	*search_ptr_in_page(t_page *page, void *ptr)
{
	t_block	*iter;

	iter = page->first;
	while (iter != NULL)
	{
		if (ptr == BDATA(iter))
			return (iter);
		iter = iter->next;
	}
	return (NULL);
}

t_block	*search_ptr(void *ptr)
{
	t_page	*page;
	t_block	*block;

	page = first_page();
	while (page != NULL)
	{
		block = search_ptr_in_page(page, ptr);
		if (block != NULL)
			return (block);
		page = page->next;
	}
	return (NULL);
}
