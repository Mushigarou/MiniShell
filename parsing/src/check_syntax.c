/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 01:05:52 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/22 14:58:03 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"

int	empty_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (!ft_isspace(line[i]))
			break ;
	if (line[i] == '\0')
		return (1);
	else
		return (0);
}

int	check_syntax(char *line)
{
	if (empty_line(line))
		return (0);
	else if (!valid_ct(line))
		return (printf("quotes\n"), 256);
	else if (!valid_rediraction(line))
		return (printf("redirection\n"), 256);
	else if (!valid_pipe(line))
		return (printf("pipe\n"), 256);
	else
		return (1);
}