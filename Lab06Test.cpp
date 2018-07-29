/***********************************************************************                            
 * Program:                                                                                         
 *    Lab 06, Producer and Consumer                                                                 
 * Author:                                                                                          
 *    James Olney                                                                              
 * Summary:                                                                                         
 *    This program will allow us to simulate the production run                                     
 *    at McLaren Cars. It would be cool if it simulated the cars                                    
 *    themselves, but that might be an assignment for another day                                   
 *                                                                                                  
 *    Note that you must compile this with the -lpthread switch:                                    
 *        g++ -lpthread lab06.cpp                                                                   
 ************************************************************************/
#include <iostream>      // for COUT                                                                
#include <cassert>       // for ASSERT                                                              
#include <string>        // for STRING                                                              
#include <sstream>       // for STRINGSTREAM                                                        
#include <queue>         // for QUEUE                                                               
#include <ctime>         // for time(), part of the random process                                  
#include <unistd.h>      // for usleep()                                                            
#include <stdlib.h>      // for rand() and srand()                                                  
#include "cars.h"        // for everything dealing with McLaren Cars                                
#include <semaphore.h>
using namespace std;

// This variable represents the shared memory between the parent thread                             
// and all the children. Recall from the reading how the main way for                               
// threads to communicate is through shared memory. This shared memory                              
// needs to be global.                                                                              
bool productionComplete = false;
Inventory inventory;
pthread_mutex_t myLock;
sem_t mySemaphore;

void * producer(void * p);                                     
void * consumer(void * p);                                       
int getNumber(const char * prompt, int max);

/***********************************************                                                    
 * MAIN                                                                                             
 * This will serve to prompt the user for the number                                                
 * of models and the number of retailers. It will then                                              
 * begin the simulation                                                                             
 ***********************************************/
int main(int argc, char **argv){
   // set up the random number generator                                                            
   srand(argc == 1 ? time(NULL) : (int)argv[1][1]);

   // determine how many producer and consumer threads     
   int numProducer = getNumber("How many models?    ", numModels());
   int numConsumer = getNumber("How many retailers? ", numRetailers());

   // produce the cars.                                 
   // launch one thread per producer here                                                   
   pthread_t producers[numProducer];
   int produced;
   pthread_t consumers[numConsumer];
   int consumed;
   pthread_mutex_init(&myLock, NULL);
   sem_init(&mySemaphore, 0, 6);
   Inventory inventory;
   for (int x = 0; x < numProducer; x++){
      produced = pthread_create(&producers[x], 
                            NULL,
                            producer,
                            (void*) models[x]);
   }

   for (int x = 0; x < numConsumer; x++){
      consumed = pthread_create(&consumers[x],
                           NULL,
                           consumer,
                           (void *) retailers[x]);
   }
   for (int x = 0; x < numProducer; x++){
      pthread_join(producers[x], NULL);
   }
      // sell the cars.                                      
   cout << "\nThe cars sold from the various retailers:\n\n";
   for (int x = 0; x < numConsumer; x++){
      void * p;
      pthread_join(consumers[x], &p);
      string * pResults = (string *)p;
      cout << *(string *)pResults << endl;
      delete (string *)pResults;
   }
   // final report                                                                                  
   cout << "Maximum size of the inventory: " << inventory.getMax() << endl;
   return 0;
}

/***********************************************************                                        
 * PRODUCER                                                                                         
 * Create those cars.                                                                               
 * This function is not currently thread safe.                                         
 * Introduced a critical section in such a way that we do                                         
 * not compromise the queue nor produce two cars with the                                           
 * same serial number.                                                                              
 **********************************************************/
void* producer(void* p){
   static int serialNumberNext = 0;

   // a car to be added to the inventory
   Car car;
   car.model = (const char *)p;
   // continue as long as we still need to produce cars in this run                                 
   while (serialNumberNext < NUM_CARS){
      // now that we decided to build a car, it takes some time                                     
      usleep(rand() % 150000);
      sem_wait(&mySemaphore);
      pthread_mutex_lock(&myLock);
      // add the car to our inventory if we still need to                                           
      if (serialNumberNext < NUM_CARS){
         car.serialNumber = ++serialNumberNext;
         inventory.makeCar(car);
      }
      pthread_mutex_unlock(&myLock);
   }
   // all done!                                                                                     
   productionComplete = true;
}

/***********************************************************                                        
 * CONSUMER                                                                                         
 * Sell those cars.                                                                                 
 * This function is not currently thread safe.                                         
 * Critical section is introduced in such a way that we                                            
 * do not compromise the queue nor sell the same car twice.                                         
 **********************************************************/
void* consumer(void* p){
   const char * retailer = (const char *)p;
   // collect our sales history into one string                                                     
   stringstream sout;
   sout << retailer << ":\n";
   // continue while there are still customers floating around                                      
   while (!(productionComplete && inventory.empty())){
      // the car to sell                                                                            
      Car car;

      // it takes time to sell our car 
      usleep(rand() % 150000);
      pthread_mutex_lock(&myLock);

      // do we have one to sell                                                                     
      if (!inventory.empty()){
         car = inventory.sellCar();
         pthread_mutex_unlock(&myLock);
         sem_post(&mySemaphore);
         sout << "\t" << car << endl;
      }
      else{
         pthread_mutex_unlock(&myLock);
	  }
   }
   // done                                                                                          
   string * report = new string(sout.str());
   return (void *) report;
}

/*********************************************                                                      
 * GET NUMBER                                                                                       
 * Generic prompt function with error checking                                                      
 ********************************************/
int getNumber(const char * prompt, int max){
   int value = -1;
   assert(cin.good());       // better not already be in error mode                                 
   assert(prompt != NULL);   // the prompt better be a valid c-string                               
   assert(max > 0);          // it better be possible for valid data to exist                       
   // continue prompting until we have valid data                                                   
   while (value <= 0 || value > max){
      cout << prompt;
      cin  >> value;
      // if the user typed a non-integer value, reprompt.                                           
      if (cin.fail()){
         cin.clear();
         cin.ignore();
         cout << "Error: non-integer value specified\n";
      }
      // if the user typed a valid outside the range, reprompt                                      
      else if (value <= 0 || value > max)
         cout << "Error: value must be between 1 and "
              << max
              << endl;
   }
   return value;
}