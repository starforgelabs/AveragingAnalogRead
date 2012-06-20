/*
 *  AveragingAnalogRead.cpp
 *
 *  Created by 治永夢守 on 12/05/27.
 *  Copyright 2012 James Knowles. All rights reserved.
 *
 * This work is licensed under a Creative Commons 
 * Attribution-ShareAlike 3.0 Unported License.
 *
 * https://creativecommons.org/licenses/by-sa/3.0/
 *
 * This code is strictly "as is". Use at your own risk. 
 *
 *
 */

#include "AveragingAnalogRead.h"
#include <math.h>


AveragingAnalogRead::AveragingAnalogRead(byte aPinNumber) : BufferedAnalogRead(aPinNumber)
{
  Init();
}

void AveragingAnalogRead::Event_NewValue(int aValue, byte aIndex)
{
  _Total += aValue;
  Value = trunc((1.0 * _Total)/Count() + 0.5);
}

void AveragingAnalogRead::Event_ReplaceValue(int aOldValue, int aNewValue, byte aIndex)
{
  _Total += aNewValue - aOldValue;
  byte count = BufferSize();
  Value = (_Total / (count/2)+1) / 2;
}

void AveragingAnalogRead::Init()
{
  _Total = 0;
}

