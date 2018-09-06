/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmuravch <hmuravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 05:06:06 by hmuravch          #+#    #+#             */
/*   Updated: 2018/09/06 05:43:35 by hmuravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error_manager(int	error)
{
	if (error == -1)
		ft_putstr_fd("ERROR: invalid file", 2);
	exit(1);
}

int	main(void)
{
	t_lm	lm;
	char	*line;

	ft_bzero(&lm, sizeof(lm));
	while(lm.error = get_next_line(0, &line))
	{
		if (lm.error == -1)
			error_manager(lm.error);
		else
			parsing(&lm);
		algorithm;
		free(line);
	}
}