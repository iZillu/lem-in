/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_len.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmuravch <hmuravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 16:59:48 by hmuravch          #+#    #+#             */
/*   Updated: 2018/10/17 05:35:37 by hmuravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_rm				*find_start(t_rm *start)
{
	t_rm			*tmp;

	tmp = start;
	while (tmp)
	{
		if (tmp->is_start)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

static inline t_rm	*find_black_room(t_link *room)
{
	t_link			*tmp;

	tmp = room;
	while (tmp)
	{
		if (tmp->room->len == -1)
			return (tmp->room);
		tmp = tmp->next;
	}
	return (NULL);
}

void				fill_len(t_q *que, t_lm *lm)
{
	t_link			*tmp_link;
	t_rm			*black_room;
	t_rm			*cur_room;
	t_q				*start_que;
	int				len;

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
			que->next = ft_memalloc(sizeof(t_q));
			que = que->next;
		}
		cur_room = start_que->room;
		start_que = start_que->next;
	}
}
