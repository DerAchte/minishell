/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deletes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdervil <thdervil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:48:27 by derachte          #+#    #+#             */
/*   Updated: 2019/11/05 08:16:55 by thdervil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_1link(t_envlist *envlink)
{
	t_envlist *next_lnk;

	next_lnk = envlink->next;
	next_lnk->ephemere = 0;
	free(next_lnk->line);
	next_lnk->line = NULL;
	next_lnk->manual = 0;
	envlink->next = next_lnk->next;
	free(next_lnk);
	next_lnk = NULL;
}

void	del_in_loop(t_mshell *mshell)
{
	if (mshell)
	{
		delete_ephemere(mshell->env_list);
		mshell->is_binary = 0;
		mshell->unvalid = 0;
		mshell->env_in = 0;
		mshell->after_exec = 0;
		mshell->commands = NULL;
	}
	return ;
}

void	delete_ephemere(t_envlist *envlist)
{
	t_envlist *start;
	t_envlist *tmp;
	t_envlist *last;

	start = envlist;
	while (envlist)
	{
		if (envlist->ephemere)
		{
			last = envlist->prev;
			while (envlist)
			{
				tmp = envlist;
				envlist = envlist->next;
				free(tmp->line);
				free(tmp);
				tmp = NULL;
			}
			envlist = start;
			last->next = NULL;
			return ;
		}
		envlist = envlist->next;
	}
}

void	del_all(t_mshell *mshell)
{
	if (mshell)
	{
		if (mshell->env_list)
			free(mshell->env_list);
		ft_strdel2(mshell->path_env);
		if (mshell->whole_env)
			free(mshell->whole_env);
		ft_bzero(mshell, sizeof(*mshell));
	}
}
