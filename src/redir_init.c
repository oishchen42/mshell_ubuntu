/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 21:22:57 by nmikuka           #+#    #+#             */
/*   Updated: 2025/08/01 23:28:52 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

static t_redir	*create_redir(t_redir_type type, char *filename);

t_redir_type	get_redir_type(const char *token)
{
	if (!token)
		return (-1);
	if (ft_strncmp(token, ">>", 2) == 0)
		return (REDIR_APPEND);
	if (ft_strncmp(token, "<<", 2) == 0)
		return (REDIR_HEREDOC);
	if (ft_strncmp(token, "<", 1) == 0)
		return (REDIR_INPUT);
	if (ft_strncmp(token, ">", 1) == 0)
		return (REDIR_OUTPUT);
	return (REDIR_NONE);
}

int	add_redirection(t_list **redirections, t_token *tokens, int i)
{
	t_redir	*redir_data;
	t_list	*new_node;

	if (!redirections || !tokens || !tokens[i].content)
		return (-1);
	if (!tokens[i + 1].content)
	{
		printf("Error: missing filename after '%s'\n", tokens[i].content);
		return (-1);
	}
	redir_data = create_redir(tokens[i].redir_type, tokens[i + 1].content);
	if (!redir_data)
	{
		printf("Error: failed to create redirection data\n");
		return (-1);
	}
	new_node = ft_lstnew((void *)redir_data);
	if (!new_node)
	{
		free_redir_content((void *)redir_data);
		printf("Error: failed to create list node\n");
		return (-1);
	}
	ft_lstadd_back(redirections, new_node);
	return (0);
}

static t_redir	*create_redir(t_redir_type type, char *filename)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->filename = ft_strdup(filename);
	if (!redir->filename)
	{
		free(redir);
		return (NULL);
	}
	redir->heredoc_delimiter = NULL;
	if (type == REDIR_HEREDOC)
		redir->heredoc_delimiter = ft_strdup(filename);
	return (redir);
}

void	free_redir_content(void *content)
{
	t_redir	*redir;

	if (!content)
		return ;
	redir = (t_redir *)content;
	free(redir->filename);
	if (redir->heredoc_delimiter)
		free(redir->heredoc_delimiter);
	free(redir);
}

// TODO: delete this for the final version
void	print_redirections(t_list *redirections)
{
	t_list	*current;
	t_redir	*redir_data;
	char	*type_names[] = {"NONE", "INPUT(<)", "OUTPUT(>)",
		"APPEND(>>)", "HEREDOC(<<)"};

	current = redirections;
	while (current)
	{
		redir_data = (t_redir *)current->content;
		printf("  Redirection: %s %i %s\n",
			type_names[redir_data->type],
			redir_data->type,
			redir_data->filename);
		current = current->next;
	}
}
