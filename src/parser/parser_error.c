/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 21:26:37 by hseong            #+#    #+#             */
/*   Updated: 2022/05/27 22:32:19 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "dlinkedlist.h"
#include "parser/token.h"
#include "parser/parser.h"

static void	command_list_delete(void *command);
static void	word_list_delete(void *token);
static void	redirect_list_delete(void *redirect);

void	parser_error(t_dlist *pipeline_list, t_token *token)
{
	dlist_delete(pipeline_list, pipeline_list_delete);
	ft_putstr_fd("minishell: syntax error near unexpected token`",
		STDERR_FILENO);
	ft_putstr_fd(token->word, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

void	pipeline_list_delete(void *pipeline)
{
	if (((t_pipeline *)pipeline)->command_list != NULL)
		dlist_delete(((t_pipeline *)pipeline)->command_list,
			command_list_delete);
}

void	command_list_delete(void *command)
{
	if (((t_command *)command)->word_list != NULL)
		dlist_delete(((t_command *)command)->word_list, word_list_delete);
	if (((t_command *)command)->redirect_list != NULL)
		dlist_delete(((t_command *)command)->redirect_list, redirect_list_delete);
}

void	word_list_delete(void *token)
{
	free(((t_token *)token)->word);
}

void	redirect_list_delete(void *redirect)
{
	free(((t_redirect *)redirect)->heredoc);
}