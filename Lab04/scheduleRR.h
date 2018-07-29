/***********************************************************************
 * Component:
 *    Scheduler RR
 * Author:
 *    James Olney
 * Summary:
 *    This is the base-class that enables various schedule algorithms
 *    to simulate CPU Scheduling
 ************************************************************************/

#ifndef SCHEDULER_RR
#define SCHEDULER_RR
#include <cassert>
#include <queue>
#include "schedule.h"
#include "process.h"
using namespace std;

/****************************************************
 * RR
 * The Round Robin scheduler
 ***************************************************/
class SchedulerRR : public Disbatcher
{
  public:
  SchedulerRR(int q) : Disbatcher(),
      timeQuantaDuration(q) {}

   // a new process has just been executed
   void startProcess(int pid)
   {
      readyQueue.push(pid);
   }

   // execute one clock cycle
   bool clock()
   {
      x = (x + 1) % timeQuantaDuration;

      // processing?
      bool processing = pidCurrent == PID_NONE || processes[pidCurrent].isDone(\
);
      // still processing?
      if (x == 0 || processing)
      {
         if (x == 0 && !processing)
         {
            readyQueue.push(pidCurrent);
         }
		// if ready queue size > 0
         // take front element
         // remove item from the ready queue
         // and put in pidCurrent.
         if (readyQueue.size())
         {
            pidCurrent = readyQueue.front();
            readyQueue.pop();
            assert(pidCurrent >= 0 && pidCurrent <= processes.size());
            x = 0;
         }
         // else set pidCurrent to none
         else
            pidCurrent = PID_NONE;
      }
      // call base-class
      return Disbatcher::clock();
   }
  private:
   int x;
   int timeQuantaDuration;
   std::queue <int> readyQueue;
};

#endif // SCHEDULE_RR

