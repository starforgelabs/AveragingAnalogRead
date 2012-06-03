/*
 *  AveragingAnalogRead.cpp
 *  Sun Tracker
 *
 *  Created by 治永夢守 on 12/05/27.
 *  Copyright 2012 James Knowles. All rights reserved.
 *
 * This work is licensed under a Creative Commons 
 * Attribution-ShareAlike 3.0 Unported License.
 *
 * https://creativecommons.org/licenses/by-sa/3.0/
 *
 *
 */

#include "AveragingAnalogRead.h"
#include <math.h>


AveragingAnalogRead::AveragingAnalogRead()
{
  BaseAnalogRead::BaseAnalogRead();

  Init(MAX_BUFFER_BITS);
}

void AveragingAnalogRead::AddToBuffer(int aValue)
{
  _Total -= _Buffer[_Head];
  _Buffer[_Head] = aValue;
  _Total += aValue;

  _Head = (_Head+1) % _BufferSize;

  if(_Count < _BufferSize)
    _Count++;
}

unsigned int AveragingAnalogRead::BufferSize()
{
  return _BufferSize;
}

int AveragingAnalogRead::CalculateAverage()
{
  if(_Count == _BufferSize)
    return ((_Total >> (_BufferBits-1)) + 1) >> 1;
  else
    return trunc((1.0 * _Total)/_Count + 0.5);
}

void AveragingAnalogRead::Init(const byte aBufferBits)
{
  _BufferBits = aBufferBits;
  _BufferSize = 1 << aBufferBits;

  for(int i=0; i<_BufferSize; i++)
    _Buffer[i] = 0;

  _Count = 0;
  _Head = 0;
  _Total = 0;
}

int AveragingAnalogRead::Read()
{
  int lReading = BaseAnalogRead::Read();

  AddToBuffer(lReading);
  int lAverage = CalculateAverage();

  Reading = lAverage;
  return Reading;
}

bool AveragingAnalogRead::setBufferSize(const unsigned int aSize)
{
  if(aSize > MAX_BUFFER_SIZE) return false;
  if(aSize < MIN_BUFFER_SIZE) return false;

  int count = 1;
  unsigned int size = aSize;
  while(size % 2 == 0) 
  {
    size >>= 1;
    count++;
  }

  // Ensure there are no other bits; that the size is a power of two.
  if(size/2 != 0) return false;

  Init(count);
  return true;
}

