/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmuravch <hmuravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 05:06:06 by hmuravch          #+#    #+#             */
/*   Updated: 2018/10/17 05:53:32 by hmuravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <fcntl.h>
#include <unistd.h>

void		error_manager(int error)
{
	ft_printf("ERROR %i\n", error);
	exit(1);
}

void		parsing(t_lm *lm)
{
	char	*line;
	int		index;

	index = 0;
	while ((lm->error = get_next_line(0, &line)) > 0)
	{
		ft_printf("%s\n", line);
		if (line[0] == '#' && line[1] == '#')
			index == 0 ? index = read_hash(line) : error_manager(43);
		else if (line[0] == '#')
			ft_strdel(&line);
		else if (ft_strchr(line, ' '))
			read_room(line, &index, lm);
		else if (ft_strchr(line, '-'))
			read_link(line, lm);
		else if (lm->ant_amount == 0)
			read_ants(line, lm);
		else
			error_manager(767);
	}
	if (lm->error == -1 || (lm->error == 0 && lm->ant_amount == 0))
		error_manager(lm->error);
}

int			main(int ac, char **av)
{
	t_lm	lm;
	t_q		que;
	t_w		*right_way;

	ft_bzero(&lm, sizeof(t_lm));
	parsing(&lm);
	if (!(check_end_start(&lm)))
		error_manager(224);
	fill_len(&que, &lm);
	if (!(right_way = find_way(&lm)))
		error_manager(86);
	print_ants(&lm, right_way);
}
