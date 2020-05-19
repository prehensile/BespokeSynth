/*
  ==============================================================================

    INoteReceiver.cpp
    Created: 17 May 2020 10:59:27pm
    Author:  Ryan Challinor

  ==============================================================================
*/

#include "INoteReceiver.h"

NoteInputBuffer::NoteInputBuffer(INoteReceiver* receiver)
: mReceiver(receiver)
{
   for (int i=0; i<kBufferSize; ++i)
      mBuffer[i].time = -1;
}

void NoteInputBuffer::Process(double time)
{
   for (int i=0; i<kBufferSize; ++i)
   {
      if (mBuffer[i].time != -1)
      {
         NoteInputElement& element = mBuffer[i];
         mReceiver->PlayNote(element.time, element.pitch, element.velocity, element.voiceIdx, element.modulation);
         mBuffer[i].time = -1;
      }
   }
}

void NoteInputBuffer::QueueNote(double time, int pitch, float velocity, int voiceIdx, ModulationParameters modulation)
{
   for (int i=0; i<kBufferSize; ++i)
   {
      if (mBuffer[i].time == -1)
      {
         mBuffer[i].time = time;
         NoteInputElement& element = mBuffer[i];
         element.pitch = pitch;
         element.velocity = velocity;
         element.voiceIdx = voiceIdx;
         element.modulation = modulation;
         break;
      }
   }
}
