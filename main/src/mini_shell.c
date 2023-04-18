/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:17:06 by faksouss          #+#    #+#             */
/*   Updated: 2023/04/17 23:41:02 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	handl_segint_child(int segnum)
{
	if (segnum == SIGINT)
	{
		write(1, "\n", 1);
		exit(130);
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
}

static void wait_childs(t_minishell *mini)
{
	while (waitpid(-1, mini->ext_st, 0) != -1)
		if (WIFEXITED(*mini->ext_st))
			*mini->ext_st = WEXITSTATUS(*mini->ext_st);
}
void	take_and_do_cmd(t_minishell *mini)
{
	take_cmd(mini);
	if (fork() == 0)
	{
		signal(SIGINT, handl_segint_child);
		execute_pipeline(mini);
	}
	wait_childs(mini);
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
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handl_segint);
	while (1)
		mini_shell(&mini);
}
