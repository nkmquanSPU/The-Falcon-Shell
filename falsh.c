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
	char path[256];
	char file_name[256];
	char *cmd;	
	char *current_directory;
	char directory[256];
	current_directory = directory;
	char buffer[256];
	//char *path[] = {"/bin"};
	
	int i, j = 0;
	int count = 0;
	
	if (argc == 1) //if user enter './flash' and hit Enter
	{			
		
		printf("falsh> ");				
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
				/*
				Get the current working directory.
				Put it into the array of char which current_directory is pointing to.
				*/
				getcwd(current_directory, 256);
				
				//print the current working directory
				//printf("Current directory: %s\n", getcwd(current_directory, 256));
				printf("Current directory: %s\n", directory, 256);
				//current_directory = NULL;
			}			
		    else if((cmd[0] == 'c') && (cmd[1] == 'd'))			
			{					
				if(strlen(cmd) > 2) //if user enter [dir] [dir] ...
				{	
					//empty the array of char that contains the previous specified directory
					memset(directory, 0, 255); 
						
					i = 0; j = 0;
					
					//extract the [dir] [dir] ... from input														
					for (i = 2; i < strlen(cmd); i++)
					{						                          
						directory[j] = cmd[i]; //update the directory with user's input
						j++;						
					}										
					directory[j + 1] = 0; //add NULL to the end of new directory					
					j = 0;
					
					chdir(current_directory); //change the current directory to new directory
					//printf("%s\n", cmd);						
				}
				else
				{
					//if [dir] are not provided, change to user’s home directory
					chdir(getenv("HOME"));					
				}
				
				//printf("%s\n", cmd);
				
			} //setpath command			
			else if((cmd[0] == 's') && 
				(cmd[1] == 'e') &&
				(cmd[2] == 't') &&
				(cmd[3] == 'p') &&
				(cmd[4] == 'a') &&
				(cmd[5] == 't') &&
				(cmd[6] == 'h'))	
			{
				if (strlen(cmd) > 8)
				{	
					char *env_name;
					//char *env_value;
					
					//empty the array of char that contains the previous specified path
					memset(path, 0, 255); 
						
					i = 0; j = 0;
					
					//extract the [dir] [dir] ... from input														
					for (i = 7; i < strlen(cmd); i++)
					{						                          
						path[j] = cmd[i]; //update the path with user's input
						j++;						
					}										
					path[j + 1] = 0; //add NULL to the end of new path					
					j = 0;
										
					//adds the env_name to the environment with the value path
					//overwrite the path
					setenv(env_name, path, 1);
					
					if (env_name != NULL)
						printf("%s is set.\n", getenv(env_name));										
				}
			}
			else if(strcmp(cmd, help) == 0) //help command
			{
				help_message();
			}
			else if((cmd[0] == 'c') && //Redirection: command > file_name
					(cmd[1] == 'o') &&
					(cmd[2] == 'm') &&
					(cmd[3] == 'm') &&
					(cmd[4] == 'a') &&
					(cmd[5] == 'n') &&
					(cmd[6] == 'd'))								
			{
				i = 0; j = 0;
				//extract file name from input														
				for (i = 8; i < strlen(cmd); i++)
				{						                          
					file_name[j] = cmd[i]; //update the path with user's input
					j++;						
				}										
				file_name[j + 1] = 0; //add NULL to the end of new path					
				j = 0;
				
				
				//freopen(file_name,"a",stderr); 
				//dup2(fileno(stdout), fileno(stderr));
				
				//open and write fileno(stdout) to file_name
				int std_out = dup(fileno(stdout));
				freopen(file_name,"w",stdout);
				
				//open and append fileno(stderr) to file_name
				int std_err = dup(fileno(stderr));
				freopen(file_name,"a",stderr);
				
				//redirect the output of stdout to file_name.out
				dup2(std_out,fileno(stdout));
				close(std_out);
				
				//redirect the output of stderr to file_name.err
				dup2(std_err,fileno(stderr));
				close(std_err);
			}
			else //if error occurs
			{
				printf("Command not found.\n");
			}
						
			printf("falsh> ");		
			
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
