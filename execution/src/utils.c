/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:48:38 by mfouadi           #+#    #+#             */
/*   Updated: 2023/05/03 22:39:59 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// Loops through the **path to find the executable of the given command
char	*find_cmd(char **path, char *cmd)
{
	char	*tmp;
	char	*tmp1;

	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		return (NULL);
	}
	while (path && *path)
	{
		tmp = ft_strjoin(ft_strdup(*path), ft_strdup("/"));
		tmp1 = ft_strjoin(tmp, ft_strdup(cmd));
		if (access(tmp1, F_OK | X_OK) == 0)
			return (tmp1);
		free(tmp1);
		path++;
	}
	return (NULL);
}

// ** Looks for PATH variable, then splits it with ':' and store it in a char **
char	*get_cmd_path(t_minishell *mini, char *cmd)
{
	char	**path;
	t_list	*tmp;

	path = NULL;
	tmp = mini->env;
	while (tmp)
	{
		if (tmp->acs != 0)
		{	
			if (ft_strncmp(tmp->pt, "PATH=", 5) == 0)
			{
				path = ft_split(tmp->pt + 5, ':');
				break ;
			}
		}
		tmp = tmp->next;
	}
	return (find_cmd(path, cmd));
}

/*	
	The output of each command in the pipeline is connected via a pipe to 
	the input of the next command.
*/
void	open_pipes(t_minishell *mini, t_exec *pipeline)
{
	int	fd[2];
	int	i;

	i = 0;
	pipeline->in = -1;
	while (pipeline)
	{
		if (pipe(fd))
			exit(error("pipe", 1));
		mini->open_fds[mini->fd_cnt++] = fd[0];
		mini->open_fds[mini->fd_cnt++] = fd[1];
		if (pipeline->next)
		{
			pipeline->next->in = fd[0];
			pipeline->out = fd[1];
		}
		i++;
		pipeline = pipeline->next;
	}
	return ;
}

// **	close all openned file descriptors, unless STDIN, STDOUT, and STDERR
void	close_file_descriptors(t_minishell *mini)
{
	int	i;

	i = 0;
	while (i < mini->fd_cnt)
	{
		close(mini->open_fds[i]);
		i++;
	}
	return ;
}

void	execute_all_commands(t_minishell *mini, t_exec *tmp, int *pid)
{
	while (tmp)
	{
		*pid = -1;
		if (!tmp->rdrct_err)
			*pid = fork();
		else
		{
			tmp = tmp->next;
			continue ;
		}
		if (*pid == 0)
			_execute_in_child(mini, tmp);
		else if (*pid == -1)
			exit(error("fork", 1));
		tmp = tmp->next;
	}
	// if (*pid != -1)
	// {		
	// 	waitpid(*pid, mini->ext_st, 0);
	// 	if (WIFEXITED(*mini->ext_st))
	// 		*mini->ext_st = WEXITSTATUS(*mini->ext_st);
	// }
}
