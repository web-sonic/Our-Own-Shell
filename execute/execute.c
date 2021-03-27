/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 13:49:34 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/27 17:41:55 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void
	execute(t_list *cmd_lst, t_list *envlst)
{
	int     tmp_fdin;
	int     tmp_fdout;
	t_list  *pipe_lst;
	t_cmd   cmd;

	tmp_fdin = dup(0);
	tmp_fdout = dup(1);
	while (cmd_lst)
	{
		pipe_lst = cmd_lst->content;
		while (pipe_lst)
		{
			cmd = parser(pipe_lst->content, envlst);
			pipe_lst = pipe_lst->next;
		}
		cmd_lst = cmd_lst->next;
	}
}

//  6    //set the initial input 
//  7    int fdin;
//  8    if (infile) {
//  9      fdin = open(infile,O_READ); 
// 10    }
// 11    else {
// 12      // Use default input
// 13      fdin=dup(tmpin);
// 14    }
// 15  
// 16    int ret;
// 17    int fdout;
// 18    for(i=0;i<numsimplecommands; i++) {
// 19      //redirect input
// 20      dup2(fdin, 0);
// 21      close(fdin);
// 22      //setup output
// 23      if (i == numsimplecommands­1){
// 24        // Last simple command 
// 25        if(outfile){
// Draft
// 26          fdout=open(outfile,â€¦â€¦);
// 27        }
// 28        else {
// 29          // Use default output
// 30          fdout=dup(tmpout);
// 31        }
// 32      }
// 33  
// 34       else {
// 35          // Not last 
// 36          //simple command
// 37          //create pipe
// 38          int fdpipe[2];
// 39          pipe(fdpipe);
// 40          fdout=fdpipe[1];
// 41          fdin=fdpipe[0];
// 42       }// if/else
// 43  
// 44       // Redirect output
// 45       dup2(fdout,1);
// 46       close(fdout);
// 47   
// 48       // Create child process
// 49       ret=fork(); 
// 50       if(ret==0) {
// 51         execvp(scmd[i].args[0], scmd[i].args);
// 52         perror(â€œexecvpâ€);
// 53         _exit(1);
// 54       }
// 55     } //  for
// 56   
// 57     //restore in/out defaults
// 58     dup2(tmpin,0);
// 59     dup2(tmpout,1);
// 60     close(tmpin);
// 61     close(tmpout);
// 62  
// 63     if (!background) {
// 64       // Wait for last command
// 65       waitpid(ret, NULL);
// 66     }
// 67  
// 68  } // execute
