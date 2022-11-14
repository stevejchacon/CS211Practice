// test.c: Test program for valgrind
#include <stdio.h>
#include <stdlib.h>

const int Size = 10;

void memoryLeak()
{
	int *intArray = (int *) malloc( sizeof( int) * Size);
	// Initialize the array with values
	for( int i=0; i < Size; i++) {
		intArray[ i] = i*2;
	}
	// Returning from function without freeing malloc space.
}

void doubleFree()
{
	// Allocate some memory and then free it twice.
  int *intTestArray = (int *) malloc( sizeof( int) * Size);
  free(intTestArray);
  free(intTestArray);
}

void useUninitializedMemory()
{
	// Allocate some memory and then use it before it is initialized.
  int *intArray2 = (int *) malloc( sizeof( int) * Size);
  int testVar;
  testVar = intArray2[1];
}

int *returnAddressOfLocalVariable()
{
	// Declare an integer variable, set it to some value, and
	// return its address.
    int x;
    x = 2;
    return &x;
}

void useReturnedAddressOfLocalVar()
{
	// Call the above function, to see if we can identify the
	  // call sequence that leads to the error.
  returnAdressOfLocalVariable();
}

int main()
{
	printf("Starting valgrind test program. \n");
	memoryLeak();
	doubleFree();
	useUninitializedMemory();
	useReturnedAddressOfLocalVar();

	printf("Done.\n");
	return 0;
}
