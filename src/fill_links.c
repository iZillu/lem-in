/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmuravch <hmuravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 06:25:50 by hmuravch          #+#    #+#             */
/*   Updated: 2018/09/18 06:40:03 by hmuravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline t_link	**get_last_link(t_link **link, t_rm *to_check)
{
	t_link			*tmp;

	if (*link == NULL)
		return (link);
	tmp = *link;
	if (to_check == tmp->room)
		return (NULL);
	while (tmp->next)
	{
		tmp = tmp->next;
		if (to_check == tmp->room)
			return (NULL);
	}
	return (&tmp->next);
}

static inline t_rm	*find_room_by_name(char *to_find, t_rm *start)
{
	t_rm			*tmp;

	tmp = start;
	while (tmp)
	{
		if (ft_strequ(tmp->name, to_find))
			return (tmp);
		tmp = tmp->next;
	}
	error_manager(12);
	return (NULL);
}

void				read_link(char *line, t_lm *lm)
{
	char *const		n1 = line;
	char *const		n2 = ft_strchr(line, '-') + 1;
	t_rm 			*room[2];
	t_link 			**link[2];

	*(n2 - 1) = '\0';
	if (ft_strequ(n1, n2))
		return ;
	room[0] = find_room_by_name(n1, lm->start);
	room[1] = find_room_by_name(n2, lm->start);
	link[0] = get_last_link(&room[0]->links, room[1]);
	link[1] = get_last_link(&room[1]->links, room[0]);
	if (link[0] == NULL || link[1] == NULL)
		return ;
	*link[0] = ft_memalloc(sizeof(t_link));
	*link[1] = ft_memalloc(sizeof(t_link));
	(*link[0])->room = room[1];
	(*link[1])->room = room[0];
}