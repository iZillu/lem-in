/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmuravch <hmuravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 05:37:51 by hmuravch          #+#    #+#             */
/*   Updated: 2018/09/16 23:00:38 by hmuravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline t_rm	**get_last_room(t_lm *lm)
{
	t_rm	*tmp;

	if (lm->start == NULL)
		return (&lm->start);
	tmp = lm->start;
	while (tmp->next)
		tmp = tmp->next;
	return (&tmp->next);
}

static inline void	read_room(char *line, int *index, t_lm *lm)
{
	t_rm **const	cur = get_last_room(lm);
	const size_t	len = ft_strlen(line);
	char			*x;
	char			*y;

	*cur = ft_memalloc(sizeof(t_rm));
	x = ft_strchr(line, ' ');
	if (x != NULL)
		y = ft_strchr(x + 1, ' ');
	if (x == NULL || y == NULL || !ft_isdigit(x[1]) || !ft_isdigit(y[1]))
		error_manager(5);
	(*cur)->name = line;
	(*cur)->x = ft_atoi(x);
	(*cur)->y = ft_atoi(y);
	*x = '\0';
	if ((ft_strlen((*cur)->name) + 2
	+ ft_strlen_int((*cur)->x) + ft_strlen_int((*cur)->y)) != len)
		error_manager(8);
	(*cur)->is_start = (*index == 1);
	(*cur)->is_end = (*index == 2);
	*index = 0;
}

static inline int	read_hash(char *line)
{
	static int		check = 0;

	if (ft_strequ(line, "##start"))
	{
		check += 2;
		if (check != 0 && check != 2 && check != 3 && check != 5)
			error_manager(6);
		return (1);
	}
	else if (ft_strequ(line, "##end"))
	{
		check += 3;
		if (check != 0 && check != 2 && check != 3 && check != 5)
			error_manager(6);
		return (2);
	}
	return (0);
}

static inline void	alloc_ants(char *line, t_lm *lm)
{
	int			ant_num;

	if (get_next_line(0, &line) > 0)
	{
		if (ft_strlen(line) != ft_strlen_int((ant_num = ft_atoi(line))))
			error_manager(4);
		lm->ant_ammount = ant_num;
		lm->head = ft_memalloc(ant_num);
		lm->map = ft_lstnew(line, 0);
	}
	else
		error_manager(3);
}

void				parsing(t_lm *lm)
{
	char	*line = NULL;
	int		index;
	t_list	*m;

	index = 0;
	alloc_ants(line, lm);	
	m = lm->map;
	while ((lm->error = get_next_line(0, &line)) > 0)
	{
		m->next = ft_lstnew(line, 0);
		m = m->next;
		if (line[0] == '#')
			index = read_hash(line);
		else
		{
			if (ft_strchr(line, ' '))
				read_room(line, &index, lm);
			// else
				// read_link(line, &index, lm);
			continue ;
		}

		free(line);
	}
	if (lm->error == -1)
		error_manager(lm->error);
	m = lm->map;
	while (m)
	{
		ft_printf("%s", m->content);
		m = m->next;
	}
}