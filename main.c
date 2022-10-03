#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Poivret Julien Oct 3 2022 poivretjulien@gmail.com


/*
  
              Quick and simple fundammantal for advanced coding in C. 
    
  This technic is a practical way to store user code variations in a data structure     
    possibly configured by a fonction for this effect and run by another one.      
  
  And so, c++ class, method and constructor can be conveniently substitued by 
    a simple prefix in the function name family at declaration.
    C is a powerfull language system but can also do Application User Interface too.
    -> now a function pointer can take variations of algorithm, by having a different code 
    within a given input/output function entry format, this could be a system file ! 
    "see fwrite function in C" for storing data structure in a file 
    and choose your own extention format before writing/reading on disk neat! no ?
 */

// A way to do Boolean in c.
typedef char bool; // ( take 8 bits, for readability...) 
#define true 1
#define false 0

// Definition of function pointer discribe by an arbitrary type: Callbck_t.
typedef int (*Callbck_t)(int);

/* 	   

   *take a function pointer, pointing on a:

                 int function_name(int value_name);
   
   *in a shape of:
	         
		 function_name , (int)

*/
int interrupt_routine(Callbck_t funct,int input){
	//...some possible additional code config there...
	return funct(input);
};

   
/* 
  Different codes to "inject" in the interrupt routine.
  
      -> prefix "inline" speed up short function definition 
         like the one following at compile time by reducing 
         long "memory jump" when function call. (good notion to have...)
      -> but "broke" the storage in data structure !
	 
*/
inline int generic_CodeA(int value){
	return (value+3); 
};

int generic_CodeB(int value){
	return (value+5); 
};

// Classic data structure.
struct data{
	double a1;
	double a2;
	char name[20];
	Callbck_t runtime_code;
};

// Classic main function entry.
int main(int argc,char* argv[]){
	
	// Data structure initialization.
        struct data st ={.a2=3.141590};
	st.runtime_code = generic_CodeB; // Code storage. 
	
	// In "file Made" boolean ( from above typedef ).
	bool check = false;
	
	// 2d list ( or pointer* on pointer* ).
	char test[3][5]={"Bonj","","Aure"};
	
        // Code for walking the 2d list normal and "raw way".
	if(check == false ){
		write(1,"Pointer on Pointer:\n",20);
		printf("Raw way: %s\n",(*(test+2)));                // Raw pointer
		printf("Classic way: %s\n",test[2]);                // Classic list
		printf("Char 1 and 2 of the third item: %c,%c\n",
		                          test[2][0],test[2][1]);   // 2d list.
	}
	// Walking the data structure with the previously embedded code:
	printf("Data structure value: %.2f\n",st.a2);	

 	printf("Code routine Handling\n"
	               "Result of code A ->%d\n"
	               "Result of code B ->%d\n",
	               interrupt_routine(generic_CodeA,10),
	               interrupt_routine(generic_CodeB,10));
	
	// Open a stream and save data structure on physical disk in an arbitrary '.jp' format.
	FILE* fd = fopen("./myfile.jp","w+");
	if( fd == NULL ){
		fprintf(stderr,"Error,cant openfile there.");
                exit(EXIT_FAILURE);
		}
	fwrite(&st,sizeof(st),1,fd); // Write
	fclose(fd); 
        // Open the '.jp' file coresponding to the architecture of the data structure and run the stored code.
	//     ( possibly a one generated from another computer and recived by email in .jp format ... )
	fd = fopen("./myfile.jp","r");
        if( fd == NULL ){
		fprintf(stderr,"Error while reading! "
			       ",a file was supposed to be there !");
                exit(EXIT_FAILURE);
		}
	struct data st_read;
	fread(&st_read,sizeof(st),1,fd); // Read
	fclose(fd); 
	printf("Data read from code previously stored in \"myfile.jp\" :%d\n",(st_read.runtime_code)(10));
	
	return EXIT_SUCCESS;
}
