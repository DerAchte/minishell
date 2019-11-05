/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdervil <thdervil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:01:37 by derachte          #+#    #+#             */
/*   Updated: 2019/11/03 13:53:51 by thdervil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	what_do(t_mshell *mshell, int i)
{
	int j;

	j = 0;
	while (mshell->commands[i][j] != '=')
		++j;
	if (mshell->commands[i][j - 1])
		env_pushback(1, 1, mshell->env_list, mshell->commands[i]);
}

int		if_builtin(t_mshell *mshell)
{
	int				i;
	static	char	*blt[] = {"echo", "cd", "setenv", "unsetenv",
								"env", "exit"};

	i = -1;
	while (++i < 6)
	{
		if (!ft_strcmp(mshell->commands[0], blt[i]))
		{
			mshell->builtin = ft_strdup(blt[i]);
			return (0);
		}
	}
	return (1);
}

int		check_existing(t_envlist *new, t_envlist *env_list)
{
	t_envlist	*start;
	int			i;

	start = env_list;
	while (env_list->next)
	{
		i = 0;
		while (env_list->next->line[i] != '=')
			i++;
		if (!ft_strncmp(env_list->next->line, new->line, i))
		{
			replace_1link(new, env_list);
			env_list = start;
			return (1);
		}
		env_list = env_list->next;
	}
	env_list = start;
	return (0);
}
