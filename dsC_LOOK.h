/***********************************************************************
* Component:
*    DISK SCHEDULING C-LOOK
* Author:
*    James Olney
* Summary:
*    This is the DERRIVED class to implement the C-LOOK algorithm
************************************************************************/

#ifndef DS_C_LOOK
#define DS_C_LOOK
#include "ds.h"   // for the DiskSchedulingAlgorithm base-class
using namespace std;

/****************************************************
 * C-LOOK
 * The C-LOOK disk scheduling algorithm
 ***************************************************/
class DiskSchedulingC_LOOK : public DiskSchedulingAlgorithm {
public:
   /*****************************************************
    * CONSTRUCTOR
    * initialize the data structures specific to C-LOOK
    *****************************************************/
   DiskSchedulingC_LOOK(const ScheduleProblem & problem) :  DiskSchedulingAlgorithm(problem) {
	  requests = problem.requests;
      increasing = problem.increasing;
   }

   /****************************************************
    * RUN
    * Implement the algorithm here. This function will only
    * be called once and will need to complete the entire
    * simulation. With file location, send the results to record().
    ***************************************************/
   void run() {
	  requests.sort();
      list <int> before;
      list <int>::iterator before_it;
	  list <int> after;
      list <int>::iterator after_it;
	  
      for(after_it = requests.begin(); after_it != requests.end() && *after_it < currentLocation; ++after_it) {
         before.push_front(*after_it);
      }
      for(;after_it != requests.end(); ++after_it) {
         after.push_front(*after_it);
      }
      // Before & after in reverse order
      if (increasing) {
         after.sort();
         before.sort();
         before_it = before.begin();
         after_it = after.begin();
         while (after_it != after.end()) {
            currentLocation = *after_it;
            record();
            after_it++;
         }
         while (before_it != before.end()) {
            currentLocation = *before_it;
            record();
            before_it++;
         }
      } else {
         before_it = before.begin();
         after_it = after.begin();
         while (before_it != before.end()) {
            currentLocation = *before_it;
            record();
            before_it++;
         }
         while (after_it != after.end()) {
            currentLocation = *after_it;
            record();
            after_it++;
         }
      }
   }

private:
   list <int> requests;
   bool increasing;
};

#endif // DS_C_LOOK