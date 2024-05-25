/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:17:06 by faksouss          #+#    #+#             */
/*   Updated: 2023/05/03 18:48:34 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	handl_segint_child(int segnum)
{
	if (segnum == SIGINT)
		exit(130);
	else if (segnum == SIGQUIT)
	{
		ft_printf("Quit\n", 2);
		exit(131);
	}
}

void	handl_segint(int segnum)
{
	if (segnum == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		if (wait(NULL) == -1)
			rl_redisplay();
		g_ext_st = 130;
	}
	else if (segnum == SIGQUIT)
		rl_redisplay();
}

void	take_and_do_cmd(t_minishell *mini)
{
	take_cmd(mini);
	if (mini->exc->cmd_exec && (check_builtin(mini->exc->cmd_exec[0])
			&& !should_not_fork(mini->exc->cmd_exec)) && !mini->exc->next)
	{
		open_redirections(mini, mini->exc);
		if (!mini->exc->rdrct_err)
			do_builtin(mini->exc, mini);
	}
	else
	{
		if (fork() == 0)
		{
			signal(SIGINT, handl_segint_child);
			signal(SIGQUIT, handl_segint_child);
			execute_pipeline(mini);
		}
		waitpid(-1, mini->ext_st, 0);
		if (WIFEXITED(*mini->ext_st))
			*mini->ext_st = WEXITSTATUS(*mini->ext_st);
	}
	free_exc(&mini->exc);
}

void	mini_shell(t_minishell *mini)
{
	mini->prompt = inisialise_prompt_2();
	mini->line = readline(mini->prompt);
	if (!mini->line)
		out(mini);
	free(mini->prompt);
	if (!empty_line(mini->line))
		add_history(mini->line);
	if (check_syntax(mini->line) == 258)
			*mini->ext_st = error(NULL, 258);
	else if (!empty_line(mini->line))
		take_and_do_cmd(mini);
	free(mini->line);
}

int	main(int ac, char **av, char **en)
{
	t_minishell	mini;

	(void)ac;
	(void)av;
	if (!en[0])
	{
		ft_printf("Minishell : there is no envirenment !*#^&# 😡🤬\n", 2);
		exit(1);
	}
	mini.env = take_env(en);
	mini.ext_st = &g_ext_st;
	signal(SIGINT, handl_segint);
	signal(SIGQUIT, handl_segint);
	while (1)
		mini_shell(&mini);
}
