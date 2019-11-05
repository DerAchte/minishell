/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_opts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdervil <thdervil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 13:26:14 by thdervil          #+#    #+#             */
/*   Updated: 2019/11/03 13:26:42 by thdervil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_no_args(t_mshell *mshell, int i)
{
	while (mshell->whole_env[i])
	{
		if (!ft_strncmp(mshell->whole_env[i], "HOME=", 5))
			mshell->cd_dir = ft_strdup(mshell->whole_env[i] + 5);
		i++;
	}
}

void	cd_minus(t_mshell *mshell)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strdup(mshell->prev_dir);
	mshell->cd_dir = tmp;
	ft_putendl(mshell->cd_dir);
}
