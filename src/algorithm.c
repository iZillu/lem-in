/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmuravch <hmuravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 15:51:19 by hmuravch          #+#    #+#             */
/*   Updated: 2018/09/27 16:28:46 by hmuravch         ###   ########.fr       */
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

void                fill_len(t_q *que, t_lm *lm)
{
    t_link          *tmp_link;
	t_rm			*black_room;
	t_rm			*cur_room;
	t_q				*start_que;
	int             len;

	cur_room = find_start(lm->start);
	start_que = que;
	while (cur_room)
	{
		len = cur_room->len + 1;
        tmp_link = cur_room->link;
		while (find_black_room(tmp_link))
		{
			black_room = find_black_room(tmp_link);
			que->room = black_room;
			black_room->len = len;
			tmp_link = tmp_link->next;
			que = que->next = malloc(sizeof(t_q));
		}
        cur_room = start_que->room;
		start_que = start_que->next;
    }
}

static inline t_rm	*find_prev_room(t_link *cur_room, int len)
{
    t_link  *tmp;

    tmp = cur_room;
    while (tmp)
    {
        if (tmp->room->len == (len - 1) && (!tmp->room->used))
            return (tmp->room);
        tmp = tmp->next;
    }
    return (NULL);
}

t_w				*find_way(t_w *way, t_lm *lm)
{
    t_rm		*cur_room;
	t_w			*right_way;
	t_w			*start_way;

    cur_room = find_end(lm->start);
	right_way = way;
	start_way = right_way;
	right_way->room = cur_room;
	right_way = right_way->next = malloc(sizeof(t_w));
	while (cur_room)
	{
		if (!(right_way->room = find_prev_room(cur_room->link, cur_room->len)))
			return (NULL);
		cur_room = right_way->room;
		cur_room->used = 1;
        if (cur_room->len == 0)
            return (start_way);
		right_way = right_way->next = malloc(sizeof(t_w));
	}
	return (start_way);
}
