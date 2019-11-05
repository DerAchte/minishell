/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdervil <thdervil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:18:00 by derachte          #+#    #+#             */
/*   Updated: 2019/11/05 09:09:48 by thdervil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	m_echo(t_mshell *mshell)
{
	int i;
	int j;

	i = 1;
	j = 0;
	if (mshell->commands[i])
	{
		while (mshell->commands[i])
		{
			if (mshell->commands[i][0] != '$')
			{
				while (mshell->commands[i][j])
				{
					ft_putchar(mshell->commands[i][j]);
					j++;
				}
				if (mshell->commands[i + 1])
					ft_putchar(' ');
				j = 0;
			}
			i++;
		}
	}
	ft_putchar('\n');
}

void	m_cd(t_mshell *mshell)
{
	int		i;

	i = 0;
	if (!mshell->commands[1])
		cd_no_args(mshell, i);
	else if (mshell->commands[1][0] == '-' &&
			!mshell->commands[2] && !mshell->commands[1][1])
		cd_minus(mshell);
	else
		mshell->cd_dir = ft_splittoone(&(mshell->commands[1]));
	free(mshell->prev_dir);
	mshell->prev_dir = NULL;
	mshell->prev_dir = getcwd(NULL, 0);
	if (chdir(mshell->cd_dir) < 0)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl(mshell->cd_dir);
	}
	free(mshell->cd_dir);
	mshell->cd_dir = NULL;
}

void	m_setenv(t_mshell *mshell)
{
	char *add;
	char *tmp1;
	char *tmp2;

	if (!(mshell->commands[1] && mshell->commands[2]) || mshell->commands[3])
	{
		ft_putendl("usage: setenv [VAR_NAME] [VALUE]");
		return ;
	}
	tmp1 = ft_strdup(mshell->commands[1]);
	tmp2 = ft_strdup(mshell->commands[2]);
	add = create_var(tmp1, tmp2);
	var_pushback(1, 0, mshell->env_list, add);
	free(tmp1);
	free(tmp2);
	free(add);
	return ;
}

void	m_unsetenv(t_mshell *mshell)
{
	t_envlist	*tmp;
	char		*var;

	tmp = mshell->env_list;
	var = NULL;
	if (!mshell->commands[1] || mshell->commands[2])
	{
		ft_putendl("usage: unsetenv [VAR]");
		return ;
	}
	while (mshell->env_list->next)
	{
		var = var_namecut(mshell->env_list->next);
		if (mshell->env_list->next->manual)
			if (!ft_strcmp(var, mshell->commands[1]))
				del_1link(mshell->env_list);
		free(var);
		mshell->env_list = mshell->env_list->next;
	}
	mshell->env_list = tmp;
}

void	m_env(t_mshell *mshell)
{
	t_envlist	*tmp;
	char		**new;

	mshell->env_in = 1;
	tmp = mshell->env_list;
	new = new_commands(mshell);
	ft_strdel2(mshell->commands);
	mshell->commands = trans_cmds(new, mshell);
	ft_strdel2(new);
	if (ft_strcmp(mshell->commands[0], "env"))
	{
		execute(mshell);
		return ;
	}
	while (mshell->env_list)
	{
		ft_putendl(mshell->env_list->line);
		mshell->env_list = mshell->env_list->next;
	}
	mshell->env_list = tmp;
	return ;
}
