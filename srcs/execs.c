/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdervil <thdervil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:22:20 by derachte          #+#    #+#             */
/*   Updated: 2019/11/05 12:53:12 by thdervil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	create_process(void)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		write(2, "error: couldn't fork process\n", 30);
		exit(0);
	}
	return (pid);
}

void	exec_builtin(t_mshell *mshell)
{
	unsigned long	i;

	i = 0;
	while (i < sizeof(g_builtins) / sizeof(*g_builtins))
	{
		if (!ft_strcmp(mshell->builtin, g_builtins[i].name))
			g_builtins[i].ptr(mshell);
		++i;
	}
	free(mshell->builtin);
	mshell->builtin = NULL;
	ft_strdel2(mshell->commands);
	return ;
}

void	execute(t_mshell *mshell)
{
	pid_t pid;

	if (!mshell->exit && valid_prog(mshell))
	{
		if (mshell->is_binary)
		{
			pid = create_process();
			if (pid == 0)
				execve(mshell->bin_path, mshell->commands, mshell->whole_env);
			else
				wait(NULL);
			ft_strdel(&mshell->bin_path);
			if (!mshell->env_in)
				ft_strdel2(mshell->commands);
			mshell->after_exec = 1;
		}
		else
			exec_builtin(mshell);
	}
	return ;
}
