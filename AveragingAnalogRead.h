//
//  AveragingAnalogRead.h
//  Sun Tracker
//
//  Created by 治永夢守 on 12/06/03.
//  Copyright 2012 James Knowles. All rights reserved.
//
// This work is licensed under a Creative Commons 
// Attribution-ShareAlike 3.0 Unported License.
//
// https://creativecommons.org/licenses/by-sa/3.0/
//
//
//

#ifndef AVERAGING_ANALOG_READ_H
#define AVERAGING_ANALOG_READ_H

#include "Arduino.h"

//
// SUMMARY
//
// This class reads a sensor and returns averaged readings.
//
// PURPOSE
//
// This class does simple moving averaging of sensor values. 
// Each call to Read() removes the oldest reading from the window
// and adds the new value to it. 
//
// USE
//
// * Set the pin with setPinNumber() (inherited from BaseAnalogRead).
// * Optionally set the buffer size.
// * Call the Read() method.
//
// The last value is held in Reading.
// 
// EXAMPLE
//
//

#include <BaseAnalogRead.h>

const byte MAX_BUFFER_BITS = 5;
const byte MAX_BUFFER_SIZE = 1 << MAX_BUFFER_BITS;
const byte MIN_BUFFER_BITS = 1;
const byte MIN_BUFFER_SIZE = 1 << MIN_BUFFER_BITS;

class AveragingAnalogRead :public BaseAnalogRead
{
  public:
    AveragingAnalogRead();

    //
    // Obtain the current sensor reading. 
    //
    virtual int Read();

    // Retrieve the buffer size
    unsigned int BufferSize();

    // Set the buffer size. To remain efficient,
    // this is restricted to powers of two up to MAX_BUFFER_SIZE.
    //
    // Changing this value will reset all the readings.
    //
    // This returns true if successful, or false if unsuccessful.
    bool setBufferSize(const unsigned int aSize);

  private:
    unsigned int _Buffer[MAX_BUFFER_SIZE];
    byte _BufferBits;
    unsigned int _BufferSize;
    byte _Count;
    byte _Head;
    unsigned long int _Total;

    void AddToBuffer(int aValue);
    int CalculateAverage();
    void Init(const byte aBufferBits);

};

#endif // AVERAGING_ANALOG_READ_H

