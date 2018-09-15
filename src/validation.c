/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmuravch <hmuravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 05:37:51 by hmuravch          #+#    #+#             */
/*   Updated: 2018/09/15 07:20:27 by hmuravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline t_rm	**get_last_room(t_lm *lm)
{
	t_rm	*tmp;

	tmp = lm->start;
	while (tmp)
		tmp = tmp->next;
	return (&tmp);
}

static inline void	read_room(char *line, int *index, t_lm *lm)
{
	t_rm	**const room = get_last_room(lm);
	char	*const x = ft_strstr(line, ' '); 
	char	*const y = ft_strstr(x, ' '); 

	if (x == NULL || !ft_isdigit(x[0]))
		error_manager(5);
	if (y == NULL || !ft_isdigit(y[0]))
		error_manager(5);
	*room = ft_memalloc(sizeof(t_rm));
	(*room)->name = line;
	*((*room)->x - 1) = '\0';
	(*room)->x = ft_atoi(x);
	(*room)->y = ft_atoi(y);
	(*index == 1) ? (*room)->is_start = 1 : false;
	(*index == 2) ? (*room)->is_end = 1 : false;
	*index = 0;
}

static inline int	read_hash(char *line)
{
	static int		check = 0;

	if (check != 0 || check != 2 || check != 3 || check != 5)
		error_manager(6);
	if (ft_strequ(line, "##start"))
	{
		check += 2;
		return (1);
	}
	else if (ft_strequ(line, "##end"))
	{
		check += 3;
		return (2);
	}
	return (0);
}

static inline int	alloc_ants(char *line, t_lm *lm)
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

void				parcing(t_lm *lm)
{
	char	*line;
	int		index;
	t_list	*m;

	index = 0;
	alloc_ants(line, lm);
	m = lm->map;
	while ((lm->error = get_next_line(0, &line)) > 0)
	{
		if (line[0] == '#')
			index = read_hash(line);
		else
			read_room(line, &index, lm);
		// error_manager(1);
		m->next = ft_lstnew(line, 0);
		m = m->next;
		free(line);
	}
	if (lm->error == -1)
		error_manager(lm->error);
	m = lm->map;
	while (m)
	{
		ft_printf("%s\n", m->content);
		m = m->next;
	}
}