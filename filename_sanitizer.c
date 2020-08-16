#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>

int check_args(int arg_nb);
void errors(int type);
uint8_t get_argument_length(char *input);
void create_out_buffer(uint8_t length,char** ptr_to_loc_filename_o);
char is_allowed(char eval, bool dot_valid);
void sanitize(uint8_t length,char* input, char* filename_o);

void main(int argc, char *argv[])
{
	//Check input arg number
	check_args(argc);
	//Find length of filename
	uint8_t length=get_argument_length(argv[1]);
	//Create output filename string
	char* filename_o=NULL;
	create_out_buffer(length,&filename_o);
	//Sanitize input
	sanitize(length,argv[1],filename_o);
	//Output new filename
	printf("%s",filename_o);
	//Cleanup
	free(filename_o);
	exit(0);

	
}

void sanitize(uint8_t length,char* input, char* filename_o)
{
	uint8_t pos=length;
	bool dot_valid = false;
	uint8_t ext_dot_pos=255;
	uint8_t fn_o_counter = 0;
  char prev=0x00;
	char undsc=0x5F;
	char tmp=0x00;
	
	//Find extension dot (usually first dot from the end)
	do
	{
		pos=pos-1;
		if (input[pos]==0x2E){ext_dot_pos=pos;break;}

	}while(pos!=0);

	for(uint8_t i=0; i<length;i++)
	{
		if(i==ext_dot_pos){dot_valid=true;}

		tmp=is_allowed(input[i],dot_valid);
		if((tmp==undsc)&&(prev==undsc)){continue;}
		else
		{
			filename_o[fn_o_counter]=tmp;
			fn_o_counter++;
			prev=tmp;
		}
	}


}


char is_allowed(char eval, bool dot_valid)
{
	//Allow A-Z (0x41 to 0x5A inclusive)
	//Allow a-z (0x61 to 0x7A inclusive)
	//Allow 0-9 (0x30 to 0x39 inclusive)
	//Allow _ (0x5F)
	//Allow . if dot_valid is true (0x2E)
	//Replace invalid with _ (0x5F)

	if(((eval>=0x41)&&(eval<=0x5A))||((eval>=0x61)&&(eval<=0x7A))||((eval>=0x30)&&(eval<=0x39))||((eval==0x2E)&&(dot_valid==true))||(eval==0x5F)){return eval;}
	else{return 0x5F;}

	
	


}

void create_out_buffer(uint8_t length,char** ptr_to_loc_filename_o)
{
	*ptr_to_loc_filename_o=(char*)malloc((length+1)*sizeof(char));
	//fill with 0x00 so that it can be printed with %s
	for (uint8_t i=0; i<=length; i++)
	{
		*(*ptr_to_loc_filename_o + (i*sizeof(char)))=0x00;
	}	
}


uint8_t get_argument_length(char *input)
{

	char curr;
	uint8_t length=0;

	do
	{
		curr=*(input+length*sizeof(char));
		if(curr==0x00||length==255){break;}
		else{length++;}
	}
	while(1);

	return length;
}

int check_args(int arg_nb)
{

	if(arg_nb!=2)
	{
		if(arg_nb==1){errors(0);}
		else{errors(1);}
	}
	else{return 0;}
		
}


void errors(int type)
{
	switch (type)
	{
		case 0:
			printf("Not enough arguments\n");
			break;
		case 1:
			printf("Too many arguments\n");
			break;
		default:
			printf("Unknown Error\n");
			break;
	}
	exit(1);
}




