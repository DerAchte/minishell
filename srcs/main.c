/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdervil <thdervil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:48:55 by thdervil          #+#    #+#             */
/*   Updated: 2019/11/05 09:25:03 by thdervil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	POINT_ALL_ADD(t_mshell *mshell)
{
	("mshell->bin_path:  %p\n", mshell->bin_path);
	("mshell->builtin:   %p\n", mshell->builtin);
	("mshell->cd_dir:    %p\n", mshell->cd_dir);
	("mshell->commands:  %p\n", mshell->commands);
	("mshell->env_list:  %p\n", mshell->env_list);
	("mshell->exit:      %d\n", mshell->exit);
	("mshell->is_binary: %d\n", mshell->is_binary);
	("mshell->path_env:  %p\n", mshell->path_env);
	("mshell->prev_dir:  %p\n", mshell->prev_dir);
	("mshell->unvalid:   %d\n", mshell->unvalid);
	("mshell->whole_env: %p\n", mshell->whole_env);
}*/

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
			ft_strdel(commands);
			ft_strdel2(split);
			del_in_loop(mshell);
		}
		else
			break ;
	}
	del_all(mshell);
	return (0);
}
