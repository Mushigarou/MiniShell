/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:58:41 by faksouss          #+#    #+#             */
/*   Updated: 2023/04/29 00:31:25 by faksouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_H
# define BUILT_H

# include"../../libtool/inc/libft.h"
# include"../../parsing/inc/parsing.h"
# include"../../execution/inc/execution.h"

/*check if the command is a builtin command or not*/
int		check_builtin(char *cmd);
/*check if the command line if it have a builtin command*/
int		is_builtin(t_list *cmd);
/*if there is a single command check if should not fork for the command*/
int		should_not_fork(char **cmd);
/*execute a builting command*/
void	do_builtin(t_exec *cmd, t_minishell *mini);
/*check if the flag -n chould work*/
int		check_echo_flg(char *flg);
/*repreduce the echo bihavior*/
void	my_echo(t_exec *cmd);
/*check if the command is echo*/
int		is_echo(char *cmd);
/*repreduce the cd bihavior*/
void	my_cd(t_exec *cmd, t_minishell *mini);
/*update the pwd in the envirenment*/
void	update_env(t_minishell *mini);
/*if cd is called whith out args go to home path*/
void	go_home(t_minishell *mini);
/*check if the command is cd*/
int		is_cd(char *cmd);
/*check if the command is pwd*/
int		is_pwd(char *cmd);
/*repreduce the pwd bihavior*/
void	my_pwd(t_list *env);
/*check if the command is env*/
int		is_env(char *cmd);
/*repreduce the env bihavior*/
void	my_env(t_list *env);
/*check if the command is exit*/
int		is_exit(char *cmd);
/*check if the argiment passed to exit is valid*/
int		valid_arg(char *arg);
/*repreduce the exit bihavior*/
void	my_exit(t_exec *cmd, t_minishell *mini);
/*check if the command is unset*/
int		is_unset(char *cmd);
/*check the unset syntax*/
int		check_unset_syntax(char *str, int *ext_st);
/*check if the str is the target to unset*/
int		is_the_target(char *str, char *env);
/*look for the target if it existe in the envirement and unset
it if it find it*/
void	unset_from_env(char *str, t_minishell *mini);
/*repreduce the unset bihavior*/
void	my_unset(t_exec *cmd, t_minishell *mini);
/*repreduce the export bihavior*/
void	my_export(t_exec *cmd, t_minishell *mini);
/*check if the command is export*/
int		is_export(char *cmd);
/*sort a list*/
void	sort_list(t_list *env);
/*check the export syntax*/
int		check_export_syntax(char *str, int *ext_st);
/*take export list form the envirement list*/
void	take_export(t_list **exp, t_list *en);
/*print the export in order*/
void	print_export(t_minishell *mini);
/*take key and valeur and the type*/
void	take_key_and_val(char *str, char **key, char **val, int *tp);
/*check if the key already exists in the envirement*/
int		already_exists(t_list *env, char *key, int *acs);
/*if the key to be exported already exists and have access change 
its valeur*/
void	change_env_prt(t_minishell *mini, char *key, char *val, int tp);
/*if the key to be exported already exists and don't have access it give it 
back access and change it valeur or remove it valeur if exported 
without valeur*/
void	bring_back_env_prt(t_minishell *mini, char *key, char *val, int tp);
/*if the key don't already exists in the envirement add it to the 
envirenment list*/
void	add_new_env_prt(t_minishell *mini, char *key, char *val, int tp);
/*print the authers of the project*/
void    who_are_we(void);

#endif
