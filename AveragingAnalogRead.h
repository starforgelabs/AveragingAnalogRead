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
// This code is strictly "as is". Use at your own risk. 
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
// * Set the pin with setPinNumber() (inherited from BufferedAnalogRead).
// * Optionally set the buffer size.
// * Call the Read() method.
//
// The last value is held in Reading.
// 
// EXAMPLE
//
//

#include <BufferedAnalogRead.h>

class AveragingAnalogRead :public BufferedAnalogRead
{
  public:
    AveragingAnalogRead(byte aPinNumber=0);

  protected:
    void Event_NewValue(int aValue, byte aIndex);
    void Event_ReplaceValue(int aOldValue, int aNewValue, byte aIndex);
    void Event_Reset() {Init();}

    // Running total of the buffer.
    unsigned long Total() { return _Total; }

  private:
    unsigned long _Total;

    void Init();
};

#endif // AVERAGING_ANALOG_READ_H

