/***********************************************************************
* Component:
*    Page Replacement FIFO
* Author:
*    James Olney
* Summary: 
*    This is the DERRIVED class to implement the FIFO algorithm
************************************************************************/

#ifndef PR_FIFO
#define PR_FIFO

#include "pr.h"   // for the PageReplacementAlgorithm base-class
#include <iostream>
using namespace std;

/****************************************************
 * FIFO
 * The first-in, first-out page replacement algorithm
 ***************************************************/
class PageReplacementFIFO : public PageReplacementAlgorithm{
public:
   /*****************************************************
    * CONSTRUCTOR
    * initialize the data structures specific to FIFO
    *****************************************************/
   PageReplacementFIFO(int numSlots) : PageReplacementAlgorithm(numSlots), fifo(0){}

   /****************************************************
    * RUN
    * Implement the Basic algorithm here. Thus function will get
    * called several times, each time requesting "pageNumber"
    * from memory. You are to assign that page to a "pageFrame"
    * and then call the base-class to record the results.
    ***************************************************/
   void run(int pageNumber){
      for (int x = 0; x < getNumSlots(); x++){
         if (pageFrame[x] == pageNumber){
            PageReplacementAlgorithm::record(pageNumber, false);
            return;
         }
	  }
      pageFrame[fifo] = pageNumber;
      fifo = (fifo + 1);
	  fifo = fifo % getNumSlots();
      
      PageReplacementAlgorithm::record(pageNumber, true);
      return;
   }

private:
   int fifo;
};
#endif // PR_BASIC
