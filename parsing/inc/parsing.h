/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:55:39 by faksouss          #+#    #+#             */
/*   Updated: 2023/02/27 14:53:21 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include"../../libtool/inc/libft.h"

# define HEREDOC 1
# define LMTR 2
# define APND 4
# define TRNC 5
# define INPT 6
# define FLG 7
# define VRB 8
# define PP 9
# define IND 10
# define ARG 12
# define QTS 13
# define EN 14
# define SP 15
# define AP_F 16
# define TR_F 17
# define IN_F 18
# define CMD 19

/*check synstax*/
int		check_syntax(char *line);
int		empty_line(char *line);
int		valid_pipe(char *line);
int		valid_rediraction(char *line);
int		check_output(char *line, int i);
int		check_input(char *line, int i);
int		check_heredoc(char *line, int i);
int		in_quotes(char *line, int i);
int		valid_ct(char *cl);
/*Store the environment*/
t_list	*take_env(char **en);
/*take Dollar*/
int		take_var(t_minishell *mini, int i);
char	*take_dollar(t_minishell *mini, char *line, int *i);
int		check_expand(char *str);
char	*expan_variable(char *var, t_minishell *mini);
/*skiping white spaces*/
int		skip_white_spaces(t_minishell *mini, int i);
/*check if the string should be splited or not*/
int		should_be_splited(char *str);
/*take  the pipe or redirections and put them in a node*/
void	take_pp_or_rdrct(char *str, int *i, t_list **new);
/*if the string contain the special character it splite it and put in nodes*/
void	add_to_new_list(t_list **new, char *str);
/*split the strings by '|', '<', '>', '>>' and '<<'*/
void	split_by_pp_and_rdrct(t_minishell *mini);
/*check if the '$' signe should be expanded or not*/
int		check_for_expander(t_list *prt);
/*take the variable and replace it by it's value*/
char	*expand_var(t_minishell *mini, char *old_str);
/*check if there is a variable should be expanded and epand it*/
void	expander(t_minishell *mini);
/*split the command by spaces that ain't in quotes*/
void	split_cmd_line_by_space(t_minishell *mini);
/*locate <, <<, >, >> and |*/
void	identify_special_charcters(t_minishell *mini);
/*locate the redirections herdoc, input, output ...*/
void	identify_rdrct(t_minishell *mini);
/*locate the command*/
void	identify_cmd(t_minishell *mini);
/*locate command's flag*/
void	identify_flag(t_minishell *mini);
/*locate command's arguments*/
void	identify_arg(t_minishell *mini);

#endif
