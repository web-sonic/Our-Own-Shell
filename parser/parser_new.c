









/* 
** @params: char *str, t_list **tokens
** TODO: добавляет в список новую лексему аргумент
**	и сдивагет строку на следующую лексему
** @return NULL
*/
static void
	add_argument(char **str, t_list **tokens)
{
	char *token;

	token = treat_str(str);
	if (token && *token)
		ft_lstadd_back(tokens, ft_lstnew(token));
}