/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdervil <thdervil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:44:23 by thdervil          #+#    #+#             */
/*   Updated: 2019/11/05 09:04:27 by thdervil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <dirent.h>
# include <limits.h>
#include <sys/wait.h>

typedef struct				s_envlist
{
	char					*line;
	struct s_envlist		*next;
	struct s_envlist		*prev;
	int						manual;
	int						ephemere;
}							t_envlist;

typedef struct				s_commands
{
	char					*command;
	struct s_commands		*next;
}							t_commands;

typedef struct				s_mshell
{
	int						after_exec;
	int						env_in;
	int						exit;
	char					*builtin;
	char					*prev_dir;
	char					*cd_dir;
	char					*bin_path;
	char					**commands;
	char					**path_env;
	char					**whole_env;
	int						is_binary;
	int						unvalid;
	t_envlist				*env_list;
}							t_mshell;

typedef	void				(*t_builtin_ptr)(t_mshell *);

typedef struct				s_builtin
{
	const char				*name;
	t_builtin_ptr			ptr;
}							t_builtin;

void						m_echo(t_mshell *mshell);
void						m_cd(t_mshell *mshell);
void						m_setenv(t_mshell *mshell);
void						m_unsetenv(t_mshell *mshell);
void						m_env(t_mshell *mshell);
char						**read_commands(void);
char						**get_path_env(char **envp);
char						*create_path(char *s1, char *s2);
pid_t						create_process(void);
void						create_poss(t_mshell *mshell);
char						**trans_cmds(char **commands, t_mshell *mshell);
char						*create_var(char *s1, char *s2);
char						*var_namecut(t_envlist *env_list);
char						**new_commands(t_mshell *mshell);
char						*replace_cmd(char *cmd, char *replace);
void						replace_1link(t_envlist *new, t_envlist *ante_old);
int							check_existing(t_envlist *new, t_envlist *env_list);
void						what_do(t_mshell *mshell, int i);
char						**lst_to_tab(t_envlist *envlist);
int							if_builtin(t_mshell *mshell);
int							valid_prog(t_mshell *mshell);
int							get_size(char **tab);
char						*ft_splittoone(char **tab);
void						exec_builtin(t_mshell *mshell);
void						execute(t_mshell *mshell);
void						del_in_loop(t_mshell *mshell);
t_envlist					*init_envlist(char *start);
t_envlist					*add_env(char *add, int manu, int eph);
void						delete_ephemere(t_envlist *envlist);
void						env_pushback(int manual, int eph,
							t_envlist *env_list, char *envpath);
t_envlist					*env_list(t_mshell *mshell);
t_mshell					*init_mshell(char **envp);
t_envlist					*env_init(char **envp);
void						del_1link(t_envlist *envlist);
void						var_pushback(int manu, int eph,
							t_envlist *env_list, char *envpath);
void						cd_no_args(t_mshell *mshell, int i);
void						cd_minus(t_mshell *mshell);
void						del_all(t_mshell *mshell);

static	const	t_builtin	g_builtins[] =
{
	{"echo", &m_echo},
	{"cd", &m_cd},
	{"setenv", &m_setenv},
	{"unsetenv", &m_unsetenv},
	{"env", &m_env},
};

#endif
