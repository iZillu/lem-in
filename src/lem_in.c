/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmuravch <hmuravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 05:06:06 by hmuravch          #+#    #+#             */
/*   Updated: 2018/09/15 05:15:33 by hmuravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error_manager(int error)
{
	ft_putstr_fd("ERROR", 2);
	// error == -1 ? ft_putstr_fd("ERROR: fail reading", 2) : false;
	// error == 1 ? ft_putstr_fd("ERROR: invalid line", 2) : false;
	//3
	//4
	// exit(1);
}

int	main(void)
{
	t_lm	lm;

	ft_bzero(&lm, sizeof(lm));
	parsing(&lm);
	// algorithm;
}