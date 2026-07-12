#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(){
	FILE *file;
	int i, n=32;
	char ch, arr[10];
	char *keywords[] = {
		"auto" , "break", "case", "char", "const", "continue", "default", "do", "double",
		"else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return",
		"short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned",
		"void", "volatile", "while"
	};

	int operators[256] = {0};
	int seperators[256] = {0};

	operators['+'] = 1;
	operators['-'] = 1;
	operators['*'] = 1;
	operators['/'] = 1;
	operators['='] = 1;

	seperators[' '] = 1;
    seperators['\t'] = 1;
    seperators['\n'] = 1;
    seperators[';'] = 1;
    seperators['('] = 1;
    seperators[')'] = 1;
    seperators['{'] = 1;
    seperators['}'] = 1;
    seperators['['] = 1;
    seperators[']'] = 1;
    seperators[','] = 1;


	int isOperator(char ch){
        	return operators[(unsigned char) ch];
	}

	int isSeperator(char ch){
        	return seperators[(unsigned char) ch];
	}

	int isKeyword(char word[], int num){
        	int i;
		for(i=0;i<num;i++){
                	if(strcmp(word,keywords[i]) == 0){
                        	return 1;
                	}
        	}

		return 0;
	}


	//Open file
	file = fopen("input.c","r");
	if(!file){
		printf("Error opening file!");
		return 1;
	}

	printf("Tokens Found : ");

	while((ch = fgetc(file)) != EOF){

		if(isOperator(ch)){
			printf("<Operator,%c>\n",ch);
		} else if(isSeperator(ch)){
			printf("<Seperator,%c>\n",ch);
		} else if(isdigit(ch)){
			i = 0;
			arr[i++] = ch;

			while(isdigit(ch = fgetc(file))){
				arr[i++] = ch;
			}

			ungetc(ch,file);
			arr[i] = '\0';
			printf("<Number,%s>\n",arr);

		} else if(isalpha(ch)){
			i = 0;
            arr[i++] = ch;

            while(isalnum(ch = fgetc(file))){
                    arr[i++] = ch;
            }

            ungetc(ch,file);
            arr[i] = '\0';

			if(isKeyword(arr,n) == 1){
				printf("<Keyword,%s>\n",arr);
			} else {
				printf("<Identifier,%s>\n",arr);
			}

		}

	}

	fclose(file);
	return 0;

}
