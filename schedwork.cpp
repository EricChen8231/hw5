#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
typedef std::vector<std::vector<bool>> AvailabilityMatrix;
typedef std::vector<std::vector<Worker_T>> DailySchedule;

// Add your implementation of schedule() and other helper functions here
bool search(const AvailabilityMatrix &avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule &sched, int currentDay, int currentWorker, int startWorkerIndex, vector<int> &shiftsCount)
{
    int numDays = static_cast<int>(avail.size());
    int numWorkers = static_cast<int>(avail[0].size());

    // Base case: If all days are scheduled
    if (currentDay >= numDays)
    {
        return true;
    }

    // Move to the next day
    if (currentWorker >= dailyNeed)
    {
        return search(avail, dailyNeed, maxShifts, sched, currentDay + 1, 0, 0, shiftsCount);
    }

    //  backtrack
    if (startWorkerIndex >= numWorkers)
    {
        return false;
    }

    // Start considering workers from startWorkerIndex
    for (int workerIndex = startWorkerIndex; workerIndex < numWorkers; workerIndex++)
    {
        if (avail[currentDay][workerIndex] && shiftsCount[workerIndex] <maxShifts)
        {

            shiftsCount[workerIndex] += 1;
            sched[currentDay][currentWorker] = workerIndex;

            // Explore further with the next worker and increment the worker count
            if (search(avail, dailyNeed, maxShifts, sched, currentDay, currentWorker + 1, workerIndex + 1, shiftsCount))
            {
                return true;
            }

            // Backtrack
            shiftsCount[workerIndex]--;
            sched[currentDay][currentWorker] += -1;
        }
    }

    // Continue with the next worker index
    return search(avail, dailyNeed, maxShifts, sched, currentDay, currentWorker, startWorkerIndex + 1, shiftsCount);
}

bool schedule(const AvailabilityMatrix &avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule &sched)
{
    // Check if the availability matrix is empty
    if (avail.empty())
    {
        return false;
    }

    // Initialize the schedule matrix and shift count 
    sched.clear();
    int numDays = static_cast<int>(avail.size());
    int numWorkers = static_cast<int>(avail[0].size());
    sched = vector<vector<Worker_T>>(numDays, vector<Worker_T>(dailyNeed, 0));
    vector<int> shiftsCount(numWorkers, 0);

    // Start the search from day 0 and worker 0
    return search(avail, dailyNeed, maxShifts, sched, 0, 0,0, shiftsCount);
}