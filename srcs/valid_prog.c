/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_prog.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdervil <thdervil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:44:39 by derachte          #+#    #+#             */
/*   Updated: 2019/11/05 08:00:26 by thdervil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		valid_prog(t_mshell *mshell)
{
	if (!mshell->is_binary)
		if (!if_builtin(mshell))
			return (1);
	create_poss(mshell);
	if (mshell->bin_path)
	{
		mshell->is_binary = 1;
		return (1);
	}
	mshell->unvalid = 1;
	if (!mshell->is_binary)
	{
		write(2, "command not found: ", 20);
		write(2, mshell->commands[0], ft_strlen(mshell->commands[0]));
		write(2, "\n", 1);
		ft_strdel2(mshell->commands);
		mshell->commands = NULL;
	}
	return (0);
}
