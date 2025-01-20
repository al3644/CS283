#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define BUFFER_SZ 50

//prototypes
void usage(char *);
void print_buff(char *, int);
int  setup_buff(char *, char *, int);

//prototypes for functions to handle required functionality
int count_words(char *, int);
int reverse_words(char *, int); 
void print_words(char *, int); 

void replace_words();

int setup_buff(char *buff, char *user_str, int len){
    int input_i = 0; 	//from user_str 
    int buff_i = 0; 	//from buff  
    int first_word = 1;  
    int prev_space = 0; 

    while (user_str[input_i] != '\0') {
        char c = user_str[input_i++];

        if (c == ' ' || c == '\t') {
            if (first_word) {	//skip first spaces 
                continue; 
            }
	    //for multiple spaces
	    else if (!prev_space){
            	buff[buff_i++] = ' ';
            	prev_space = 1; 
        	}
	} 
	else {
		//count word and reset
		first_word = 0;  	
		buff[buff_i++] = c;
            	prev_space = 0;
            }
    }

    if (prev_space) {
	    buff_i--; 
    }

    while (buff_i < len) {
        buff[buff_i++] = '.';
    }

    if (buff_i > len){
	    return -1;
    }

    return input_i; 
}
  

void print_buff(char *buff, int len){
    printf("Buffer:  [");
    for (int i=0; i<len; i++){
        putchar(*(buff+i));
    }
    printf("]");
    putchar('\n');
}

void usage(char *exename){
    printf("usage: %s [-h|c|r|w|x] \"string\" [other args]\n", exename);

}


int count_words(char *buff, int str_len){
    int word_count = 0;
    int in_word = 0; 	//acts as a true/false

    for (int i = 0; i < str_len; i++){
	    char c = buff[i]; 

	    if (c == ' ' || c == '\t'){
		    in_word = 0; 
	    }
	    else{
		    //if not space, count
		    if (in_word == 0 ){
			word_count++;
		    }
		    	in_word = 1;
	    } 
    }
    return word_count;
}

void reverse_string(char *buff, int str_len){
	int l = 0;		//left char 
	int r = str_len - 1; 	//right char 

	while (l<r){
		char temp = buff[l]; 
		buff[l] = buff[r];
		buff[r] = temp; 

		l++; 
		r--; 
	}
}

void print_words(char *buff, int str_len){
	int word_index = 1; 
	int c_index = 0; 
	int word_start = -1; 

	printf("Word Print\n"); 
    	printf("----------\n");

	//loop over input
	for (c_index = 0; c_index < str_len; c_index++){
		if (buff[c_index] != ' ' && buff[c_index] != '\t'){
			if (word_start == -1){
				word_start = c_index;
			}
		}
		//inside word and print
		else if (word_start != -1) {
			printf("%d. ", word_index);
			for (int w = word_start; w < c_index; w++){
				putchar(buff[w]);
			}
			printf("(%d)\n", c_index-word_start);

			word_index++;
			word_start = -1;
		}
	}
	//print last word if doesn't end in space
	if (word_start != -1){
		printf("%d. ", word_index);
		for (int w = word_start; w < c_index; w++){
			putchar(buff[w]);
		}
		printf("(%d)\n", c_index-word_start);
	}
}
	

void replace_words(){
	printf("Not Implemented!");
}

int main(int argc, char *argv[]){

    char *buff;             //placehoder for the internal buffer
    char *input_string;     //holds the string provided by the user on cmd line
    char opt;               //used to capture user option from cmd line
    int  rc;                //used for return codes
    int  user_str_len;      //length of user supplied string

    //TODO:  #1. WHY IS THIS SAFE, aka what if arv[1] does not exist?
    //      PLACE A COMMENT BLOCK HERE EXPLAINING
 
    //      It will be handled by the argc function as this is an or statement
    //      Otherwise, no operation had been indicated or is done incorrectly
    if ((argc < 2) || (*argv[1] != '-')){
        usage(argv[0]);
        exit(1);
    }

    opt = (char)*(argv[1]+1);   //get the option flag

    //handle the help flag and then exit normally
    if (opt == 'h'){
        usage(argv[0]);
        exit(0);
    }

    //WE NOW WILL HANDLE THE REQUIRED OPERATIONS

    //TODO:  #2 Document the purpose of the if statement below
    //      PLACE A COMMENT BLOCK HERE EXPLAINING
 
    //This checks if the user has the program name, command-flag, or their input
    if (argc < 3){
        usage(argv[0]);
        exit(1);
    }

    input_string = argv[2]; //capture the user input string

    //TODO:  #3 Allocate space for the buffer using malloc and
    //          handle error if malloc fails by exiting with a 
    //          return code of 99
    // CODE GOES HERE FOR #3

    buff = (char *) malloc (BUFFER_SZ);

    if (buff == NULL){
	    printf("Problem\n");
	    exit(99); 
    }

    user_str_len = setup_buff(buff, input_string, BUFFER_SZ);     //see todos
    if (user_str_len < 0){
        printf("Error setting up buffer, error = %d", user_str_len);
        exit(2);
    }

    switch (opt){
        case 'c':
            rc = count_words(buff, user_str_len);  //you need to implement
            if (rc < 0){
                printf("Error counting words, rc = %d", rc);
                exit(2);
            }
            printf("Word Count: %d\n", rc); 
            break;

        //TODO:  #5 Implement the other cases for 'r' and 'w' by extending
        //       the case statement options
	
	case 'r':
	    reverse_string(buff, user_str_len);		
	    break;

	case 'w':
	    print_words(buff, user_str_len);
	    
	    printf("\n");

	    rc = count_words(buff, user_str_len);  //you need to implement
            if (rc < 0){
                printf("Error counting words, rc = %d", rc);
                exit(2);
            }
            printf("Number of words returned: %d\n", rc);
            break;
	
	case 'x':
	    replace_words(); 
	  exit(0);   

        default:
            usage(argv[0]);
            exit(1);
    }

    //TODO:  #6 Dont forget to free your buffer before exiting
    print_buff(buff,BUFFER_SZ);
    free(buff); 
    exit(0);
}

//TODO:  #7  Notice all of the helper functions provided in the 
//          starter take both the buffer as well as the length.  Why
//          do you think providing both the pointer and the length
//          is a good practice, after all we know from main() that 
//          the buff variable will have exactly 50 bytes?
//  
//          This could be because of future modification as the length argument 
//          would need to be utilized should the buff variable change, assuring it 
//          will still work correctly. 
