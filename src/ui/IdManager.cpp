////////////////////////////////////////////////////////////////////////////////
//
// File: IdManager.cpp
//
// Author: Raynard Brown
//
// Copyright (c) 2019 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include "ui/private/IdManager.h"

IdManager::IdManager(int minV, int maxV)
:minV(minV),
 maxV(maxV),
 currentPosition(0),
 endPosition(0),
 maxSlots(0),
 usedSlots(0)
{
  maxSlots = (maxV - minV) + 1;
  usedSlots = 0;
  currentPosition = minV;
  endPosition = maxSlots;
}

IdManager::~IdManager()
{
}

int IdManager::requestId()
{
  if(!returnedIds.empty())
  {
    ++usedSlots;

    int returnedId = returnedIds.front();
    returnedIds.pop();

    return returnedId;
  }

  if(maxSlots == usedSlots)
  {
    // out of ids
    return -1;
  }

  int nextId = currentPosition;

  ++usedSlots;
  ++currentPosition;

  return nextId;
}

void IdManager::returnId(int id)
{
  // ensure there are actually ids in use
  if(usedSlots > 0)
  {
    // ensure id is within the range
    if(id >= minV && id <= maxV)
    {
      // ensure the id is _NOT_ an id that has _NOT_ been requested (i.e. an id in the not yet requested range)
      if(!(id >= currentPosition && id < endPosition))
      {
        // check if we can avoid adding the reclaimed id back to the queue
        // we'd like to just adjust the current pointer instead
        // we can do this by checking if the reclaimed id is adjacent to the
        // current pointer
        if((id + 1) == currentPosition)
        {
          // decrement the used slots
          --usedSlots;

          // adjust the current pointer
          --currentPosition;
        }
        else
        {
          // decrement the used slots
          --usedSlots;

          // reclaim the id
          returnedIds.push(id);
        }
      }
    }
  }
}
