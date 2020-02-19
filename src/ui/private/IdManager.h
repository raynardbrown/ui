////////////////////////////////////////////////////////////////////////////////
//
// File: IdManager.h
//
// Author: Raynard Brown
//
// Copyright (c) 2019 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef IDMANAGER_H_
#define IDMANAGER_H_

#include <queue>

class IdManager
{
  public:

    IdManager(int minV, int maxV);

    ~IdManager();

    /**
     * Request an unused identifier from this IdManager given range of the min
     * and max values specified in the constructor.
     *
     * @return an id in the range of min and max (inclusive) if there is an id
     * available or -1 if the number of available ids given the range of min and
     * max have been exhausted.
     */
    int requestId();

    /**
     * Return the specified id back to this IdManager for reuse.
     *
     * @param id the id that will be returned to this IdManager.
     */
    void returnId(int id);

  private:

    int minV;
    int maxV;

    int currentPosition;
    int endPosition;
    int maxSlots;
    int usedSlots;

    std::queue<int> returnedIds;
};
#endif /* IDMANAGER_H_ */
