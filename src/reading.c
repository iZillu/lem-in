/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmuravch <hmuravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 06:25:55 by hmuravch          #+#    #+#             */
/*   Updated: 2018/10/17 20:28:18 by hmuravch         ###   ########.fr       */
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

static inline void	check_validity_of_room(t_lm *lm, t_rm *cur)
{
	t_rm			*tmp;

	tmp = lm->start;
	if (*cur->name == 'L' || *cur->name == '#')
		error_manager(6);
	while (tmp)
	{
		if (cur != tmp)
		{
			if (cur->x == tmp->x && cur->y == tmp->y)
				error_manager(5);
			if (ft_strequ(tmp->name, cur->name))
				error_manager(7);
		}
		tmp = tmp->next;
	}
}

int					validate_coords(char *x, char *y)
{
	int				i;
	int				j;

	j = 1;
	i = 1;
	if (x[i] == '-')
		i++;
	if (y[j] == '-')
		j++;
	while (x[i] && x[i] != ' ')
		if (!ft_isdigit(x[i++]))
			return (0);
	while (y[j])
		if (!ft_isdigit(y[j++]))
			return (0);
	return (1);
}

void				read_room(char *line, int *index, t_lm *lm)
{
	t_rm **const	cur = get_last_room(&lm->start);
	const size_t	len = ft_strlen(line);
	char			*x;
	char			*y;

	*cur = ft_memalloc(sizeof(t_rm));
	lm->start->link != NULL ? error_manager(9) : false;
	x = ft_strchr(line, ' ');
	if (x != NULL)
		y = ft_strchr(x + 1, ' ');
	if (x == NULL || y == NULL || (!(validate_coords(x, y))))
		error_manager(5);
	(*cur)->name = line;
	(*cur)->x = ft_atoi(x);
	(*cur)->y = ft_atoi(y);
	(*index == 1) ? ((*cur)->len = 0) : false;
	(*index != 1) ? ((*cur)->len = -1) : false;
	*x = '\0';
	check_validity_of_room(lm, *cur);
	if ((ft_strlen((*cur)->name) + 2
	+ ft_strlen_int((*cur)->x) + ft_strlen_int((*cur)->y)) != len)
		error_manager(8);
	(*index == 1) ? (*cur)->is_start = 1 : false;
	(*index == 2) ? (*cur)->is_end = 1 : false;
	*index = 0;
}

int					read_hash(char *line)
{
	static int		check = 0;
	const bool		is_start = (ft_strequ(line, "##start"));
	const bool		is_end = (ft_strequ(line, "##end"));
	const bool		is_info = (ft_strequ(line, "##info"));

	free(line);
	if (is_start)
	{
		check += 2;
		if (check != 2 && check != 3 && check != 5)
			error_manager(10);
		return (1);
	}
	else if (is_end)
	{
		check += 3;
		if (check != 2 && check != 3 && check != 5)
			error_manager(10);
		return (2);
	}
	else if (is_info)
		execute_command(1);
	return (0);
}
