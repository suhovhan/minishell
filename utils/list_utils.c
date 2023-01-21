#include "../includes/minishell.h"

int	append_token(t_token **token, int type, char *str)
{
	static int	index = -1;
	t_token		*new_node;
	t_token 	*last_node;

	if (*str == '\0')
		return (0);
	new_node = malloc(sizeof(t_token));
	new_node->type = type;
	new_node->index = ++index;
	new_node->token = str;
	new_node->next = NULL;
	new_node->prev = NULL;
	if (*token == NULL)
	{
		index = -1;
		new_node->index = ++index;
		*token = new_node;
	}
	else
	{
		last_node = *token;
		while (last_node->next != NULL)
			last_node = last_node->next;
		new_node->prev = last_node;
		last_node->next = new_node;
	}
	return (0);
}

int	append_pipeexec(t_pipe_exec **pipe_list, char **cmd_line, char *infile, int out)
{
	t_pipe_exec		*new_node;
	t_pipe_exec 	*last_node;

	new_node = malloc(sizeof(t_pipe_exec));
	new_node->infile = infile;
	new_node->output = out;
	new_node->cmd_line = cmd_line;
	new_node->next = NULL;
	if (*pipe_list == NULL)
		*pipe_list = new_node;
	else
	{
		last_node = *pipe_list;
		while (last_node->next != NULL)
			last_node = last_node->next;
		last_node->next = new_node;
	}
	return (0);
}

int	append_filename(t_filename **head, char *str, int pipe_index, int input_index)
{
	t_filename	*new_node;
	t_filename 	*last_node;

	new_node = malloc(sizeof(t_filename));
	new_node->input_index = input_index;
	new_node->pipe_index = pipe_index;
	new_node->filename = str;
	new_node->next = NULL;
	new_node->prev = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		last_node = *head;
		while (last_node->next != NULL)
			last_node = last_node->next;
		new_node->prev = last_node;
		last_node->next = new_node;
	}
	return (0);
}

int	append_env(t_env **env, char *key, char *value)
{
	t_env	*new_node;
	t_env	*last_node;

	new_node = malloc(sizeof(t_env));
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	if (*env == NULL)
		*env = new_node;
	else
	{
		last_node = *env;
		while ((*env)->next != NULL)
			*env = (*env)->next;
		(*env)->next = new_node;
		*env = last_node;
	}
	return (0);
}

void	remove_node_from_token(t_token **token, int index)
{
	t_token	*tmp;

	tmp = *token;
	if ((*token)->index == index)
		tmp = (*token)->next;
	while ((*token)->index != index)
		(*token) = (*token)->next;
	if ((*token)->index == index && !(*token)->prev && !(*token)->next)
	{
		free((*token)->token);
		free((*token));
		*token = NULL;
	}
	else if ((*token)->index == index)
	{
		if ((*token)->prev)
			(*token)->prev->next = (*token)->next;
		if ((*token)->next)
			(*token)->next->prev = (*token)->prev;
		free((*token)->token);
		free((*token));
	}
	*token = tmp;
}

void	clean_space_from_token(t_token	**token)
{
	t_token	*tmp;
	int		index;

	tmp = *token;
	while (tmp)
	{
		if (tmp->type == _SPACE)
		{
			index = tmp->index;
			tmp = tmp->next;
			if (tmp && tmp->type == _SPACE)
				remove_node_from_token(token, index);
		}
		else
			tmp = tmp->next;
	}
}
