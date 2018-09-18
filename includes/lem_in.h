/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmuravch <hmuravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 05:08:21 by hmuravch          #+#    #+#             */
/*   Updated: 2018/09/18 03:35:40 by hmuravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LEM_IN_H
# define LEM_IN_H

# include "libft.h"

typedef	struct	s_room t_rm;

typedef struct		s_links
{
	t_rm			*room;
	struct s_links	*next;
	
}					t_link;

typedef	struct	s_room
{
	unsigned int	is_empty : 1;
	unsigned int	is_start : 1;
	unsigned int	is_end : 1;
	int				x;
	int				y;
	char			*name;
	t_link			*links;
	t_rm			*next;

}						t_rm;

typedef struct	s_ant
{
	int			number;
	t_rm		*his_room;

}				t_ant;

typedef	struct	s_lem_in
{
	int			error;
	int			ant_amount;
	t_list		*map;
	t_ant		*head;		//массив муравьёв
	t_rm		*start;		//лист комнат
	
}				t_lm;

void			parsing(t_lm *lm);
void			error_manager(int error);

#endif