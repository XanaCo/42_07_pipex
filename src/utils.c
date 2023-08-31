/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:06:29 by ancolmen          #+#    #+#             */
/*   Updated: 2023/05/22 16:29:47 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/*
This function creates the number of pipes needed, which depends on 
the number of processes (commands in the arguments) passed
*/
void	create_pipes(t_data *ppx)
{
	int	i;

	i = 0;
	if (ppx->hd)
	{
		if (pipe(ppx->hd_fd) == -1)
			free_and_exit(ppx, NULL, errno);
	}
	while (i < ppx->n_cmds - 1)
	{
		if (pipe(ppx->pipe[i]) == -1)
			free_and_exit(ppx, NULL, errno);
		i++;
	}
}

/*
This function closes all the pipes in the current process
*/
void	close_all_pipes(t_data *ppx)
{
	int	i;

	i = 0;
	if (ppx->hd)
	{	
		close(ppx->hd_fd[0]);
		close(ppx->hd_fd[1]);
	}
	while (i < ppx->n_cmds - 1)
	{
		close(ppx->pipe[i][0]);
		close(ppx->pipe[i][1]);
		i++;
	}
}

/*
This function will wait for every child process generated
*/
void	wait_for_all(t_data *ppx)
{
	int	i;

	i = 0;
	while (i < ppx->n_cmds)
	{
		waitpid(-1, &ppx->wstatus, 0);
		i++;
	}
}

/*
This function writes in the special hd pipe created
*/
void	print_hd(t_data *ppx)
{
	t_list	*elem;
	int		i;

	i = 0;
	elem = ppx->here;
	while (elem)
	{
		ft_putstr_fd((char *)elem->content, ppx->hd_fd[1]);
		elem = elem->next;
	}
}
