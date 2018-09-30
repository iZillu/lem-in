/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmuravch <hmuravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 05:06:06 by hmuravch          #+#    #+#             */
/*   Updated: 2018/09/30 18:47:25 by hmuravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <fcntl.h>
#include <unistd.h>

void	error_manager(int error)
{
	printf("ERROR %i\n", error);
	// error ? ft_printf("ERROR: fail reading\n") : false;
	// error == 1 ? ft_printf("ERROR: invalid line\n") : false;
	//3
	//4
	exit(1);
}

void				print_map(t_lm *lm)
{
	t_list	*m;

	m = lm->map;
	while (m)
	{
		ft_printf("%s", m->content);
		m = m->next;
	}
}

void				parsing(t_lm *lm)
{
	char	*line;
	int		index;
	t_list	**m;

	index = 0;
	m = &lm->map;
	while ((lm->error = get_next_line(0, &line)) > 0)
	{
		*m = ft_lstnew(line, ft_strlen(line));
		m = &(*m)->next;
		if (lm->ant_amount == 0)
			read_ants(line, lm);
		else if (line[0] == '#' && line[1] == '#')
			index == 0 ? index = read_hash(line) : error_manager(43);
		else if (ft_strchr(line, ' '))
			read_room(line, &index, lm);
		else if (ft_strchr(line, '-'))
			read_link(line, lm);
		else if (line[0] == '#')
			;
		else 
			error_manager(lm->error);
	}
	if (lm->error == -1)
		error_manager(lm->error);
}

int		main(int ac, char **av)
{
	t_lm	lm;
	t_q		que;
	t_w		way;
	t_w		*right_way;

	dup2(open(av[1], O_RDONLY), 0);
	ft_bzero(&lm, sizeof(lm));
	parsing(&lm);
	right_way = ft_memalloc(sizeof(t_w));
	fill_len(&que, &lm);
	if (!(right_way = find_way(&way, &lm)))
		error_manager(86);
	print_map(&lm);
	print_ants(&lm, right_way);

	 	/*PRINT WAYS*/
			// printf("Way :\n");
			// while (right_way)
			// {
			// 	printf("%s ---> ", right_way->room->name);
			// 	right_way = right_way->prev;
			// }
			// 	printf(":D");
			// 	printf("\n");
	
		/*PRINT LENS*/
			// while (lm.start)
			// {
			// 	printf("==============\nRoom -> %s\nLen  -> %i\n", lm.start->name, lm.start->len);
			// 	lm.start = lm.start->next;
			// }
			
}
