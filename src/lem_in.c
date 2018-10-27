/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmuravch <hmuravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 05:06:06 by hmuravch          #+#    #+#             */
/*   Updated: 2018/10/28 01:37:17 by hmuravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		error_manager(int error)
{
	error == -1 ? ft_printf("Error: Fail reading\n") : false;
	error == 0 ? ft_printf("Error: Abort program\n") : false;
	error == 4 ? ft_printf("Error: Invalid ants\n") : false;
	error == 5 ? ft_printf("Error: Invalid coordinates\n") : false;
	error == 6 ? ft_printf("Error: Invalid name of room\n") : false;
	error == 7 ? ft_printf("Error: such room already exists\n") : false;
	error == 8 ? ft_printf("Error: Invalid input\n") : false;
	error == 9 ? ft_printf("Error: Room after links\n") : false;
	error == 10 ? ft_printf("Error: Excess exit or start\n") : false;
	error == 11 ? ft_printf("Error: No such name of room\n") : false;
	error == 12 ? ft_printf("Error: Wrong amount of start or end\n") : false;
	error == 13 ? ft_printf("Error: NO WAY\n") : false;
	exit(1);
}

void		parsing(t_lm *lm, int index)
{
	char	*tmp;
	char	*line;

	while ((lm->error = get_next_line(0, &line)) > 0)
	{
		tmp = malloc(sizeof(char) * ft_strlen(line) + 1);
		ft_strcpy(tmp, line);
		lm->input[lm->i++] = tmp;
		if (line[0] == '#' && !check_line(line))
			ft_strdel(&line);
		else if (lm->ant_amount == 0)
			read_ants(line, lm);
		else if (ft_strequ(line, "##go"))
			break ;
		else if (line[0] == '#' && line[1] == '#')
			index == 0 ? index = read_hash(line) : error_manager(10);
		else if (ft_strchr(line, ' '))
			read_room(line, &index, lm);
		else if (ft_strchr(line, '-'))
			read_link(line, lm);
		else
			break ;
	}
	if (lm->error == -1 || (lm->error == 0 && lm->ant_amount == 0))
		error_manager(lm->error);
}

int			main(void)
{
	t_lm	lm;
	t_q		que;
	t_w		*right_way;
	int		j;

	j = 0;
	ft_bzero(&lm, sizeof(t_lm));
	ft_bzero(&que, sizeof(t_q));
	lm.input = ft_memalloc(sizeof(char *) * 10000000);
	parsing(&lm, 0);
	if (!(check_end_start(&lm)))
		error_manager(12);
	fill_len(&que, &lm);
	if (!(right_way = find_way(&lm)))
		error_manager(13);
	while (j < lm.i)
		ft_printf("%s\n", lm.input[j++]);
	print_ants(&lm, right_way);
}
