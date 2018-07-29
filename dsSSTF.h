/***********************************************************************
* Component:
*    DISK SCHEDULING SSTF
* Author:
*    James Olney
* Summary:
*    This is the DERRIVED class to implement the SSTF algorithm
************************************************************************/

#ifndef DS_SSTF
#define DS_SSTF
#include "ds.h"   // for the DiskSchedulingAlgorithm base-class
using namespace std;

/****************************************************
 * SSTF
 * The Sortest-Seek-Time-First disk scheduling algorithm
 ***************************************************/
class DiskSchedulingSSTF : public DiskSchedulingAlgorithm {
public:
   /*****************************************************
    * CONSTRUCTOR
    * initialize the data structures specific to SSTF
    *****************************************************/
   DiskSchedulingSSTF(const ScheduleProblem & problem) :  DiskSchedulingAlgorithm(problem)  {
	  requests = problem.requests;
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
      list <int> greater_than;
	  list <int> less_than;
      list <int> :: iterator it;
      for (it = requests.begin(); it != requests.end(); ++it) {
         if (*it < currentLocation) {
            less_than.push_front(*it);
         } 
		 else {
            greater_than.push_front(*it);
         }
      }
      less_than.sort();
      greater_than.sort();
      list <int> :: reverse_iterator less_than_it = less_than.rbegin();
      list <int> :: iterator greater_than_it = greater_than.begin();

      while(less_than_it != less_than.rend() && greater_than_it != greater_than.end()) {
         int less_than_distance = currentLocation - *less_than_it;
         int greater_than_distance = *greater_than_it - currentLocation;
         if (less_than_distance < greater_than_distance) {
            currentLocation = *less_than_it;
            less_than_it++;
         } 
		 else {
            currentLocation = *greater_than_it;
            greater_than_it++;
         }
         record();
      }
      for (; less_than_it != less_than.rend(); less_than_it++) {
         currentLocation = *less_than_it;
         record();
      }
      for (; greater_than_it != greater_than.end(); greater_than_it++) {
         currentLocation = *greater_than_it;
         record();
      }
   }

private:
   list <int> requests;
};

#endif // DS_SSTF


