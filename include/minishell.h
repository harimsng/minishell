/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:59:46 by hseong            #+#    #+#             */
/*   Updated: 2022/06/05 14:43:20 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "types.h"
# include "parser/token.h"

t_dlist	*parser(const char *line, t_dlist *env_list);
t_dlist	*temp_parse(const char *line, t_dlist *env_list);

void	print_item(t_token *token);
void	delete_item(t_token **token);

#endif
