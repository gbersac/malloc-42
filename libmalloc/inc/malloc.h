/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 12:35:28 by gbersac           #+#    #+#             */
/*   Updated: 2015/01/29 14:43:40 by gbersac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# define BLOCK_SIZE	(sizeof(t_block))
# define BDATA(b)	((void*)((char*)b + sizeof(t_block) + 1))

# define PAGE_SIZE	(sizeof(t_page))
# define PDATA(p)	((void*)((char*)p + sizeof(t_page) + 1))

# define TINY_LENGTH		8192
# define TINY_MAX_ALLOC		128

# define SMALL_LENGTH		65536
# define SMALL_MAX_ALLOC	1024

# include <stdlib.h>
# include <sys/mman.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

void				free(void *ptr);
void				*malloc(size_t size);
void				*malloc_b(size_t size);
void				*realloc(void *ptr, size_t size);
void				show_alloc_mem(void);

typedef enum		e_page_type
{
	TINY,
	SMALL,
	LARGE
}					t_page_type;

struct s_block;

/*
** Pages contains blocks.
*/
typedef struct		s_page
{
	t_page_type		type;
	size_t			size;
	struct s_page	*prev;
	struct s_page	*next;
	struct s_block	*first;
	int				nb_block;
}					t_page;

/*
** A block contains one malloc.
*/
typedef struct		s_block
{
	size_t			size;
	struct s_block	*prev;
	struct s_block	*next;
	int				is_free;
}					t_block;

t_page				*first_page();
void				init_block(void *a, size_t b);
void				init_page(void *ptr, t_page_type size, size_t block_size);
void				add_page(t_page *new_page);
t_block				*get_block_from_ptr(void *p);

void				print_chain(t_block *b);
void				print_block(t_block *b);

t_block				*alloc_new_block(size_t size);
size_t				page_length(size_t size);
size_t				page_length_2(t_page_type size);
void				split_block(t_block *b, size_t mem_width);
t_page_type			page_type(size_t size);
t_page				*block_parent_page(t_block *b);

void				del_page(t_page *page);
void				free_all(void);
t_block				*search_ptr(void *ptr);

void				ft_putstr(char const *str);
void				ft_put_addr(void *addr);
char				*ft_itoa(int n);
char				*put_addr(void *addr);
void				ft_putnbr(int n);

#endif
