//FAYAZ KHAN

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

struct memory_region{
  size_t * start;
  size_t * end;
};

struct memory_region global_mem;
struct memory_region heap_mem;
struct memory_region stack_mem;

void walk_region_and_mark(void* start, void* end);

//how many ptrs into the heap we have
#define INDEX_SIZE 1000
void* heapindex[INDEX_SIZE];


//grabbing the address and size of the global memory region from proc 
void init_global_range(){
  char file[100];
  char * line=NULL;
  size_t n=0;
  size_t read_bytes=0;
  size_t start, end;

  sprintf(file, "/proc/%d/maps", getpid());
  FILE * mapfile  = fopen(file, "r");
  if (mapfile==NULL){
    perror("opening maps file failed\n");
    exit(-1);
  }

  int counter=0;
  while ((read_bytes = getline(&line, &n, mapfile)) != -1) {
    if (strstr(line, "hw4")!=NULL){
      ++counter;
      if (counter==3){
        sscanf(line, "%lx-%lx", &start, &end);
        global_mem.start=(size_t*)start;
        // with a regular address space, our globals spill over into the heap
        global_mem.end=malloc(256);
        free(global_mem.end);
      }
    }
    else if (read_bytes > 0 && counter==3) {
      if(strstr(line,"heap")==NULL) {
        // with a randomized address space, our globals spill over into an unnamed segment directly following the globals
        sscanf(line, "%lx-%lx", &start, &end);
        printf("found an extra segment, ending at %zx\n",end);						
        global_mem.end=(size_t*)end;
      }
      break;
    }
  }
  fclose(mapfile);
}


//marking related operations

int is_marked(size_t* chunk) {
  return ((*chunk) & 0x2) > 0;
}

void mark(size_t* chunk) {
  (*chunk)|=0x2;
}

void clear_mark(size_t* chunk) {
  (*chunk)&=(~0x2);
}

// chunk related operations

#define chunk_size(c)  ((*((size_t*)c))& ~(size_t)3 ) 
void* next_chunk(void* c) { 
  if(chunk_size(c) == 0) {
    printf("Panic, chunk is of zero size.\n");
  }
  if((c+chunk_size(c)) < sbrk(0))
    return ((void*)c+chunk_size(c));
  else 
    return 0;
}
int in_use(void *c) { 
  return (next_chunk(c) && ((*(size_t*)next_chunk(c)) & 1));
}


// index related operations


/*Below function is optional*/
#define IND_INTERVAL ((sbrk(0) - (void*)(heap_mem.start - 1)) / INDEX_SIZE)
void build_heap_index() {
  // TODO
}

/*
1. The first gc run should free every chunk in heap since after first round of allocations every pointer in global area is set to 0

    and nothing in heap can be reached.

2. Next gc run is performed after second round of allocations and in this run nothing should be freed because, even though

    9999 pointers in global region were wiped, pointer 10000 is still points to last chunk in heap and and all the rest of chunks

    are pointed to one another starting from last one to previous one, hence they are all reachable from root.

3. Now. Here comes the source of my confusion. In the next step in main, the remaining pointer to heap is wiped and gc

    is run again. This time, nothing is reachable from global region and everything in heap should be freed but... problem is,

    that the heap hasn't changed since previous gc run during which everything in the heap was marked as reachable.

*/

// the actual collection code
void sweep() 
{

  // TODO
	printf("\nTest Sweep\n");

	size_t *s = heap_mem.start - 1;

	while(s && s<(size_t*)sbrk(0))
	{
		printf("\nTest Sweep222\n");       		  
		size_t *temp_s= next_chunk(s); 
		if(!is_marked(s))
		{
			if(in_use(s))
			  free(s+1);
			/*
				you can only free the payload 
			*/
		}
		else
		{
			clear_mark(s);

			/*
				I orignially had next_chunk here but later moved to the
				top of the while loop
			*/	
		}
		
		s = temp_s;
		printf("\nTest Sweep333333\n");
	}
printf("\nTest Sweep4444444\n");
heap_mem.end=sbrk(0);
printf("\nTest Sweep555555555\n");
}

//determine if what "looks" like a pointer actually points to a block in the heap
size_t * is_pointer(size_t * ptr) {
  // TODO
	printf("\nTest is_pointer\n");
	/*
		the if statment is to determine if within the stack. 
		if it is not then return null.
	*/
	if(heap_mem.start<= ptr && ptr <= heap_mem.end)
	{

		size_t * s = heap_mem.start -1;
		while(s && s!= heap_mem.end)
		{
			if(s<= ptr && (size_t*)next_chunk(s)>ptr && in_use(s) )
				return s;	
			s = next_chunk(s);
		}
	
	}
	else
	{
	   return NULL;
	}
}


/*
A Mark&Sweep garbage collector consists of a mark phase, which marks all
reachable and allocated descendants of the root nodes, followed by a sweep phase,
which frees each unmarked allocated block. Typically, one of the spare low-order
bits in the block header is used to indicate whether a block is marked or not.
Our description of Mark&Sweep will assume the following functions, where
ptr is defined as typedef void *ptr
*/

void walk_region_and_mark(void* start, void* end) {
  // TODO
	size_t *s;

	printf("\nTest Walk and region\n");
	//Traversing through
	size_t * temp_s;
	for(temp_s = (size_t*)start; temp_s!= (size_t*)end;temp_s++ )
	{
		
		s = is_pointer(temp_s);
		if(s != NULL && !is_marked(s))
		{	
			mark(s);
			walk_region_and_mark(s+1,next_chunk(s));
		}
	}

}

// standard initialization 

void init_gc() {
  size_t stack_var;
  init_global_range();
  heap_mem.start=malloc(512);
  //since the heap grows down, the end is found first
  stack_mem.end=(size_t *)&stack_var;
}

void gc() {
  size_t stack_var;
  heap_mem.end=sbrk(0);
  //grows down, so start is a lower address
  stack_mem.start=(size_t *)&stack_var;

  // build the index that makes determining valid ptrs easier
  // implementing this smart function for collecting garbage can get bonus;
  // if you can't figure it out, just comment out this function.
  // walk_region_and_mark and sweep are enough for this project.
  build_heap_index();

  //walk memory regions
  walk_region_and_mark(global_mem.start,global_mem.end);
  walk_region_and_mark(stack_mem.start,stack_mem.end);
  sweep();
}
