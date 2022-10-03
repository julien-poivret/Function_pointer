#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
    Quick and simple fundammantal for advanced coding in C.
*/

/*
  This technic is a practical way to store user code variations in a data structure     
    possibly configured by a fonction for this effect and run by another one.      
  
  And so, c++ class, method and constructor can be conveniently substitued by 
    a simple prefix in the function name family at declaration.
    c is a powerfull language system but can do Application User Interface too.
 */

// A way to do Boolean in c.
typedef char bool; // ( take 8 bits, for readability...) 
#define true 1
#define false 0

// Definition of function pointer of type Callbck_t.
typedef int (*Callbck_t)(int);

/* 	   
           *take a function pointer, pointing on a:
	         int function_name(int value_name);
	   *in a shape of:
	         function_name , (int)
*/
int interrupt_routine(Callbck_t funct,int input){
	// here possible additional code config.
	return funct(input);
};

   
/* 
  Different codes to "inject" in the interrupt routine.
  
      -> prefix "inline" speed up short function definition 
         like the two following at compile time by reducing 
         long "memory jump" at function call.
	 
*/
inline int generic_CodeA(int value){
	return (value+3); 
};

inline int generic_CodeB(int value){
	return (value+5); 
};

// Classic data structure.
struct data{
	double a1;
	double a2;
	char name[20];
	Callbck_t runtime_code;
};

// Runtime.
int main(int argc,char* argv[]){
        struct data st ={.a2=3.141570};
	bool check = false;
	char test[10][5]={"Bonj","","Aure"};

	if(check == false ){
		write(1,"Pointer on Pointer:\n",20);
		printf("%s\n",(*(test+2)));             // Raw pointer
		printf("%s\n",test[2]);                 // Classic list
		printf("Char 1 and 2 of the third item: %c,%c\n",
		                          test[2][0],test[2][1]);// 2d list.
	}
	
	printf("Data structure value: %.2f\n",st.a2);	

 	printf("Code routine Handling\n"
	               "Result of code A ->%d\n"
	               "Result of code B ->%d\n",
	               interrupt_routine(generic_CodeA,10),
	               interrupt_routine(generic_CodeB,10));
	return EXIT_SUCCESS;
}
