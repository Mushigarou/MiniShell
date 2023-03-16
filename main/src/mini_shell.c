/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:17:06 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/16 11:03:18 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/mini_shell.h"

void	take_and_do_cmd(t_minishell *mini)
{
	take_cmd(mini);
	split_and_execute_cmd(mini);
	ft_lstclear(&mini->cmd);
}

void	mini_shell(t_minishell *mini)
{
	mini->prompt = inisialise_prompt();
	mini->line = readline(mini->prompt);
	if (!mini->line)
		out(mini);
	free(mini->prompt);
	if (!empty_line(mini->line))
		add_history(mini->line);
	if (check_syntax(mini->line) == 258)
		mini->ext_st = error(NULL, 258) * 256;
	else if (!empty_line(mini->line))
		take_and_do_cmd(mini);
	free(mini->line);
}

int	main(int ac, char **av, char **en)
{
	t_minishell	mini;

	(void)ac;
	(void)av;
	mini.env = take_env(en);
	while (1)
		mini_shell(&mini);
}
