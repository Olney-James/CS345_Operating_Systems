/***********************************************************************
* Component:
*    Scheduler SRT
* Author:
*    James Olney
* Summary:
*    This is the base-class that enables various schedule algorithms
*    to simulate CPU Scheduling
************************************************************************/

#ifndef SCHEDULER_SRT
#define SCHEDULER_SRT
#include <cassert>
#include "schedule.h"

/****************************************************
 * SRT
 * The Shortest Remaining Time Scheduler
 ***************************************************/
class SchedulerSRT : public Disbatcher
{
public:
   SchedulerSRT() : Disbatcher() {}

   // a new process has just been executed
   void startProcess(int pid)
   {
      if (readyQueue.size()){
         bool largest = true;
         list<int>::iterator itrtr;
         for (itrtr = readyQueue.begin(); itrtr != readyQueue.end(); ++itrtr){
            if (processes[pid].getTimeLeft() < processes[*itrtr].getTimeLeft() \
&& largest){
               readyQueue.insert(itrtr,pid);
               largest = false;
            }
         }
         if (largest){
            readyQueue.push_back(pid);
         }
      }
      else{
         readyQueue.push_front(pid);
      }
      list<int>::iterator itrtr;
   }

   // execute one clock cycle
   bool clock()
 {
      if (pidCurrent == PID_NONE || processes[pidCurrent].isDone()){
         if (readyQueue.size()){
            pidCurrent = readyQueue.front();
            readyQueue.pop_front();
            assert(pidCurrent >= 0 && pidCurrent <= processes.size());
         }
         else{
            pidCurrent = PID_NONE;
         }
      }
      //if readyQueue has anything
      if (readyQueue.size()){
         if (processes[pidCurrent].getTimeLeft() > processes[readyQueue.front()\
].getTimeLeft()){
            bool largest = true;
            list<int>::iterator itrtr;
            for (itrtr = readyQueue.begin(); itrtr != readyQueue.end(); ++itrtr\
){
               if (processes[pidCurrent].getTimeLeft() < processes[*itrtr].getT\
imeLeft() && largest){
                  readyQueue.insert(itrtr,pidCurrent);
                  largest = false;
               }
            }
            if (largest){
               readyQueue.push_back(pidCurrent);
            }
            pidCurrent = readyQueue.front();
            readyQueue.pop_front();
         }
      }
      return Disbatcher::clock();
   }

  private:
   std::list<int> readyQueue;
};

#endif // SCHEDULE_SRT
