/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmuravch <hmuravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 05:37:51 by hmuravch          #+#    #+#             */
/*   Updated: 2018/09/16 08:12:41 by hmuravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// static inline t_rm	**get_last_room(t_rm **room)
// {
// 	t_rm	**tmp;

// 	*tmp = lm->start;
// 	while (*tmp)
// 	{
// 		// write(1, "aaa\n", 4);
// 		// printf("name is %s\n", tmp->name);
// 		*tmp = (*tmp)->next;
// 	}
// 	return (tmp);
// }

static inline t_rm	*read_room(char *line, int *index, t_lm *lm)
{
	// t_rm	*room;
	char	*x = NULL; 
	char	*y = NULL;
	size_t	len;
	t_rm	*cur;

	// room = get_last_room(lm);
	// write(1, "AAA\n", 4);
	// while (room)
	// {
	// 	write(1, "asd\n", 4);
	// 	room = room->next;
	// }
	// if (lm->start)
	// {
	// 	lm->start = malloc(sizeof(t_rm));
	// 	lm->room = lm->start;
	// }
	// else
	// {
	// 	cur = lm->start;
	// 	while (cur)
	// 	{
	// 		cur = cur->next;
	// 	}
	// 	lm->room = cur;
	// 	lm->room = malloc(sizeof(t_rm));
	// }
	// printf("%p\n", lm->room);
	// printf("%p\n", lm->room);
	lm->room = ft_memalloc(sizeof(t_rm));
	ft_strchr(line, ' ') ? x = ft_strchr(line, ' ') + 1 : false;
	// write(1, "ASD\n", 4);
	if (x)
		ft_strchr(x, ' ') ? y = ft_strchr(x, ' ') + 1 : false;
	
	// if (ft_strchr(line, '-') && !ft_strchr(line, ' '))
	// {
	// 	write(1, "AAA\n", 4);
	// 	while (lm->start)
	// 	{
	// 		write(1, "SUKA\n", 5);
	// 		// printf("name is %s\n", lm->start->name);
	// 		lm->start = lm->start->next;
	// 	}
	// }
	len = ft_strlen(line);
	(x == NULL) || (!ft_isdigit(x[0])) ? error_manager(5) : false;
	(y == NULL) || (!ft_isdigit(y[0])) ? error_manager(5) : false;
	line[x - line - 1] = '\0'; 
	lm->room->name = line;
	// printf("NAME %s\n", lm->room->name);
	// write(1, lm->room->name, 6);
	lm->room->x = ft_atoi(x);
	lm->room->y = ft_atoi(y);
	if ((ft_strlen_int(lm->room->x) + ft_strlen_int(lm->room->y) + 2
		+ ft_strlen(lm->room->name)) != len)
		error_manager(6);
	*index == 1 ? lm->room->is_start = 1 : false;
	*index == 2 ? lm->room->is_end = 1 : false;
	*index = 0;
	return (lm->room);
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

void	print(t_lm *lm)
{
	t_rm *cur = lm->start;

	while (cur)
	{
		printf("[$$$$][%s]\n", cur->name);
		cur = cur->next;
	}
}

void				parsing(t_lm *lm)
{
	char	*line = NULL;
	int		index;
	t_list	*m;
	int		check = 1;

	// room = malloc(sizeof(t_rm));
	// room = lm->start;
	index = 0;
	alloc_ants(line, lm);	
	m = lm->map;
	while ((lm->error = get_next_line(0, &line)) > 0)
	{
		if (line[0] == '#')
			index = read_hash(line);
		else
		{
			lm->room = read_room(line, &index, lm);
			printf("	pervi 		%s\n", lm->room->name);
			if (check)
			{
				lm->start = lm->room;
				printf("start %s\n", lm->start->name);
				check--;
			}
			printf("%p\n", lm->room);
			printf("%p\n", lm->start);
			lm->room = lm->room->next;
			print(lm);
		}
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