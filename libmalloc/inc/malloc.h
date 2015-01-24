/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 12:35:28 by gbersac           #+#    #+#             */
/*   Updated: 2015/01/23 19:28:46 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
#define MALLOC_H

#define BLOCK_SIZE	(sizeof(t_block))
#define BDATA(b)	(b + sizeof(t_block) + 1)

#include <stdlib.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void	free(void *ptr);
void	*malloc(size_t size);
void	*malloc_b(size_t size);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem(void);

typedef struct	s_block
{
	size_t			size;
	struct s_block	*prev;
	struct s_block	*next;
	int				isFree;
	char			data[1];
}				t_block;

t_block	*first_heap(t_block*);
t_block	*last_heap(t_block*);
void	init_block(void *, size_t);
t_block	*get_block_from_ptr(void *p);

void	print_all(void);
void	print_chain(t_block *b);
void	print_block(t_block *b);

#endif
