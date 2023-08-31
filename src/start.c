/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:12:52 by ancolmen          #+#    #+#             */
/*   Updated: 2023/05/22 18:34:52 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/*
This function starts the process for the first command. If there is a here_doc,
the here_doc process starts, if not, the function opens infile, redirects STDIN 
and STDOUT, closes all pipes and executes the command
*/
void	first_process(t_data *ppx, char **argv, t_lst *iter, char **envp)
{
	ppx->child = 1;
	if (ppx->hd)
	{
		here_doc(ppx);
		if (dup2(ppx->hd_fd[0], STDIN_FILENO) == -1)
			free_and_exit(ppx, NULL, errno);
		close(ppx->hd_fd[0]);
		if (dup2(ppx->pipe[0][1], ppx->hd_fd[1]) == -1)
			free_and_exit(ppx, NULL, errno);
	}
	else
	{	
		ppx->i_fd = open(argv[1], O_RDONLY, 0755);
		if (ppx->i_fd == -1)
			free_and_exit(ppx, argv[1], errno);
		if (dup2(ppx->i_fd, STDIN_FILENO) == -1)
			free_and_exit(ppx, NULL, errno);
		close(ppx->i_fd);
	}
	if (dup2(ppx->pipe[0][1], STDOUT_FILENO) == -1)
		free_and_exit(ppx, NULL, errno);
	close_all_pipes(ppx);
	if (execve(iter->path, iter->cmd_op, envp) == -1)
		free_and_exit(ppx, iter->arg, -1);
}

/*
This function will start the process for the last command. It will redirect 
STDIN, STDOUT and create the outfile if it does not exist. Then will close all 
open pipes and execute the last command finishing the process
*/
void	last_process(t_data *ppx, char **argv, t_lst *iter, char **envp)
{
	ppx->child = 1;
	if (dup2(ppx->pipe[ppx->n_cmds - 2][0], STDIN_FILENO) == -1)
		free_and_exit(ppx, NULL, errno);
	close_all_pipes(ppx);
	if (ppx->hd)
		ppx->o_fd = open(argv[ppx->argc], O_RDWR | O_CREAT | O_APPEND, 0755);
	else
		ppx->o_fd = open(argv[ppx->argc], O_RDWR | O_CREAT | O_TRUNC, 0755);
	if (ppx->o_fd == -1)
		free_and_exit(ppx, argv[ppx->argc], errno);
	if (dup2(ppx->o_fd, STDOUT_FILENO) == -1)
		free_and_exit(ppx, NULL, errno);
	close(ppx->o_fd);
	if (execve(iter->path, iter->cmd_op, envp) == -1)
		free_and_exit(ppx, iter->arg, -1);
}

/*
This function will start the process for the commands in the middle. 
It will redirect STDIN, STDOUT, close all open pipes and execute the 
commands finishing each process
*/
void	middle_process(t_data *ppx, int i, t_lst *iter, char **envp)
{
	ppx->child = 1;
	if (dup2(ppx->pipe[i - 1][0], STDIN_FILENO) == -1)
		free_and_exit(ppx, NULL, errno);
	if (dup2(ppx->pipe[i][1], STDOUT_FILENO) == -1)
		free_and_exit(ppx, NULL, errno);
	close_all_pipes(ppx);
	if (execve(iter->path, iter->cmd_op, envp) == -1)
		free_and_exit(ppx, iter->arg, -1);
}

/*
This function will launch the here_doc process. It will write directly into the 
pipe each command line and will stop when the line is the key word (without 
taking it into account)
*/
void	here_doc(t_data *ppx)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		ft_putstr_fd("> ", 2);
		line = get_next_line(STDIN_FILENO);
		tmp = ft_strtrim(line, "\n");
		if (!line
			|| !(ft_strncmp(tmp, ppx->key_word, ft_strlen(ppx->key_word) + 1)))
		{
			free(tmp);
			free(line);
			break ;
		}
		errno = 0;
		add_to_list_hd(ppx, line);
		free(tmp);
	}
	print_hd(ppx);
}

/*
This function will create with fork the different processes needed for each 
argument. It will check if we are in the first, middle or last process
and act accordingly, moving on to the next command. All child processes should 
end before leaving this function
*/
void	start_pipex(t_data *ppx, char **argv, char **envp)
{
	int		i;
	t_lst	*iter;

	i = 0;
	iter = ppx->cmd;
	while (i < ppx->n_cmds)
	{
		ppx->pids[i] = fork();
		if (ppx->pids[i] == -1)
			free_and_exit(ppx, NULL, errno);
		if (ppx->pids[i] == 0 && i == 0)
			first_process(ppx, argv, iter, envp);
		else if (ppx->pids[i] == 0 && i == ppx->n_cmds - 1)
			last_process(ppx, argv, iter, envp);
		else if (ppx->pids[i] == 0 && i != ppx->n_cmds - 1 && i != 0)
			middle_process(ppx, i, iter, envp);
		iter = iter->next;
		i++;
	}
	close_all_pipes(ppx);
	wait_for_all(ppx);
}
