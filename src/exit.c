/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:17:49 by ancolmen          #+#    #+#             */
/*   Updated: 2023/05/22 16:31:51 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/*
Exit function for all errors. Checks if the allocated elements in the structure
still exist and frees them if that is the case. Exits with errno error if needed
*/
void	free_and_exit(t_data *ppx, char *str, int error)
{
	if (error != 0)
		error_handling(ppx, str, error);
	free_structure(ppx);
	exit(errno);
}

/*
This function will free all the allocted memory if needed, and will exit in error
if the last child exited in error also
*/
void	free_structure(t_data *ppx)
{
	if (ppx->path)
		ft_free_matrix((void **)ppx->path);
	if (ppx->here)
		ft_lstfree(ppx->here);
	if (ppx->cmd)
		ft_lstclear_ppx(ppx->cmd);
	if (ppx->i_fd)
		close(ppx->i_fd);
	if (ppx->o_fd)
		close(ppx->o_fd);
	if (ppx->hd)
	{
		close(ppx->hd_fd[0]);
		close(ppx->hd_fd[1]);
	}
	if (ppx->wstatus)
		exit(EXIT_FAILURE);
}

/*
This function will handle the possible errors, writing them 
in a nicer and personalized 'pipex' way
*/
void	error_handling(t_data *ppx, char *str, int error)
{
	if (error > 0)
	{	
		errno = error;
		ft_putstr_fd("pipex: ", 2);
		if (str)
		{	
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": ", 2);
		}
		perror(NULL);
	}
	if (error < 0 && ppx->child)
	{
		errno = 127;
		ft_putstr_fd("pipex: ", 2);
		if (str)
		{	
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": ", 2);
		}
		if (error == -1)
			ft_putstr_fd("command not found\n", 2);
	}
}

/*
Cleans the linked list and the different arrays inside
*/
void	ft_lstclear_ppx(t_lst *lst)
{
	t_lst	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		if (lst->cmd_op)
			ft_free_matrix((void **)lst->cmd_op);
		if (lst->path)
			free(lst->path);
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}

/*
Cleans the linked list and the different arrays inside
*/
void	ft_lstfree(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		if (lst->content)
			free(lst->content);
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}
