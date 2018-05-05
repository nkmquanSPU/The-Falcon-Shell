#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
 
void help_message();

int main(int argc, char* argv[])
{
	FILE *file_ptr;
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
	char temp[256];
	char new_data[256];	
	int i, j = 0;
	int count = 0;
	int index;
	
	if (argc == 2) //to run non-built-in command
	{
		char *command_name[1]; //for example new_cat.c or new_wc.c
		pid_t pid; //process's ID
		int status_process;		
		char *exec_file = command_name[1];
		
		if ((pid = fork()) < 0) //fork() the child process
		{		
			printf("fork() failed."); //fork() has failed		
		}
		else if (pid == 0)
		{		
			if (execv(exec_file, command_name) < 0) //execute the command_name
			{	
				printf("execv() failed."); //execv() has failed		
			}			
		}
		else
			while (wait(&status_process) != pid); //wait for the child to return
	}
	else if (argc == 1) //if user enter './flash' and hit Enter
	{			
		
		printf("falsh> ");	
		
		//erase values of temp and buffer before give them new ones 
		memset(temp, 0, 255); 
		memset(buffer, 0, 255); 
		fgets(buffer, 256, stdin); //get input from user. This may contains whitespaces				
		stpcpy(temp, buffer); //copy value of buffer to temp
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
		
		//while the user's cmd is not 'exit'
		// get user's cmd and perform it.		
		while(strcmp(cmd, exit) != 0)  // while the command is not the 'exit'
		{
			if(strcmp(cmd, pwd) == 0) //pwd command
			{	
				/*
				Get the current working directory.
				Put it into the array of char which current_directory is pointing to.
				*/
				getcwd(current_directory, 256);
				printf("Current directory: %s\n", directory, 256);				
			}			
		    else if((cmd[0] == 'c') && (cmd[1] == 'd'))	//cd command		
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
				}
				else //if [dir] are not provided, change to user’s home directory
				{				
					chdir(getenv("HOME"));					
				}				
				
			} 	
			else if((cmd[0] == 's') && //setpath command		
				(cmd[1] == 'e') &&
				(cmd[2] == 't') &&
				(cmd[3] == 'p') &&
				(cmd[4] == 'a') &&
				(cmd[5] == 't') &&
				(cmd[6] == 'h'))	
			{
				if (strlen(cmd) > 8)
				{	
					//the PATH when falsh launches contains only /bin.
					setenv("PATH", "/bin", 1);
					printf("\nOriginal PATH: %s\n", getenv("PATH"));
					char *env_name;
					
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
					// and overwrite the path
					setenv("PATH", path, 1);
					if (env_name != NULL)
						printf("%s is set.\n", getenv("PATH"));	
							
					setenv("PATH", path, 1);
					printf("PATH now contains: %s\n\n", getenv("PATH"));												
				}
			}
			else if(strcmp(cmd, help) == 0) //help command
			{
				help_message(); //print out help message
			}
			else if((cmd[0] == 'c') && //Redirection: command > file_name
					(cmd[1] == 'o') &&
					(cmd[2] == 'm') &&
					(cmd[3] == 'm') &&
					(cmd[4] == 'a') &&
					(cmd[5] == 'n') &&
					(cmd[6] == 'd'))								
			{							
				//erase values of new_data and file_name before give them new ones
				memset(new_data, 0, 255); 
				memset(file_name, 0, 255); 
				
				//find the index of '>' in user's input
				char *ptr = NULL;					
				
				ptr = strchr(temp, '>');  //returns the pointer to the first occurrence of '>'
				index = ptr - temp; //get the index of '>'
				
				if ((ptr == NULL) || (strlen(temp) == index + 2))
				{
					printf("	Filename is missing.\n");
					printf("	Cannot run the command.\n");
				}				
				else
				{																		
					ptr = NULL; //set ptr to NULL so that we can re-use it for
								// later inputs from user
					
					j = 0;
					//get new data from user for the file
					for(i = 8; i < index - 1; i++)
					{
						new_data[j] = temp[i];
						j++;
					}
					new_data[j + 1] = 0; //add NULL to the end of new path	
					
					j = 0;
					//get file name from user														
					for (i = index + 2; i < strlen(temp) - 1; i++)
					{						                          
						file_name[j] = temp[i]; //update the path with user's input
						j++;						
					}										
					file_name[j + 1] = 0; //add NULL to the end of new path					
					j = 0;					
										
					/*
					Open the file so that it is write only or read only.
					If the file does not exist, create it.
					*/
					int file_descriptor = open(file_name, O_WRONLY | O_APPEND | O_CREAT);
					
					if (file_descriptor < 0) //invalid file descriptor 
					{
						printf("The value of file descriptor is invalid.");
						return 0;
					}
					else
					{
						//open and write fileno(stdout) to file_name
						//int std_out = dup(STDOUT_FILENO); //creates a copy of a file descriptor
						int std_out = open(file_name, O_WRONLY, stdout);
							
						if (std_out == 1)
						{
							write(std_out,new_data, 51); //write new_date to .out file
							//redirect the output of stdout to file_name.out
							dup2(std_out, STDOUT_FILENO);							
							close(std_out);
						}
						else
						{
							char error_message[80] = "Error writing to" ;
							strcat(error_message, file_name);
							
							//open and append fileno(stderr) to file_name
							//int std_err = dup(STDERR_FILENO);
							int std_err = open(file_name, O_APPEND, stderr);						
							write(std_err,error_message, 51); //write new_date to .err file
							
							//redirect the output of stderr to file_name.err
							dup2(std_err, STDERR_FILENO);
							close(std_err);
						}																		
					}					
					
				}																																				
			}
			else //if user enters an invalid command
			{
				printf("Command not found.\n");
			}
						
			printf("falsh> ");
			
			//erase values of temp and buffer before give them new ones 
			memset(temp, 0, 255); 
			memset(buffer, 0, 255); 
			
			fgets(buffer, 256, stdin); //get input from user. This may contains whitespaces
			stpcpy(temp, buffer); //copy value of buffer to temp
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
