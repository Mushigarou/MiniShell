/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:50:21 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/14 18:00:22 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/built.h"

int	main(int ac, char **av, char **en)
{
	if (ac == 1 && !ft_strncmp((av[0] + 2), "env_f", 6))
	{
		while (*en)
			printf("%s\n", *en++);
	}
}