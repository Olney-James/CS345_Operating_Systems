/***********************************************************************
* Component:
*    DISK SCHEDULING C-SCAN
* Author:
*    James Olney
* Summary:
*    This is the DERRIVED class to implement the C-SCAN algorithm
************************************************************************/
#ifndef DS_C_SCAN
#define DS_C_SCAN
#include "ds.h"   // for the DiskSchedulingAlgorithm base-class
using namespace std;

/****************************************************
 * C-SCAN
 * The C-SCAN disk scheduling algorithm
 ***************************************************/
class DiskSchedulingC_SCAN : public DiskSchedulingAlgorithm {
public:
   /*****************************************************
    * CONSTRUCTOR
    * initialize the data structures specific to C-SCAN
    *****************************************************/
   DiskSchedulingC_SCAN(const ScheduleProblem & problem) : DiskSchedulingAlgorithm(problem) {
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
      if (increasing) {
         while (after_it != requests.end()) {
            currentLocation = *after_it;
            record();
            after_it++;
         }
         if (before_it != before.end()) {
            currentLocation = getDiskSize() - 1;
            record();
            currentLocation = 0;
            record();
            before.sort();
            before_it = before.begin();
            while (before_it != before.end()) {
               currentLocation = *before_it;
               record();
               before_it++;
            }
         }
      } else {
         before_it = before.begin();
         while (before_it != before.end()) {
            currentLocation = *before_it;
            record();
            before_it++;
         }
         if (after_it != requests.end()) {
            currentLocation = 0;
            record();
            requests.reverse();
            before_it = requests.begin();
            while (*before_it != *after_it) {
               currentLocation = *before_it;
               record();
               before_it++;
            }
            currentLocation = *before_it;
            record();
         }
      }
   }

private:
   list <int> requests;
   bool increasing;
};

#endif // DS_C_SCAN