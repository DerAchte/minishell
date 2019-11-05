/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdervil <thdervil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:26:39 by derachte          #+#    #+#             */
/*   Updated: 2019/11/05 07:46:48 by thdervil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**get_path_env(char **envp)
{
	char	**ret;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
			ret = ft_strsplit(envp[i] + 5, ':');
		i++;
	}
	return (ret);
}

t_mshell	*init_mshell(char **envp)
{
	t_mshell	*ret;

	if (!(ret = (t_mshell *)malloc(sizeof(t_mshell))))
		return (NULL);
	ret->bin_path = NULL;
	ret->commands = NULL;
	ret->whole_env = envp;
	ret->path_env = get_path_env(envp);
	ret->is_binary = 0;
	ret->cd_dir = NULL;
	ret->env_list = env_init(envp);
	ret->unvalid = 0;
	ret->exit = 0;
	ret->prev_dir = NULL;
	ret->prev_dir = getcwd(NULL, 0);
	ret->env_in = 0;
	ret->after_exec = 0;
	ret->builtin = NULL;
	return (ret);
}

t_envlist	*env_init(char **envp)
{
	t_envlist	*env_list;
	int			i;

	i = 0;
	env_list = init_envlist(envp[i++]);
	while (envp[i])
	{
		env_pushback(0, 0, env_list, envp[i]);
		i++;
	}
	return (env_list);
}

t_envlist	*init_envlist(char *start)
{
	t_envlist	*ret;

	if (!(ret = (t_envlist *)malloc(sizeof(t_envlist))))
		return (NULL);
	ret->line = ft_strdup(start);
	ret->next = NULL;
	ret->manual = 0;
	ret->ephemere = 0;
	return (ret);
}
