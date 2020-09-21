#include "filename_sanitizer.h"

int main(int argc, char *argv[])
{
	//Check input arg number
	check_args(argc);
	
	//Find length of filename
	uint8_t length=get_argument_length(argv[1]);
	
	//Create output filename string
	uint8_t* filename_o = NULL;
	create_output(length,&filename_o);
	
	//Sanitize input
	sanitize((uint8_t*)argv[1], length, filename_o);
	
	//Output new filename
	printf("%s",filename_o);
	
	//Cleanup
	if(filename_o!=NULL){free(filename_o);filename_o=NULL;}
	return 0;
}

//@desc: sanitize input argument do not print consecutive underscores
//@return: none
void sanitize(uint8_t *input, uint8_t input_s, uint8_t *output)
{
	uint8_t dot_pos = 0;
	bool dot_valid = false;
	//Find extension dot (last dot in string)
	for(uint8_t i=0;i<input_s;i++)
	{
		if(input[i]==ASCII_DOT)
		{
			dot_pos = i;
		}
	}
	//Record previous character to avoid printing consecutive underscores
	uint8_t prev_c = 0x00;
	uint8_t new_c = 0x00;
	uint8_t output_s = 0; 
	for(uint8_t j=0;j<input_s;j++)
	{
		if(j==dot_pos)
		{
			dot_valid=true;
		}
		//Substitute with valid character if invalid / exempt extension dot
		new_c=is_allowed(input[j],dot_valid);
		//Check previous characters
		if((new_c==prev_c)&&(new_c==ASCII_UNDERSCORE))
		{
			//ignore character
			continue;
		}
		else
		{
			//pass to output
			output[output_s]=new_c;
			output_s++;
			prev_c=new_c;
		}
	}
	return;
}

//@desc: Check is char is allowed
//@return: Subsitution (same if allowed, _ if not allowed)
char is_allowed(char eval, bool dot_valid)
{
	//Allow A-Z (0x41 to 0x5A inclusive)
	//Allow a-z (0x61 to 0x7A inclusive)
	//Allow 0-9 (0x30 to 0x39 inclusive)
	//Allow . if dot_valid is true (0x2E)
	//Allow _ (0x5F)
	//Replace invalid with _ (0x5F)
	if( ((eval>=0x41)&&(eval<=0x5A)) || ((eval>=0x61)&&(eval<=0x7A)) || ((eval>=0x30)&&(eval<=0x39)) || ((eval==0x2E)&&(dot_valid==true)) || (eval==0x5F) )
	{
		return eval;
	}
	else
	{
		return 0x5F;
	}
}

//@desc: Create a buffer of specific length and add 1 byte for the NULL-term
//@return: none
void create_output(uint8_t length, uint8_t **buffer)
{
	*buffer=NULL;
	//add 1 more byte for the null termination
	*buffer=malloc((length+1)*sizeof(uint8_t));
	if(*buffer==NULL)
	{
		error_handler((uint8_t*)"@create_out_buffer: Failed to allocate memeory!",1);
	}
	//Initialize to 0x00
	memset(*buffer,0x00,(length+1)*sizeof(uint8_t));
	
	return;
}
	
//@desc: Find length of a null-terminated input string using the null character
//@return: string length
uint8_t get_argument_length(char *input)
{
	char curr;
	uint8_t length=0;
	do
	{
		curr=*(input+length*sizeof(char));
		//fins null terminator or cap a 255 characters
		if(curr==0x00||length==255)
		{
			break;
		}
		else
		{
			length++;
		}
	}
	while(1);

	return length;
}

//@desc: Check the number of input args
//@return: none
void check_args(int arg_nb)
{
	if(arg_nb!=2)
	{
		error_handler((uint8_t*)"Invalid number of arguments!",1);
	}
	return;	
}

//@desc: Handles errors. It classifies them as fatal and non fatal and prints error message!
//@return: none
void error_handler(uint8_t* message, uint8_t action)
{
	switch (action)
	{
		//Non-fatal
		case 0:
			printf("--> %s\n",message);
			break;
		//Fatal
		case 1:
			printf("--> %s\n",message);
			printf("FATAL...Exiting!\n");
			exit(1);
			break;
		default:
			printf("-->Unknown Error\n");
			exit(1);
	}
	return;
}




