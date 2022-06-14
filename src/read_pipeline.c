/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gson <gson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:07:30 by hseong            #+#    #+#             */
/*   Updated: 2022/06/14 22:33:58 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "libft.h"

#include "minishell.h"
#include "cmd.h"
#include "constants.h"
#include "parser/parser.h"

int			generate_process(t_command *command, t_dlist *env_list,
				int pipe_exist);
static int	read_command_list(t_dlist *command_list, t_dlist *env_list);
static int	wait_process(t_dlist *pid_list);

void	read_pipeline(t_dlist *pipeline_list, t_dlist *env_list)
{
	t_pipeline	*pipeline;

	pipeline = get_front(pipeline_list);
	while (pipeline != NULL)
	{
		pipeline->result
			= read_command_list(pipeline->command_list, env_list);
		pop_front(pipeline_list, delete_pipeline_content);
		pipeline = get_front(pipeline_list);
	}
}

int	read_command_list(t_dlist *command_list, t_dlist *env_list)
{
	t_command	*command;
	t_dlist		*pid_list;
	pid_t		pid;
	int			prev_cmd_flag;

	pid_list = dlist_init();
	command = get_front(command_list);
	prev_cmd_flag = 0;
	while (command != NULL)
	{
		if (prev_cmd_flag == CMD_HEREDOC)
		{
			pid = *((pid_t *)get_front(pid_list));
			pop_front(pid_list, free);
			waitpid(pid, NULL, 0);
		}
		pid = generate_process(command, env_list, command_list->size > 1);
		prev_cmd_flag = command->flag;
		pop_front(command_list, delete_command_content);
		command = get_front(command_list);
		push_back(pid_list,
			ft_memcpy(malloc(sizeof(pid_t)), &pid, sizeof(pid_t)));
	}
	return (wait_process(pid_list));
}

int	wait_process(t_dlist *pid_list)
{
	int		status;
	pid_t	pid;

	while (pid_list->size > 0)
	{
		pid = *((pid_t *)get_front(pid_list));
		pop_front(pid_list, free);
		if (pid < 0)
			continue ;
		waitpid(pid, &status, 0);
	}
	dlist_delete(pid_list, free);
	return (status);
}
