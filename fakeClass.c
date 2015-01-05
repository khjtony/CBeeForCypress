#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int _get_char_len(char* msg){
	int i=0;
	while (msg[i]!='\0'){
		i++;
	}
	return i;
}

typedef struct fakeClass_t{
	char name[10];
	int age;
	char* content;
	int (*grow)(struct fakeClass_t*);
	void (*_append_content)(struct fakeClass_t*,char*);
} fakeClass;

int growUp(struct fakeClass_t* this){
	this->age++;
	return this->age;
}

void append_content(struct fakeClass_t* this, char* msg){
	int old_len=0;
	int msg_len=_get_char_len(msg);
	int new_len=0;
	int i=0;
	char* temp;
	// printf("msg_len is: %d\n",msg_len);
	if (this->content==NULL){
		// printf("This is null now\n");
		// this->content=(char*)malloc(sizeof(char)*new_len);
		this->content=msg;
	}else{
		old_len=_get_char_len(this->content);
		new_len=old_len+msg_len+1;
		temp=(char*)malloc(sizeof(char)*(new_len));
		// printf("new_len is: %d\n",new_len);
		for(i=0;i<old_len;i++){
			temp[i]=this->content[i];
		}
		// printf("Now the content is: %s\n",temp);
		for (i=0;i<msg_len;i++){
			temp[i+old_len]=msg[i];
		}
		this->content=temp;
		temp=NULL;
	}
	return;
}

void _fakeClass_init(struct fakeClass_t* this){
	this->content=NULL;
	this->grow=&growUp;
	this->_append_content=append_content;
	return;
}



int main(){
	printf("this is test\n");
	fakeClass LOL;
	_fakeClass_init(&LOL);
	printf("After init, LOL->content: %s\n",LOL.content);
	LOL._append_content(&LOL,"LOL");
	printf("After append LOL, LOL->content: %s\n",LOL.content);
	LOL._append_content(&LOL,"WOW");
	printf("After append WOW, LOL->content: %s\n",LOL.content);
	printf("The whole len is: %d\n", _get_char_len(LOL.content));
	return;
}