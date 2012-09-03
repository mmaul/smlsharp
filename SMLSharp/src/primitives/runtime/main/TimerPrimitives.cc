#include "Primitives.hh"
#include "PrimitiveSupport.hh"
#include "Log.hh"
#include "Debug.hh"

// ToDo : 
#if defined(__MINGW32__)
#include <sys/timeb.h>
#else
#include <sys/times.h>
#include <limits.h>
#include <unistd.h>
#endif

BEGIN_NAMESPACE(jp_ac_jaist_iml_runtime)

///////////////////////////////////////////////////////////////////////////////

#if defined(__MINGW32__)

static
void
getTimes(SInt32Value* sysSeconds, SInt32Value* sysMicroSeconds, 
         SInt32Value* usrSeconds, SInt32Value* usrMicroSeconds, 
         SInt32Value* GCSeconds, SInt32Value* GCMicroSeconds)
{
    struct timeb buffer;
    ftime(&buffer);
    
    *usrSeconds = buffer.time;
    *usrMicroSeconds = buffer.millitm * 1000;
    *sysSeconds = 0;
    *sysMicroSeconds = 0;
    *GCSeconds = 0;
    *GCMicroSeconds = 0;
}

#else

static long clocksPerSecond = sysconf(_SC_CLK_TCK);

static
void
clocksToSecond(clock_t clocks,
               SInt32Value *secondsRef,
               SInt32Value *microSecondsRef)
{
    *secondsRef = clocks / clocksPerSecond;
    *microSecondsRef = (clocks % clocksPerSecond) * 1000000 / clocksPerSecond;
    return;
}

static
void
getTimes(SInt32Value* sysSeconds, SInt32Value* sysMicroSeconds, 
         SInt32Value* usrSeconds, SInt32Value* usrMicroSeconds, 
         SInt32Value* GCSeconds, SInt32Value* GCMicroSeconds)
{
    struct tms buffer;
    ::times(&buffer);
    clocksToSecond(buffer.tms_stime, sysSeconds, sysMicroSeconds);
    clocksToSecond(buffer.tms_utime, usrSeconds, usrMicroSeconds);
    clocksToSecond(0, GCSeconds, GCMicroSeconds);// ToDo : GC time
/*
    DBGWRAP(printf("sysSec=%d, sysMicroSeconds=%d \n", *sysSeconds, *sysMicroSeconds);)
    DBGWRAP(printf("usrSec=%d, usrMicroSeconds=%d \n", *usrSeconds, *usrMicroSeconds);)
*/
}

#endif // defined(__MINGW32__)

void
IMLPrim_Timer_getTimeImpl(UInt32Value argsCount,
                          Cell* argumentRefs[],
                          Cell* resultRef)
{
    Cell values[6];
    getTimes(&values[0].sint32, &values[1].sint32,
             &values[2].sint32, &values[3].sint32,
             &values[4].sint32, &values[5].sint32);
    Cell* block = PrimitiveSupport::allocateAtomBlock(6, values);
    resultRef->blockRef = block;
    return;
}

Primitive IMLPrim_Timer_getTime = IMLPrim_Timer_getTimeImpl;

///////////////////////////////////////////////////////////////////////////////

END_NAMESPACE