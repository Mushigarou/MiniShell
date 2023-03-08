/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 23:32:21 by faksouss          #+#    #+#             */
/*   Updated: 2023/03/08 05:42:42 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/execution.h"

void	do_single_cmd(t_list *cmd, t_minishell *mini)
{
	char	**cm;
	char	*cm_pth;

	cm = NULL;
	cm_pth = NULL;
	if (check_in_rdrct(cmd))
		take_input(cmd, mini);
	if (check_out_rdrct(cmd))
		take_output(cmd);
	if (check_cmd(cmd))
	{
		if (is_builtin(cmd))
		{
			do_builtin(cmd, mini);
			exit(mini->ext_st);
		}
		cm = take_char_cmd(cmd);
		cm_pth = take_path(cm[0], mini);
		if (!cm_pth)
			cmd_not_found(cm);
		execve(cm_pth, cm, take_char_env(mini->env));
		exit(error("execve"));
	}
	exit(EXIT_SUCCESS);
}

void	execute_one(t_list *cmd, t_minishell *mini)
{
	int		pid;

	if (is_builtin(cmd) && should_not_fork(cmd))
		do_builtin(cmd, mini);
	else
	{
		pid = fork();
		if (!pid)
			do_single_cmd(cmd, mini);
		else
			waitpid(pid, &mini->ext_st, 0);
	}
}

void	execute_mltpl_cmd(t_list **cmd, t_minishell *mini)
{
	int	i;
	int	pid;

	i = -1;
	while (cmd[++i])
	{
		if (pipe(mini->fd) < 0)
			exit(error("pipe"));
		pid = fork();
		if (!pid)
		{
			close(mini->fd[0]);
			if (cmd[i + 1])
				dup2(mini->fd[1], STDOUT_FILENO);
			do_single_cmd(cmd[i], mini);
		}
		else
		{
			close(mini->fd[1]);
			if (cmd[i + 1])
				dup2(mini->fd[0], STDIN_FILENO);
			waitpid(pid, &mini->ext_st, 0);
		}
	}
	exit(mini->ext_st);
}

void	execute_all(t_list **cmd, int ct, t_minishell *mini)
{
	int	pid;
	int	i;

	if (ct == 1)
		execute_one(cmd[0], mini);
	else
	{
		pid = fork();
		if (!pid)
			execute_mltpl_cmd(cmd, mini);
		else
			waitpid(pid, &mini->ext_st, 0);
	}
	i = -1;
	while (cmd[++i])
		ft_lstclear(&cmd[i]);
	free(cmd);
}
