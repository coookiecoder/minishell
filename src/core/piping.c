/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   NOOT NOOT MOTHER FUCKER                      :#:  :#:         :#:  :#:   */
/*                                                :#:  :#::#     #::#:  :#:   */
/*   By: an asshole who like to break thing       :#:  :#::#: # :#::#:  :#:   */
/*                                                :##::##: :#:#:#: :##::##:   */
/*   Created: the-day-it-was created by UwU        :####:  :##:##:  :####:    */
/*   Updated: the-day-it-was updated by UwU                                   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	duplicate_input(size_t pos, t_exec *exe)
{
	if (pos)
	{
		if (pos % 2 == 1)
			dup2(exe->fds_odd[0], STDIN_FILENO);
		else
			dup2(exe->fds_even[0], STDIN_FILENO);
	}
}

void	duplicate_output(size_t pos, t_exec *exe)
{
	if (pos < exe->total - 1)
	{
		if (pos % 2 == 0)
			dup2(exe->fds_odd[1], STDOUT_FILENO);
		else
			dup2(exe->fds_even[1], STDOUT_FILENO);
	}
}

void	close_fd(size_t pos, t_exec *exe)
{
	if (pos % 2 == 1)
	{
		if (exe->fds_odd[0] >= 0)
			close(exe->fds_odd[0]);
		if (exe->fds_odd[1] >= 0)
			close(exe->fds_odd[1]);
	}
	else
	{
		if (exe->fds_even[0] >= 0)
			close(exe->fds_even[0]);
		if (exe->fds_even[1] >= 0)
			close(exe->fds_even[1]);
	}
}

void	new_pipe(size_t pos, t_exec *exec)
{
	if (pos % 2 == 0)
		pipe(exec->fds_odd);
	else
		pipe(exec->fds_even);
}
