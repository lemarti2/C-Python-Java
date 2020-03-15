#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> 

//**

const long MAX_THREADS = 8;

// Accessible to all threads
long threadCount;  
int *A_array;
long N;
long testSum = 0;

void
getInput();

void
fillArray();

void
arrayCalc();

void
printUsage (const char* progName);

void*
sayHello (void* threadId);

//**

int
main (int argc, char* argv[]) 
{	
  getInput();
  A_array = malloc(sizeof(int)*N);
  fillArray();
  arrayCalc();
  if (threadCount <= 0 || threadCount > MAX_THREADS)
  {
    printUsage (argv[0]);
    exit (EXIT_FAILURE);
  }
  pthread_t* threads = malloc (threadCount * sizeof (pthread_t));
  
  for (long threadId = 0; threadId < threadCount; ++threadId)  
  {
    pthread_create (&threads[threadId], NULL,
		    sayHello, (void *) threadId);
  }
  
  long sum = 0;
  for (long threadId = 0; threadId < threadCount; ++threadId) 
  {
    void* returnVal;
    pthread_join (threads[threadId], &returnVal);
    sum+= (long)returnVal;
  }
  printf("ThreadSum = %ld\n", sum);
  printf("ActualSum = %ld\n", testSum);

  free (threads);
  
  pthread_exit (EXIT_SUCCESS);
}

//**

void
getInput()
{
	printf("P ==> ");
	scanf("%d", &threadCount);
	printf("N ==> ");
	scanf("%d", &N);
}

//**

void
fillArray()
{
  for(int i = 0; i < N; ++i)
  {
    A_array[i] = rand()%5;
  }
  /*for(int i = 0; i < N; ++i)
  {
    printf("%d ",A_array[i]);
  }*/
}

//**

void
arrayCalc()
{
	for(int i = 0; i < N; ++i)
	{
		testSum += A_array[i];
	}
}

//**

void*
sayHello (void* threadId) 
{
  long myId = (long) threadId;
  long calc = (long)N/threadCount;
  long sum = 0;
  for(long i = myId*calc; i < (myId*calc) + calc; ++i)
  {
   sum+=A_array[i];
  }

  return (void*)sum;
} 

//**

void
printUsage (const char* progName) 
{
  fprintf (stderr, "Usage: %s <number of threads>\n", progName);
  fprintf (stderr, "0 < number of threads <= %ld\n", MAX_THREADS);
}