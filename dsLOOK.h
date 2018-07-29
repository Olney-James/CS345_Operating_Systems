/***********************************************************************
* Component:
*    DISK SCHEDULING LOOK
* Author:
*    James Olney
* Summary:
*    This is the DERRIVED class to implement the LOOK algorithm
************************************************************************/

#ifndef DS_LOOK
#define DS_LOOK
#include "ds.h"   // for the DiskSchedulingAlgorithm base-class
using namespace std;

/****************************************************
 * SCAN
 * The LOOK (SCAN with lookahead) disk scheduling algorithm
 ***************************************************/
class DiskSchedulingLOOK : public DiskSchedulingAlgorithm {
public:
   /*****************************************************
    * CONSTRUCTOR
    * initialize the data structures specific to SCAN
    *****************************************************/
   DiskSchedulingLOOK(const ScheduleProblem & problem) : DiskSchedulingAlgorithm(problem) {
	  requests = problem.requests;
      increasing = problem.increasing;
   }

   /****************************************************
    * RUN
    * Implement the algorithm here. This function will only
    * be called once and will need to complete the entire
    * simulation.
    *
    * Each time a disk request is made by setting currentLocation,
    * call record() to save that.
    ***************************************************/
   void run() {
      requests.sort();
      list <int> before;
      list <int>::iterator before_it;
	  list <int>::iterator after_it;
      for(after_it = requests.begin(); after_it != requests.end() && *after_it < currentLocation; ++after_it) {
         before.push_front(*after_it);
      }
      before_it = before.begin();
      if (increasing) {
         while (after_it != requests.end()) {
            currentLocation = *after_it;
            record();
            after_it++;
         }
      }
      while (before_it != before.end()) {
         currentLocation = *before_it;
         record();
         before_it++;
      }
      while (after_it != requests.end()) {
         currentLocation = *after_it;
         record();
         after_it++;
      }
   }

private:
   list <int> requests;
   bool increasing;
};

#endif // DS_LOOK
