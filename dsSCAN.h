/***********************************************************************
* Component:
*    DISK SCHEDULING SCAN
* Author:
*    James Olney
* Summary:
*    This is the DERRIVED class to implement the SCAN algorithm
************************************************************************/

#ifndef DS_SCAN
#define DS_SCAN
#include "ds.h"   // for the DiskSchedulingAlgorithm base-class
using namespace std;

/****************************************************
 * SCAN
 * The SCAN (aka Elevator) disk scheduling algorithm
 ***************************************************/
class DiskSchedulingSCAN : public DiskSchedulingAlgorithm
{
public:
   /*****************************************************
    * CONSTRUCTOR
    * initialize the data structures specific to SCAN
    *****************************************************/
   DiskSchedulingSCAN(const ScheduleProblem & problem) : DiskSchedulingAlgorithm(problem) {
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
         if (before_it != before.end()) {
            currentLocation = getDiskSize() - 1;
            record();
            while (before_it != before.end()) {
               currentLocation = *before_it;
               record();
               before_it++;
            }
         }
      } else {
         while (before_it != before.end()) {
            currentLocation = *before_it;
            record();
            before_it++;
         }
         if (after_it != requests.end()) {
            currentLocation = 0;
            record();
            while (after_it != requests.end()) {
               currentLocation = *after_it;
               record();
               after_it++;
            }
         }
      }
   }
private:
   list <int> requests;
   bool increasing;
};
#endif // DS_SCAN



