/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 03:17:16 by faksouss          #+#    #+#             */
/*   Updated: 2023/04/21 11:31:32 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/built.h"

int	check_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (is_cd(cmd) || is_echo(cmd) || is_env(cmd) || is_exit(cmd)
		|| is_unset(cmd) || is_export(cmd) || is_pwd(cmd) || !ft_strcmp(cmd, "who_are_we"))
		return (1);
	else
		return (0);
}

void	do_builtin(t_exec *cmd, t_minishell *mini)
{
	if (is_echo(cmd->cmd_exec[0]))
		my_echo(cmd);
	else if (is_cd(cmd->cmd_exec[0]))
		my_cd(cmd, mini);
	else if (is_pwd(cmd->cmd_exec[0]))
		my_pwd(mini->env);
	else if (is_env(cmd->cmd_exec[0]))
		my_env(mini->env);
	else if (is_exit(cmd->cmd_exec[0]))
		my_exit(cmd, mini);
	else if (is_unset(cmd->cmd_exec[0]))
		my_unset(cmd, mini);
	else if (is_export(cmd->cmd_exec[0]))
		my_export(cmd, mini);
	else if(!ft_strcmp(cmd->cmd_exec[0], "who_are_we"))
		who_are_we();
}

int	should_not_fork(char **cmd)
{
	if (is_cd(cmd[0]) || is_exit(cmd[0]) || is_unset(cmd[0])
		|| (is_export(cmd[0]) && cmd[1]))
		return (0);
	return (1);
}
