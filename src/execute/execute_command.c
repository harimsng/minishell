/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:06:41 by hseong            #+#    #+#             */
/*   Updated: 2022/06/16 19:33:49 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

#include "minishell.h"
#include "cmd.h"
#include "constants.h"
#include "execute.h"

typedef int				(*t_program)(t_dlist *, int, char **);

static int	is_builtin(const char *name);
static int	execute_builtin(t_dlist *env_list, char **argv, int idx);

static const int		g_builtin_tab_size = 7;
static const int		g_internal_builtin_tab_size = 4;
static const char		*g_builtin_name_tab[]
	= {
	"cd",
	"exit",
	"unset",
	"export",
	"echo",
	"env",
	"pwd",
};
static const t_program	g_builtin_tab[7]
	= {
	cd,
	builtin_print_exit,
	unset,
	export,
	echo,
	env,
	pwd
};

int	execute_command(t_dlist *word_list, t_dlist *env_list)
{
	int		idx;
	int		status;
	char	**argv;
	char	**envp;
	char	**path_arr;

	argv = dlist_to_array(word_list, get_word_from_token);
	idx = is_builtin(argv[0]);
	if (idx >= 0)
		status = execute_builtin(env_list, argv, idx);
	else
	{
		path_arr = ft_split(find_env_by_key(env_list, "PATH"), ":");
		envp = dlist_to_array(env_list, env_to_str);
		status = execve_wrapper(argv[0], argv, envp, path_arr);
		free_str_arr(envp);
		free_str_arr(path_arr);
	}
	free(argv);
	return (builtin_set_exit(env_list, status, 0, NULL));
}

int	is_builtin(const char *name)
{
	int		idx;

	idx = 3;
	while (idx < g_builtin_tab_size)
	{
		if (ft_strncmp(name, g_builtin_name_tab[idx],
				ft_strlen(g_builtin_name_tab[idx]) + 1) == 0)
			return (idx);
		++idx;
	}
	return (-1);
}

int	execute_builtin(t_dlist *env_list, char **argv, int idx)
{
	int		argc;

	argc = 0;
	while (argv[argc] != NULL)
		++argc;
	return (g_builtin_tab[idx](env_list, argc, argv));
}

int	is_internal_builtin(t_dlist *word_list)
{
	t_token	*token;
	int		idx;
	char	*name;

	if (word_list->size < 1)
		return (-1);
	token = get_front(word_list);
	name = token->word;
	idx = 0;
	while (idx < g_internal_builtin_tab_size)
	{
		if (ft_strncmp(g_builtin_name_tab[idx], name,
				ft_strlen(g_builtin_name_tab[idx]) + 1) == 0)
		{
			if (idx == g_internal_builtin_tab_size && word_list->size > 1)
				return (-1);
			return (idx);
		}
		++idx;
	}
	return (-1);
}

int	execute_internal_builtin(t_dlist *word_list, t_dlist *env_list, int idx)
{
	int		argc;
	char	**argv;
	int		status;

	argv = dlist_to_array(word_list, get_word_from_token);
	argc = word_list->size;
	status = g_builtin_tab[idx](env_list, argc, argv);
	free(argv);
	return (-status);
}