
/**
 * @file Timer.h
 */

/**********************************************************************

  Created: 20 Nov 2005

    Copyright (C) 2005 Frank Buss, J?r?me Laheurte

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The names of the authors may not be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHORS ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

**********************************************************************/
// $Id: Timer.h 1469 2005-11-20 13:04:05Z fraca7 $

#ifndef _TIMER_H
#define _TIMER_H

#include <psptypes.h>

namespace PSP2D
{
    /**
     * Timer listener
     */

    class TimerListener
    {
      public:
       virtual ~TimerListener() {};

       /**
        * This  is  the  main  callback.  If  it  returns  false,  the
        * associated timer will exit its run() method.
        */

       virtual bool fire(void) = 0;
    };

    /**
     * High-precision timer for firing events at specified intervals
     */

    class Timer
    {
      public:
       /**
        * Constructor. The Timer becomes owner of 'listener'.
        *
        * @param tmo: Interval in milliseconds
        * @param listener: An object whose method 'fire' will be invoked at regular intevals
        */

       Timer(u32 tmo, TimerListener *listener);

       ~Timer();

       /**
        * Main loop.
        */

       void run(void);

      protected:
       u32 _tmo;
       TimerListener *_listener;
    };
};

#endif /* _TIMER_H */
