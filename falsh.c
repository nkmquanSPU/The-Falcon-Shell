#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

void help_message();

int main(int argc, char* argv[])
{
	char help_flag[256] = "-h";
	char exit[256] = "exit";
	char pwd[256] = "pwd";
	char cd[256] = "cd";
	char setpath[256] = "setpath";
	char help[256] = "help";
	char *cmd;	
	char current_directory[256];
	char new_directory[256];
	char buffer[256];
	int i, j = 0;
	int count = 0;
	
	if (argc == 1) //if user enter './flash' and hit Enter
	{			
		//buffer[256] = '\0';
		//printf("falsh> ");
		//scanf("%s", &cmd); //get user's input and eliminate all white spaces
		
		fgets(buffer, 256, stdin); //get input from user. This may contains whitespaces
		
		//printf("%s", buffer);
		//return 0;
		/*
		for (i = 0; buffer[i] != '\0'; i++)
		{
			if(buffer[i] != ' ')
			{
				cmd[j] = cmd[i];
				j++;
			}				
		}
		cmd[j++] = '\0';
		j = 0;
		*/
		//buffer.erase(remove(buffer.begin(), buffer.end(), ' '), buffer.end());
		/*
		char *cmd = buffer;
		
		for (i = 0, j = 0; i < strlen(buffer); i++, j++)          
		{
			if (buffer[i] != ' ')                           
				cmd[j] = buffer[i];                     
			else
				j--;                                     
		}
		cmd[j] = 0;
		*/
		
		cmd = buffer;
		//this loop eliminate whitespaces in buffer
		// and put all the chars into cmd
		for (i = 0; i < strlen(buffer); i++)          
		{
			if (buffer[i] != ' ')                           
				cmd[j] = buffer[i];                     
			else
				j--;
			j++;
		}
		cmd[j - 1] = 0; //add NULL to the end cmd
		j = 0;
		
		//printf("%s ", cmd);
		//printf("%lu\n", strlen(cmd));
		//return 0;
		
		//while the user's cmd is not 'exit'
		// get user's cmd and perform it.		
		while(strcmp(cmd, exit) != 0) 
		{
			if(strcmp(cmd, pwd) == 0) 
			{	
				//print the current working directory
				printf("Current directory: %s\n", getcwd(current_directory, 256));
			}			
		    else if((cmd[0] == 'c') && (cmd[1] == 'd'))
			{	
				/*
				if(strlen(cmd) > 2)
				{					
					//for (i = 2; i < strlen(cmd) - 1; i++)					
						//new_directory[i - 2] = cmd[i];
					
					//chdir(new_directory);
					printf("%s\n", cmd);						
				}
				else
				{
					//if no arguments are provided, change to the user’s home directory
					chdir(getenv("HOME"));					
				}
				*/
				printf("%s\n", cmd);
				
			}
			else if(strcmp(cmd, setpath) == 0)
			{
				printf("setpath\n");
			}
			else if(strcmp(cmd, help) == 0)
			{
				help_message();
			}
			else //if error occurs
			{
				printf("Command not found.\n");
			}
			
			//buffer[256] = '\0';
			//printf("falsh> ");		
			
			fgets(buffer, 256, stdin); //get input from user. This may contains whitespaces
			
		    cmd = buffer;
			//this loop eliminate whitespaces in buffer
			// and put all the chars into cmd
			for (i = 0; i < strlen(buffer); i++)          
			{
				if (buffer[i] != ' ')                           
					cmd[j] = buffer[i];                     
				else
					j--;
				j++;
			}
			cmd[j -1] = 0; //add NULL to the end cmd
			j = 0;
			//buffer[256] = '\0';
			//scanf("%s", &cmd); //get user's input and eliminate all white spaces					
		}			
		
		return 0;
	}
	else if(strcmp(argv[1], help_flag) == 0) //if user enter './falsh -h'
	{	
		help_message();	
		return 0;					
	}	
	
	return 0;
}

/*
This function list all built-in commands with short, user-friendly descriptions.
Parameter: None
Return: None 
*/
void help_message()
{
	printf("\n");
	printf("These are the built-in commands of falsh shell.\n"); 
	printf("Type './falsh -h' to see this list.\n");
	printf("\n");
	printf("	exit - exit the program.\n");
	printf("	Usage: exit\n");
	printf("\n");
	printf("	pwd - print the current working directory.\n");
	printf("	Usage: pwd\n");
	printf("\n");
	printf("	cd - change directory.\n");
	printf("	Usage: cd\n");
	printf("\n");
	printf("	setpath - sets the path, user must provide at least one argument (directory).\n");
	printf("	Usage: setpath <dir> [dir] … [dir]\n");
	printf("\n");
	
}