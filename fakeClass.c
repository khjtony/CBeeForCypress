#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct {
	char name[10];
	int age;
	int (*grow)(myfakeClass*);
} myfakeClass;

int growUp(myfakeClass* this){
	this->age++;
	return this->age;
}



int main(){
	printf("this is test\n");
	myfakeClass LOL;
	strcpy(LOL.name,"LOL");
	printf("The name of object is: %s\n",LOL.name);
	LOL.age=10;
	printf("The age of this object is %d last year.\n",LOL.age);
	LOL.grow=&growUp;
	LOL.grow(&LOL);
	printf("The age of this object is %d last year.\n",LOL.age);
	return;
}