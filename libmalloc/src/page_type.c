/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/28 21:14:10 by gbersac           #+#    #+#             */
/*   Updated: 2015/01/28 21:14:38 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_page_type	page_type(size_t size)
{
	if (size <= TINY_MAX_ALLOC)
		return (TINY);
	if (size <= SMALL_MAX_ALLOC)
		return (SMALL);
	return (LARGE);
}

size_t		page_length(size_t size)
{
	if (size <= TINY_MAX_ALLOC)
		return (TINY_LENGTH);
	if (size <= SMALL_MAX_ALLOC)
		return (SMALL_LENGTH);
	return (size + PAGE_SIZE);
}

size_t		page_length_2(t_page_type size)
{
	if (size == TINY)
		return (TINY_LENGTH);
	if (size == SMALL)
		return (SMALL_LENGTH);
	return (size);
}
