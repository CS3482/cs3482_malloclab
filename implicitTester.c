/* 
 * This program is used to test the implicit lists code.
 * You need to modify the program so that it provides a
 * good test of first fit, best fit, and next fit.
 * This program has a very simple test of first fit to give
 * a demonstration of how to write it.  You need to write a  
 * better test that includes tests of next fit and best fit.
 */
#include <string.h>
#include <stdlib.h>
#include "mmImplicit.h"
#include "memlib.h"

void parseArgs(int argc, char * argv[]);
void addressCompare(void * correct, void * returned);
void usage();

/* 
 * After calling mem_init and mm_init, this program makes
 * a series of calls to mm_malloc, mm_free, and printBlocks
 * to see the results
 */
int main(int argc, char * argv[])
{
   void *bp1, *bp2, *bp3, *bp4;

   parseArgs(argc, argv);
   //don't delete these calls. You need these.
   mem_init();
   mm_init();
   
   //this is what the heap looks like before any mallocs
   printBlocks();

   //You can modify this however you like.  You want to come
   //up with an example of mallocs and frees so that the mallocs
   //will return different blocks depending upon
   //the placement strategy.
   //Your first set of mallocs should use almost the entire heap
   //(and no more). 
   //After you do a bunch of mallocs, free half of those blocks
   //so you'll have a free block between every two allocated blocks.
   //That's your setup.
   printf("Blocks after malloc(0x128), malloc(0x118), malloc(0x178)\n");
   bp1 = mm_malloc(0x128);
   bp2 = mm_malloc(0x118);
   bp3 = mm_malloc(0x178);
   printBlocks();
   mm_free(bp1);
   mm_free(bp3);
   printf("Blocks after free(0x%x), free(0x%x)\n",
          (unsigned int) bp1, (unsigned int) bp3);
   printBlocks();

   //After the setup, you should make two more calls to malloc.
   //That call will return a different value depending upon which
   //fitting strategy is used. Next fit should cause malloc to
   //return the free block at the end.
   printf("Blocks after malloc(0x38)\n");
   bp4 = mm_malloc(0x38);
   printBlocks();
   //firstfit will pick the very first free block that is big enough.
   //The one pointed to by bp1 is big enough.
   //Add tests like this to your code to check for correctness of
   //your placement strategy.  You'll have to figure out what
   //the first parameter is "by hand" ... studying the heap and
   //understanding how the placement strategy works
   if (whichfit == FIRSTFIT) addressCompare(bp1, bp4);

   //Now do one more call.  For this one, your setup should cause
   //nextfit to loop around to find a block.

   return 0;
}

/* 
 * addressCompare - Takes two addresses as input and compares them.
 *                  If the addresses don't match, an error message
 *                  is printed and the program is exited.
*/
void addressCompare(void * correct, void * returned)
{
   if (correct != returned) 
   {
      if (whichfit == FIRSTFIT) printf("First fit placement failed.\n");
      if (whichfit == NEXTFIT) printf("Next fit placement failed.\n");
      if (whichfit == BESTFIT) printf("Best fit placement failed.\n");
      printf("Should have picked: %x \n", (unsigned int) correct);
      printf("Instead chose: %x\n", (unsigned int) returned);
      exit(0);
   }
}

/*
 * parseArgs - Parses the command line arguments in order to set the 
 *             placement policy (first fit, next fit, or best fit).
 */
void parseArgs(int argc, char * argv[])
{
   if (argc > 2 && !strcmp(argv[1], "-w") && !strcmp(argv[2], "next"))
   {
      whichfit = NEXTFIT;
      printf("Implicit List Tester\n");
      printf("Using next fit placement strategy\n");
   } else if (argc > 2 && !strcmp(argv[1], "-w") && !strcmp(argv[2], "best"))
   {
      printf("Implicit List Tester\n");
      printf("Using best fit placement strategy\n");
      whichfit = BESTFIT;
   } else if (argc > 2 && !strcmp(argv[1], "-w") && !strcmp(argv[2], "first"))
   {
      printf("Implicit List Tester\n");
      printf("Using first fit placement strategy\n");
      whichfit = FIRSTFIT;
   } else if (argc != 1)
   {
      usage();
   }
}

/*
 * usage - prints usage information
 */
void usage()
{
   printf("Usage: implicitTester [-h | -w <fit>]\n");
   printf("       -w <fit> is first (default), next, or best\n"); 
   printf("       -h prints usage information\n");
   exit(0);
}

