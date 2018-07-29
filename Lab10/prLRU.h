/***********************************************************************
* Component:
*    Page Replacement LRU
* Author:
*    James Olney
* Summary: 
*    This is the DERRIVED class to implement LRU
************************************************************************/

#ifndef PR_LRU
#define PR_LRU

#include "pr.h"   // for the PageReplacementAlgorithm base-class
#include <list> 
#include <iostream>
using namespace std;

/****************************************************
 * SRL
 * The least-recently-used page replacement algorithm
 ***************************************************/
class PageReplacementLRU: public PageReplacementAlgorithm{
public:
   /*****************************************************
    * CONSTRUCTOR
    * initialize the data structures specific to LRU
    *****************************************************/
   PageReplacementLRU(int numSlots) : PageReplacementAlgorithm(numSlots){
      // Initialize the next indexes
      for(int x = 0; x < numSlots; ++x){
         leastRecentlyUsed.push_front(x);
      }
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
            leastRecentlyUsed.remove(x);
            leastRecentlyUsed.push_front(x);
            PageReplacementAlgorithm::record(pageNumber, false);
            return;
         }
	  }
      pageFrame[leastRecentlyUsed.back()] = pageNumber;
      leastRecentlyUsed.push_front(leastRecentlyUsed.back());
      leastRecentlyUsed.pop_back();
      
      PageReplacementAlgorithm::record(pageNumber, true);
      return;
   }

private:
    std::list<int> leastRecentlyUsed;
};

#endif // PR_LRU
