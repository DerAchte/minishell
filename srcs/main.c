/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdervil <thdervil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:48:55 by thdervil          #+#    #+#             */
/*   Updated: 2019/11/05 12:53:19 by thdervil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_var(t_mshell **mshl, char ***s, char ***cmd, char **envp)
{
	*s = NULL;
	*cmd = (char**)malloc(sizeof(char*));
	*mshl = init_mshell(envp);
}

int		main(int ac, char **av, char **envp)
{
	t_mshell	*mshell;
	char		**commands;
	char		**split;

	(void)ac;
	(void)av;
	init_var(&mshell, &split, &commands, envp);
	while (!mshell->exit)
	{
		write(1, "> ", 2);
		if (get_next_line(STDIN_FILENO, commands))
		{
			if (!commands[0][0])
				continue ;
			split = ft_strsplit(*commands, ' ');
			mshell->commands = trans_cmds(split, mshell);
			execute(mshell);
			del_in_loop(mshell, commands, split);
		}
		else
			break ;
	}
	del_all(mshell, commands);
	return (0);
}
