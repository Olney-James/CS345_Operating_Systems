/***********************************************************************
* Component:
*    Scheduler SJF
* Author:
*    James Olney
* Summary:
*    This is the base-class that enables various schedule algorithms
*    to simulate CPU Scheduling
************************************************************************/
#ifndef SCHEDULER_SJF
#define SCHEDULER_SJF
#include <cassert>
#include "schedule.h"

/****************************************************
 * SJF
 * The Shortest Job First scheduler
 ***************************************************/
class SchedulerSJF : public Disbatcher
{
public:
   SchedulerSJF() : Disbatcher() {}

   //execute process
   void startProcess(int pid)
   {
      //if there's anything in the ready queue
      if (readyQueue.size()){
         bool biggest = true;
         list<int>::iterator it;
         for (it = readyQueue.begin(); it != readyQueue.end(); ++it){
            if (processes[pid].getServiceTime() < processes[*it].getServiceTime\
() && biggest){
               readyQueue.insert(it,pid);
               biggest = false;
            }
         }
         if (biggest){
            readyQueue.push_back(pid);
         }
      }
      else
         readyQueue.push_front(pid);
      list<int>::iterator it;
   }
   // execute one clock cycle
   bool clock()
   {
      //if current finished? or there is no current?

      if (pidCurrent == PID_NONE || processes[pidCurrent].isDone()){
         //if readyQueue not empty
         if (readyQueue.size()){
            pidCurrent = readyQueue.front();
            readyQueue.pop_front();
            assert(pidCurrent >= 0 && pidCurrent <= processes.size());
         }
         else{
            pidCurrent = PID_NONE;
         }
      }
      return Disbatcher::clock();
   }

private:
   std::list<int> readyQueue;
};

#endif // SCHEDULE_SJF
