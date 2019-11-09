#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
void modify_cat(Cat *c);
void print_cat(Cat *c);
void print_cat_list(Cat *cats);
void add_cats(Cat *cats, int n);
void add_cat(Cat *cats);
void delete_cat(Cat *cats, char *c_name);

int main(){

	//cats = create_cats(10);
        cats = create_cat();
	modify_cat(cats);
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
			printf("Cat(s) added!\n\n");
		break;
		
		case DELETE:
			printf("Enter the name of the cat to delete. > ");
			fgets(user_input, BUFFER, stdin);
			delete_cat(cats, user_input);
			printf("%s removed!", user_input);
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


void modify_cat(Cat *c){
	int name_len;
	printf("What would you like to name this cat? > ");
	// fgets() is going to take in the \n character when you enter the string.
	// Need a way to parse it out.
	fgets(user_input, BUFFER, stdin);
	name_len = strlen(user_input);
	
	// I feel like this is a hacky way to do it but it works.
	//printf("Value of name_len: %d\n", name_len);
	//printf("Last char in name: %c\n", user_input[name_len-1]);
        user_input[name_len-1] = '\0';
	strcpy(c->name, user_input);

        //Interesting side effect of the user entering their name is that the new line
	//that they type to enter the name moves us onto the next line and so i don't
	//need to explicitly write it in at the beginning of this statement.
	printf("How old is this cat? > ");
        fgets(user_input, BUFFER, stdin);
	c->age = atoi(user_input);
	printf("What sound does %s make? > ", c->name);
        fgets(c->sound, BUFFER, stdin);

}

// I think there's a \n somewhere that's causing this function not to work with "default"
// The user putting values in and then hitting enter is causing a newline to go in.
// It's happening so often i might write a function just to clean out those \n, they are so annoying.
// It's what's causing this function to fail 
void delete_cat(Cat *cat, char *c_name){
	printf("In delete function, here's given name: %s\n", c_name);
	int i=0;
	Cat *prev_cat;
	while (cat != NULL){
		printf("looking for: %s, given name: %s\n", cat->name, c_name);
		if  (cat->name == c_name){
			// if its the first node, then make the beginning of the list
			// the cat that this one points to. (cat->next)
			if (i==0){
				cat = cat->next; // is that it?
				printf("Deleted a cat at the beginning\n");
				return;	
			}	
			// if its the last node, then make the previous cats ptr NULL
			else if (cat->next == NULL){
				prev_cat->next = NULL;
				printf("Deleted a cat at the end\n");
				return;
			}
			// if its not one of the previous two, make the pointer from
			// the previous cat point to the cat saved in the current cat's c->next.
			else{
				prev_cat->next = cat->next;
				printf("Deleted a cat in the middle\n");
				return;	
			}
		}
		else{
			// what to do if this isn't the cat you're looking for
			prev_cat = cat;
			cat = cat->next;
			i++;
		}
		// printf("Didn't find a cat by that name\n");
	}
	printf("Didn't find a cat by that name\n");
}

// need to modify this function forcing people to make a cat with a name.
// like we need to call a modify cat function immediately after this to have a
// cat that is not just the default.
Cat *create_cat(){
	Cat *to_return = calloc(1,sizeof(Cat));

	snprintf(to_return->name,BUFFER, "default"); // I think this is inserting a \n messing up my search
	

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
