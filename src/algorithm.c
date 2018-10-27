/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmuravch <hmuravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 15:51:19 by hmuravch          #+#    #+#             */
/*   Updated: 2018/10/20 04:09:50 by hmuravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline void	check_room_for_ant(t_w *way, int num)
{
	if (!way->room->ant || way->room->is_end)
		if (way->next && way->next->room->ant)
		{
			way->room->ant++;
			way->next->room->ant--;
			ft_printf("L%d-%s ", num, way->room->name);
		}
}

void				print_ants(t_lm *lm, t_w *way)
{
	t_w				*tmp;
	t_rm			*end;
	t_rm			*start;

	ft_printf("\n");
	start = find_start(lm->start);
	start->ant = lm->ant_amount;
	start->num = 1;
	end = find_end(lm->start);
	while (end->ant < lm->ant_amount)
	{
		tmp = way;
		while (tmp)
		{
			if (tmp->next && tmp->next->room->ant)
				tmp->room->num = tmp->next->room->num++;
			check_room_for_ant(tmp, tmp->room->num);
			tmp = tmp->next;
		}
		ft_printf("\n");
	}
}
