/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmuravch <hmuravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 15:51:19 by hmuravch          #+#    #+#             */
/*   Updated: 2018/09/24 12:30:24 by hmuravch         ###   ########.fr       */
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

// void	ft_lstdel(t_list **alst)
// {
// 	if (alst && *alst && del)
// 	{
// 		while (*alst)
// 		{
// 			free(*alst);
// 			*alst = (*alst)->next;
// 		}
// 		*alst = NULL;
// 	}
// }

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

static inline void  fill_len(t_rm *start)
{
    t_rm            *tmp_start;
    t_rm            *save;
    int             len;

    len = 1;
    tmp_start = find_start(start);
    while (tmp_start)
    {
		if (find_black_room(tmp_start->link))
            save = find_black_room(tmp_start->link);
		else
			break ;
        while (tmp_start->link)
        {
            if ((tmp_start->link->room->len > len) || (tmp_start->link->room->len == -1))
                tmp_start->link->room->len = len;
            tmp_start->link = tmp_start->link->next;
        }
        len++;
        tmp_start = save;
    }
}

void				algorithm(t_lm *lm)
{
	fill_len(lm->start);
}
