/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_redirction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:36:17 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/22 17:11:08 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"

int	take_rediraction(t_minishell *mini, t_list **cmd, int i)
{
	if (mini->line[i] == '<')
		i = take_input(mini, cmd, i);
	else
		i = take_output(mini, cmd, i);
	return (i);
}
