/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmuravch <hmuravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 17:00:36 by hmuravch          #+#    #+#             */
/*   Updated: 2018/10/17 05:45:13 by hmuravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_rm				*find_end(t_rm *start)
{
	t_rm			*tmp;

	tmp = start;
	while (tmp)
	{
		if (tmp->is_end)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

static inline t_rm	*find_prev_room(t_link *cur_room, int len)
{
	t_link			*tmp;

	tmp = cur_room;
	while (tmp)
	{
		if (tmp->room->len == (len - 1) && (!tmp->room->used))
			return (tmp->room);
		tmp = tmp->next;
	}
	return (NULL);
}

t_w					*find_way(t_lm *lm)
{
	t_rm			*cur_room;
	t_w				*right_way;
	t_w				*start;

	cur_room = find_end(lm->start);
	right_way = ft_memalloc(sizeof(t_w));
	start = right_way;
	right_way->room = cur_room;
	right_way->next = ft_memalloc(sizeof(t_w));
	right_way = right_way->next;
	while (cur_room)
	{
		if (!(right_way->room = find_prev_room(cur_room->link, cur_room->len)))
			return (NULL);
		cur_room = right_way->room;
		cur_room->used = 1;
		if (cur_room->len == 0)
			break ;
		if (cur_room)
		{
			right_way->next = ft_memalloc(sizeof(t_w));
			right_way = right_way->next;
		}
	}
	return (start);
}
