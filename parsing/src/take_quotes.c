/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:27:24 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/22 18:27:23 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/parsing.h"

int	in_quotes(char *line, int i)
{
	int	j;
	int	in;

	j = -1;
	in = 0;
	while (line[++j])
	{
		if (line[j] == '\'' || line[j] == '"')
		{
			if (!in)
				in = 1;
			else
				in = 0;
		}
		if (j == i)
			break ;
	}
	return (in);
}

int	valid_ct(char *cl)
{
	int	i;
	int	j;
	int	ct;

	i = -1;
	while (cl[++i])
	{
		j = 1;
		if (cl[i] == '\'' || cl[i] == '"')
		{
			ct = cl[i];
			while (cl[i + j])
			{
				if (cl[i + j] == ct)
					break ;
				j++;
			}
			if (cl[i + j] == '\0')
				return (0);
			i += j + 1;
		}
	}
	return (1);
}

char	*take_double_qts(t_minishell *mini, int i)
{
	int		j;
	int		x;
	char	*r;

	j = i + 1;
	r = NULL;
	while (1)
	{
		x = j;
		while (mini->line[j])
		{
			if (mini->line[j] == '$' || mini->line[j] == '"')
				break ;
			j++;
		}
		r = ft_strjoin(r, ft_substr(mini->line, x, j - x));
		if (mini->line[j] == '$')
			r = ft_strjoin(r, take_dollar(mini, &j));
		if (mini->line[j] == '"')
			break ;
	}
	return (r);
}

int	take_quotes(t_minishell *mini, t_list **cmd, int i)
{
	int		j;
	char	*pt;

	j = i;
	while (mini->line[++j])
		if (mini->line[i] == mini->line[j])
			break ;
	if (j == i + 1)
	{
		ft_lstadd_back(cmd, ft_lstnew("", QTS));
		return (j);
	}
	else if (mini->line[i] == '\'')
		pt = ft_substr(mini->line, i, j - i + 1);
	else if (mini->line[i] == '"')
		pt = take_double_qts(mini, i);
	ft_lstadd_back(cmd, ft_lstnew(pt, QTS));
	free(pt);
	return (j + 1);
}
