/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmuravch <hmuravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 15:51:19 by hmuravch          #+#    #+#             */
/*   Updated: 2018/09/25 17:47:46 by hmuravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline t_rm  *find_start(t_rm *start)
{
    t_rm            *tmp;

    tmp = start;
    while (tmp)
    {
        if (tmp->is_start)
            return (tmp);
        tmp = tmp->next;
    }
    return (tmp);
}

static inline t_rm  *find_black_room(t_link *room)
{
    t_link  *tmp;

    tmp = room;
    while (tmp)
    {
        if (tmp->room->len == -1)
            return (tmp->room);
        tmp = tmp->next;
    }
    return (NULL);
}

static inline t_rm  *find_end(t_rm *start)
{
    t_rm            *tmp;

    tmp = start;
    while (tmp)
    {
        if (tmp->is_end)
            return (tmp);
        tmp = tmp->next;
    }
    return (tmp);
}

static inline void  fill_len(t_rm *start, t_q *que, t_lm *lm)
{
	t_rm			*room;
	t_rm			*iterator;
	t_q				*start_que;
	int             len;

	len = 1;
	iterator = find_start(start);
	start_que = que;
	while (iterator)
	{
		len = iterator->len + 1;
		while ((room = find_black_room(iterator->link)))
		{
			que->room = room;
			room->len = len;
			iterator->link = iterator->link->next;
			que = que->next = malloc(sizeof(t_q));
		}
        iterator = start_que->room;
		start_que = start_que->next;
    }
}

void				algorithm(t_lm *lm)
{
	t_q				que;

	fill_len(lm->start, &que, lm);
}
