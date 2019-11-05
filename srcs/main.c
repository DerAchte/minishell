/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdervil <thdervil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:48:55 by thdervil          #+#    #+#             */
/*   Updated: 2019/11/05 11:03:31 by thdervil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av, char **envp)
{
	t_mshell	*mshell;
	char		**commands;
	char		**split;

	(void)ac;
	(void)av;
	split = NULL;
	commands = (char**)malloc(sizeof(char*));
	mshell = init_mshell(envp);
	while (!mshell->exit)
	{
		write(1, "> ", 2);
		if (get_next_line(STDIN_FILENO, commands))
		{
			if (!commands[0][0])
			{
				continue ;
				ft_strdel(commands);
			}
			split = ft_strsplit(*commands, ' ');
			mshell->commands = trans_cmds(split, mshell);
			if (mshell->exit)
				break ;
			execute(mshell);
			free(commands);
			ft_strdel2(split);
			del_in_loop(mshell);
		}
		else
			break ;
	}
	del_all(mshell, commands);
	free(mshell);
	return (0);
}
