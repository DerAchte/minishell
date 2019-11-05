/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdervil <thdervil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:00:15 by derachte          #+#    #+#             */
/*   Updated: 2019/11/05 12:17:00 by thdervil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_cmds3(t_mshell *mshell, char **ret, int start, int j)
{
	while (mshell->commands[start])
		ret[j++] = ft_strdup(mshell->commands[start++]);
	ret[j] = NULL;
	ft_strdel2(mshell->commands);
	mshell->commands = NULL;
}

char	**new_cmds2(t_mshell *mshell, int i)
{
	int		j;
	int		start;
	char	**ret;

	j = 0;
	ret = NULL;
	if (!mshell->commands[i] || !ft_strcmp(mshell->commands[i], "env"))
	{
		ret = (char**)malloc(sizeof(char*) * 2);
		ret[0] = ft_strdup("env");
		ret[1] = NULL;
		return (ret);
	}
	if (mshell->commands[i])
	{
		start = i;
		while (mshell->commands[i++])
			j++;
		if (!(ret = (char **)malloc(sizeof(char *) * (j + 1))))
			return (NULL);
		j = 0;
		new_cmds3(mshell, ret, start, j);
	}
	return (ret);
}

char	**new_commands(t_mshell *mshell)
{
	char	**ret;
	int		i;

	i = 0;
	ret = NULL;
	while (mshell->commands[i++])
	{
		if (ft_cisin(mshell->commands[i], '='))
			what_do(mshell, i);
		if (ft_strcmp(mshell->commands[i], "env")
			&& !ft_cisin(mshell->commands[i], '='))
			break ;
	}
	ret = new_cmds2(mshell, i);
	if (ret)
		mshell->is_binary = 1;
	return (ret);
}

char	*replace_cmd(char *cmd, char *replace)
{
	char	*new;
	char	*tmp;
	int		i;

	i = 0;
	tmp = replace;
	if (ft_cisin(replace, '='))
		while (replace[i] != '=')
			i++;
	new = ft_strdup(&replace[i + 1]);
	free(cmd);
	cmd = NULL;
	replace = tmp;
	return (new);
}
