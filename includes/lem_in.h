/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmuravch <hmuravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 05:08:21 by hmuravch          #+#    #+#             */
/*   Updated: 2018/10/28 01:40:13 by hmuravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

typedef	struct		s_room t_rm;
typedef struct		s_links	t_q;
typedef struct		s_links	t_w;

typedef struct		s_links
{
	t_rm			*room;
	struct s_links	*next;

}					t_link;

typedef	struct		s_room
{
	unsigned int	is_empty : 1;
	unsigned int	is_start : 1;
	unsigned int	is_end : 1;
	unsigned int	used : 1;
	int				ant;
	int				num;
	int				x;
	int				y;
	int				len;
	char			*name;
	t_link			*link;
	t_rm			*next;

}						t_rm;

typedef	struct		s_lem_in
{
	char			**input;
	int				i;
	int				error;
	int				ant_amount;
	int				rib_amount;
	t_rm			*start;

}					t_lm;

int					read_hash(char *line);
int					check_line(char *line);
int					check_end_start(t_lm *lm);
void				error_manager(int error);
void				execute_command(int	cmd);
void				fill_len(t_q *que, t_lm *lm);
void				print_ants(t_lm *lm, t_w *way);
void				read_ants(char *line, t_lm *lm);
void				read_link(char *line, t_lm *lm);
void				read_room(char *line, int *index, t_lm *lm);
t_w					*find_way(t_lm *lm);
t_rm				*find_end(t_rm *start);
t_rm				*find_start(t_rm *start);

#endif
