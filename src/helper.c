/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmuravch <hmuravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 21:00:12 by hmuravch          #+#    #+#             */
/*   Updated: 2018/10/28 00:54:20 by hmuravch         ###   ########.fr       */
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

int			check_line(char *line)
{
	if (ft_strequ(line, "##end") || ft_strequ(line, "##start")
		|| ft_strequ(line, "##go"))
		return (1);
	if (ft_strequ(line, "##info"))
		execute_command(1);
	return (0);
}

void		read_ants(char *line, t_lm *lm)
{
	const int		ant_num = ft_atoi(line);

	if (ft_strlen(line) != ft_strlen_int(ant_num)
	|| !ft_isdigit(*line) || ant_num <= 0)
		error_manager(4);
	lm->ant_amount = ant_num;
	ft_strdel(&line);
}

void		execute_command(int cmd)
{
	if (cmd == 1)
		ft_printf("• The goal of this program is to find the quickest way to " \
		"get 'n' ants across the farm.\n• Obviously, there are some basic con" \
		"straints. To be the first to arrive, ants will need to take the shor" \
		"test path (and that isn’t necessarily the simplest). They will also " \
		"need to avoid traffic jams as well as walking all over their fellow " \
		"ants.\n• At the beginning of the game, all the ants are in the room " \
		"##start. The goal is to bring them to the room ##end with as few tur" \
		"ns as possible. Each room can only contain one ant at a time. (excep" \
		"t at '##start' and '##end' which can contain as many ants as necessa" \
		"ry.)\n• At each turn program will display only the ants that moved.\n"\
		"• At each turn program can move each ant only once and through a tub" \
		"e (the room at the receiving end must be empty).\n• You can use coma" \
		"nd '##go' for start program 😉\n");
}
