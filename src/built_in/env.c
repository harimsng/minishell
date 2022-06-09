/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 18:24:02 by gson              #+#    #+#             */
/*   Updated: 2022/06/09 18:14:25 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static int	check_arg_error(int argc, char **argv)
{
	if (argc > 1)
	{
		printf("env: %s: No such file or directory\n", argv[1]);
		return (1);
	}
	return (0);
}

int	env(t_dlist *envlist, int argc, char **argv)
{
	t_env	*cur_env;

	if (check_arg_error(argc, argv) == 1)
		return (1);
	envlist->cur = envlist->head;
	while (envlist->cur != 0)
	{
		cur_env = (t_env *)envlist->cur->content;
		if (cur_env->has_equal == 1)
		{
			if (cur_env->value == NULL)
				printf("%s=\n", cur_env->key);
			else
				printf("%s=%s\n", cur_env->key, cur_env->value);
		}
		envlist->cur = envlist->cur->next;
	}
	return (0);
}