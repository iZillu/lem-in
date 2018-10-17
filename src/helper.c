/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmuravch <hmuravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 21:00:12 by hmuravch          #+#    #+#             */
/*   Updated: 2018/09/30 21:30:31 by hmuravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			check_end_start(t_lm *lm)
{
	t_rm	*tmp;
	int		check;

	check = 0;
	tmp = lm->start;
	while (tmp)
	{
		if (tmp->is_end)
			check++;
		if (tmp->is_start)
			check++;
		tmp = tmp->next;
	}
	if (check == 2)
		return (1);
	return (0);
}

void		read_ants(char *line, t_lm *lm)
{
	const int		ant_num = ft_atoi(line);

	if (ft_strlen(line) != ft_strlen_int(ant_num)
	|| !ft_isdigit(*line) || ant_num < 0)
		error_manager(4);
	lm->ant_amount = ant_num;
	ft_strdel(&line);
}
