/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmuravch <hmuravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 05:37:51 by hmuravch          #+#    #+#             */
/*   Updated: 2018/09/18 04:03:06 by hmuravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline t_rm	**get_last_room(t_rm **poi)
{
	t_rm			*tmp;

	if (*poi == NULL)
		return (poi);
	tmp = *poi;
	while (tmp->next)
		tmp = tmp->next;
	return (&tmp->next);
}

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

static inline void	read_link(char *line, t_lm *lm)
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

static inline void	check_room(char *line, t_lm *lm, t_rm *cur)
{
	t_rm	*tmp;

	tmp = lm->start;
	if (*cur->name == 'L' || *cur->name == '#' || ft_strchr(cur->name, '-'))
		error_manager(15);
	while (tmp)
	{
		if (cur != tmp)
			if (cur->name == tmp->name
			|| (cur->x == tmp->x && cur->y == tmp->y))
				error_manager(9);
		tmp = tmp->next;
	}
}

static inline void	read_room(char *line, int *index, t_lm *lm)
{
	t_rm **const	cur = get_last_room(&lm->start);
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
	check_room(line, lm, *cur);
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
	const bool		is_start = (ft_strequ(line, "##start"));
	const bool		is_end = (ft_strequ(line, "##end"));

	free(line);
	if (is_start)
	{
		check += 2;
		if (check != 0 && check != 2 && check != 3 && check != 5)
			error_manager(6);
		return (1);
	}
	else if (is_end)
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
	const int		ant_num = ft_atoi(line);

	if (ft_strlen(line) != ft_strlen_int(ant_num)
	|| !ft_isdigit(*line) || ant_num < 0)
		error_manager(4);
	lm->ant_amount = ant_num;
	lm->head = ft_memalloc(ant_num);
	free(line);
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
		*m = ft_lstnew(line, 0);
		m = &(*m)->next;
		if (line[0] == '#')
			index = read_hash(line);
		else if (ft_strchr(line, ' '))
			read_room(line, &index, lm);
		else if (ft_strchr(line, '-'))
			read_link(line, lm);
		else if (lm->ant_amount == 0)
			alloc_ants(line, lm);
		else
			error_manager(lm->error);
	}
	if (lm->error == -1)
		error_manager(lm->error);
	print_map(lm);
}
