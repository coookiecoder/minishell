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

int	ft_strlen(const char *str)
{
	int	a;

	a = 0;
	while (str && *(str + a))
		a++;
	return (a);
}

int	ft_strclen(const char *str, const char stop)
{
	int	a;

	a = 0;
	while (str && *(str + a) && *(str + a) != stop)
		a++;
	return (a);
}
