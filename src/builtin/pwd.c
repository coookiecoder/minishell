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

int	pwd(char **envp)
{
	int	cursor;

	cursor = 0;
	while (*(envp + cursor) && ft_strncmp(*(envp + cursor), "PWD", 3))
		cursor++;
	write(1, *(envp + cursor) + 4, ft_strlen(*(envp + cursor) + 4));
	return (0);
}
