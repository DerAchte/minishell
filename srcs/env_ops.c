/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdervil <thdervil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:41:30 by derachte          #+#    #+#             */
/*   Updated: 2019/11/03 13:44:35 by thdervil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		replace_1link(t_envlist *new, t_envlist *ante_old)
{
	t_envlist *to_del;

	to_del = ante_old->next;
	new->next = ante_old->next->next;
	ante_old->next = new;
	free(to_del);
	ft_bzero(to_del, sizeof(*to_del));
}

t_envlist	*add_env(char *add, int manu, int eph)
{
	t_envlist *ret;

	if (!(ret = (t_envlist *)malloc(sizeof(t_envlist))))
		return (NULL);
	ret->line = ft_strdup(add);
	ret->next = NULL;
	ret->prev = NULL;
	ret->manual = manu;
	ret->ephemere = eph;
	return (ret);
}

void		var_pushback(int manu, int eph, t_envlist *env_list, char *envpath)
{
	t_envlist *new;
	t_envlist *tmp;

	new = add_env(envpath, manu, eph);
	if (check_existing(new, env_list))
		return ;
	while (env_list->next->next)
		env_list = env_list->next;
	tmp = env_list->next;
	env_list->next = new;
	new->next = tmp;
}

void		env_pushback(int manu, int eph, t_envlist *env_list, char *envname)
{
	while (env_list->next)
		env_list = env_list->next;
	env_list->next = add_env(envname, manu, eph);
	env_list->next->prev = env_list;
}
