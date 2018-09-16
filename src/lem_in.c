/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmuravch <hmuravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 05:06:06 by hmuravch          #+#    #+#             */
/*   Updated: 2018/09/16 06:10:16 by hmuravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error_manager(int error)
{
	printf("ERROR %i\n", error);
	// error ? ft_printf("ERROR: fail reading\n") : false;
	// error == 1 ? ft_printf("ERROR: invalid line\n") : false;
	//3
	//4
	exit(1);
}

int	main(void)
{
	t_lm	lm;

	ft_bzero(&lm, sizeof(lm));
	parsing(&lm);
	// algorithm;
}