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
    "see fwrite/fread function in C" for storing data structure in a file 
    and choose your own extention format before writing/reading on disk neat! no ?
    ( !! only values must be set on a struct when you plane to store the structure in a config file !! )
    ( pointer would lead to segmentation fault in the next runtime. )  
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
	return funct(input);
};

   
/* 
  Function pointer is usefull for API internal standard
  when a programer wich to inject it's own code between fixed 
  api inputs / output.
*/
inline int generic_CodeA(int value){
	//...some possible additional code config there...
	return (value+3); 
};
/*
    -> prefix "inline" speed up short function definition 
       like the one above at compile time by replacing 
       long "memory jump" when function call by short asm instructions. 
       ( good notion to have... )
    -> but "broke" the storage of the data structure (with the C fwrite function),
       since only a memory address can be fix in size,
       consecutives inlined assembly instructions at compile time 
       would involve to store an undifined number of asm instructions in
       the data structure, the size would not be possible to know by advance
       at write time for an user config file. ( inportant to understand why... )
*/

int generic_CodeB(int value){
	//...some possible additional code config there...
	return (value+5); 
};

// Classic data structure.
struct data{
	double a1;
	double a2;
	char name[20];
	Callbck_t runtime_code; // this may be stupid, the memory adress point on something valid 
};                              // ONLY for this runtime meaning that if you attempt to read 
                                // the next time a file with this struct in another runtime 
                                // the memory adrress will not be valid anymore,
                                // since the os will allocate the stack/heap in another active 
                                // region of the sdram ... 
                                // i made this mistake ;{ a shame... but very instructive.
                                // But work well if you dont save the struct on a file.
                               

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
	printf("Data structure a2 value: %.2f\n",st.a2);	

 	printf("Code routine Handling\n"
	               "Result of code A ->%d\n"
	               "Result of code B ->%d\n",
	               interrupt_routine(generic_CodeA,10),
	               interrupt_routine(generic_CodeB,10));
	
	// Open a stream and save data structure on physical disk in an arbitrary '.jp' format.
	FILE* fd = fopen("./myfile.jp","w+b");
	if( fd == NULL ){
		fprintf(stderr,"Error,cant openfile there.");
                exit(EXIT_FAILURE);
		}
	fwrite(&st,sizeof(st),1,fd); // Write
	fclose(fd); // close stream.
        // Open the '.jp' file coresponding to the architecture of the data structure and run the stored struct data.
	//     ( possibly a one generated from another computer and recived by email in .jp format ... )
	fd = fopen("./myfile.jp","rb");
        if( fd == NULL ){
		fprintf(stderr,"Error while reading! "
			       ",a file was supposed to be there !");
                exit(EXIT_FAILURE);
		}
	struct data* st_read = calloc(sizeof(st));             // Structure definition on ram.
	fread(st_read,sizeof(st),1,fd);                        // Read from disk & store on ram.
	fclose(fd);                                            // close stream.
	printf("Data read from code previously stored in \"myfile.jp\" :%d\n",(st_read->runtime_code)(10)); //!! only valid for this runtime.
	free(st_read);                                         // free ram region from heap.
	return EXIT_SUCCESS;
}
