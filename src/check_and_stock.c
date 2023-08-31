/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_stock.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:09:51 by ancolmen          #+#    #+#             */
/*   Updated: 2023/05/22 18:29:53 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/*
Stocks splited path lines from variable $PATH from the 5th character (P.A.T.H.=) 
in a char** in the main structure, with ":" as separator
*/
void	stock_path(t_data *ppx, char **envp)
{
	int	i;

	i = 0;
	if (!*envp)
		return ;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH", 4))
			ppx->path = ft_split((envp[i] + 5), ':');
		i++;
	}
}

/*
Stocks commands in linked list in main structure. First command will vary if 
there is a 'here_doc' argument or not. If there is, first command will be 
argv[3]. If not, the list will start from argv[2].
*/
void	stock_cmd(t_data *ppx, char **argv, int argc)
{
	int	i;
	int	pos;

	i = argc - 2;
	pos = 1;
	if (ppx->hd)
		pos = 2;
	while (i > pos)
	{
		add_to_lst(ppx, argv[i]);
		get_exec_path(ppx);
		i--;
	}
}

/*
Called by stock_cmd, this function will get the final exec path and store it 
for each command node. It will also check if its path is absolute or relative
*/
void	get_exec_path(t_data *ppx)
{
	int		i;
	char	*cmd;

	i = 0;
	cmd = ppx->cmd->arg;
	if (ppx->cmd->cmd_op)
		cmd = ppx->cmd->cmd_op[0];
	if (ft_strchr(ppx->cmd->arg, '/') && !access(cmd, X_OK))
		ppx->cmd->path = ft_strdup(cmd);
	else if (!ft_strchr(ppx->cmd->arg, '/'))
	{
		if (!ppx->path)
			return ;
		cmd = ft_strjoin("/", cmd);
		while (ppx->path[i])
		{
			free(ppx->cmd->path);
			ppx->cmd->path = ft_strjoin(ppx->path[i], cmd);
			if (!access(ppx->cmd->path, X_OK))
				break ;
			errno = 0;
			i++;
		}
		free(cmd);
	}
}

/*
Adds new command to the linked list or creates the first element 
if it is not already there
*/
void	add_to_lst(t_data *ppx, char *str)
{
	t_lst	*new;

	new = (t_lst *)malloc(sizeof(t_lst));
	if (!new)
		free_and_exit(ppx, NULL, errno);
	new->arg = str;
	new->cmd_op = ft_split(str, ' ');
	new->path = NULL;
	new->next = NULL;
	if (!ppx->cmd)
		ppx->cmd = new;
	else
	{
		new->next = ppx->cmd;
		ppx->cmd = new;
	}
}

/*
Adds new command to the linked list or creates the first element 
if it is not already there
*/
void	add_to_list_hd(t_data *ppx, char *str)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		free_and_exit(ppx, NULL, errno);
	new->content = str;
	new->next = NULL;
	ft_lstadd_back(&ppx->here, new);
}
