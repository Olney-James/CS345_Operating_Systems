/***********************************************************************
* Component:
*    Page Replacement Second Chance
* Author:
*    James Olney
* Summary: 
*    This is the DERRIVED class to implement Second
************************************************************************/

#ifndef PR_SECOND
#define PR_SECOND

#include "pr.h"   // for the PageReplacementAlgorithm base-class
#include <iostream>
using namespace std;

/****************************************************
 * Second Chance
 * The least-recently-used Approximation page replacement
 * algorithm known as Second Chance
 ***************************************************/
class PageReplacementSecond : public PageReplacementAlgorithm{
public:
   /*****************************************************
    * CONSTRUCTOR
    * initialize the data structures specific to Second
    *****************************************************/
   PageReplacementSecond(int numSlots) : PageReplacementAlgorithm(numSlots), index(0){
      referenceBit.resize(numSlots, false);
   }

   /****************************************************
    * RUN
    * Implement the LRU algorithm here. Thus function will get
    * called several times, each time requesting "pageNumber"
    * from memory. You are to assign that page to a "pageFrame"
    * and then call the base-class to record the results.
    ***************************************************/
   void run(int pageNumber){
      for (int x = 0; x < getNumSlots(); x++){
         if (pageFrame[x] == pageNumber){
            referenceBit[x] = true;
            PageReplacementAlgorithm::record(pageNumber, false);
            return;
         }
	  }
      while (referenceBit[index]){
        referenceBit[index] = false;
        index = (index + 1) % getNumSlots();
      }
      referenceBit[index] = true;
      pageFrame[index] = pageNumber;
      index = (index + 1) % getNumSlots();
      
      PageReplacementAlgorithm::record(pageNumber, true);
      return;
   }

private:
   std::vector <bool> referenceBit;
   int index;
};

#endif // PR_SECOND
