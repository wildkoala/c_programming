#include<stdio.h>
#include<stdlib.h>

#define BUFFER 200

enum OPTIONS{
	NULL_OPT,
	ADD,
	SELECT,
	DELETE,
	EDIT,
	PRINT
};

typedef struct cat_tag{
	char name[BUFFER];
	int age;
	char sound[BUFFER];
	struct cat_tag *next;
} Cat;

Cat *cats;
char cat_selected[BUFFER];
char user_input[BUFFER];

void loop();
void prompt_input();
void handle(int c);

Cat *create_cat();
Cat *create_cats(int n);
void print_cat(Cat *c);
void print_cat_list(Cat *cats);
void add_cats(Cat *cats, int n);
void add_cat(Cat *cats);


int main(){

	cats = create_cats(10);

	print_cat_list(cats);

	while(1){
		loop();
	}


	return 0;
}

void loop(){
	prompt_input();
	
	fgets(user_input,BUFFER,stdin);

	handle(atoi(user_input));
}

void prompt_input(){

	const char* options = "\
Options:\n\
1) add cat\n\
2) select cat\n\
3) delete cat\n\
4) edit cat\n\
5) print cats\n\n\
Cat Selected: %s\n\
What would you like to do? > ";

	printf(options,cat_selected);

}

void handle(int c){

	switch(c){
		case ADD:
			printf("How many? > ");
			fgets(user_input,BUFFER,stdin);
			add_cats(cats,atoi(user_input));
			printf("Cat added!\n\n");
		break;
		case PRINT:
			print_cat_list(cats);
		break;
		default:
			printf("ERROR! Input Invalid!\n");
		break;
	}
}

void print_cat(Cat *c){

	const char* format = "<cat>\tname:\t%s\t\tage:\t%d\t\tsound:\t%s\n";

	printf(format,c->name,c->age,c->sound);

}

void print_cat_list(Cat *cats){

	Cat *c = cats;

	int i = 0;
	while(c!=NULL){
		printf("%d: ", i);
		print_cat(c);
		c = c->next;
		i++;
	}
}

void add_cats(Cat *cats, int n){

	int i;
	for (i=0; i<n;i++){
		add_cat(cats);
	}
}

void add_cat(Cat *cats){

	Cat *c = cats;

	while(c->next!=NULL){
		c = c->next;
	}

	c->next = create_cat();
}



Cat *create_cat(){
	Cat *to_return = calloc(1,sizeof(Cat));

	snprintf(to_return->name,BUFFER,"default");
	to_return->age = 0;
	snprintf(to_return->sound,BUFFER,"meow");
	
	to_return->next = NULL;

	return to_return;
}

Cat *create_cats(int n){
	Cat *to_return = create_cat();

	add_cats(to_return,n-1);

	return to_return;
}
