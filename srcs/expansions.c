/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdervil <thdervil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:55:00 by derachte          #+#    #+#             */
/*   Updated: 2019/11/05 09:24:48 by thdervil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tilde_trans(char **commands, int i, t_envlist *env_list)
{
	t_envlist	*start;
	char		*var_name;

	start = env_list;
	{
		while (env_list)
		{
			var_name = var_namecut(env_list);
			if (!ft_strcmp("HOME", var_name))
			{
				commands[i] = replace_cmd(commands[i], env_list->line);
				break ;
			}
			env_list = env_list->next;
			free(var_name);
			var_name = NULL;
		}
		env_list = start;
	}
}

void	dollar_trans(char **commands, int i, t_envlist *env_list)
{
	t_envlist	*start;
	char		*var_name;

	start = env_list;
	{
		while (env_list)
		{
			var_name = var_namecut(env_list);
			if (!ft_strcmp(&commands[i][1], var_name))
			{
				commands[i] = replace_cmd(commands[i], env_list->line);
				free(var_name);
				env_list = start;
				return ;
			}
			free(var_name);
			var_name = NULL;
			env_list = env_list->next;
		}
		env_list = start;
	}
}


char	**trans_cmds(char **commands, t_mshell *mshell)
{
	int i;
	char	*tmp;
	char	**ret;

	i = 0;
	if (!ft_strcmp(commands[0], "exit") || !commands)
	{
		mshell->exit = 1;
		ft_strdel2(commands);
		return (commands);
	}
	while (commands[i])
	{
		if (commands[i][0] == '$')
			dollar_trans(commands, i, mshell->env_list);
		if (commands[i][0] == '~')
			tilde_trans(commands, i, mshell->env_list);
		i++;
	}
	tmp = ft_splittoone(commands);
	ret = ft_strsplit(tmp, ' ');
	free(tmp);
	return (ret);
}
