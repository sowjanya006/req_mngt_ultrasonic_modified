
/*
 * File generated by TESSY.
 * DO NOT EDIT THIS FILE!
 */

 /* Allow main as testobject */
#define main  ts_main
#define TESSY_SOURCE_01

/* stubfunction counters */
#include "ts_stubcounter.h"

extern float timedur;
float distance;
typedef enum {obst_near,obst_far,inv_dist,inv_time}status;

status vehdist()
{
   if(timedur > 0.0)
    {
    distance = ((timedur/2)*34.4);
    if (distance < 2 || distance > 80)
    	return inv_dist;
    else
    {
   	if (distance < 30.0)
   		return obst_near;
   	else
   	    return obst_far;
	}
    }
  	else
 	   return inv_time;
}




/****************************************************************/
/* T E S S Y  C O D E                                           */
/****************************************************************/

#define __TS_THIS_IS_THE_SLAVE__

/*
 * external variables
 */
float timedur;

#include "tstcomm.h"
#include "ts_vehdist_s.h"
#include "ts_usr.h"
#include "ts_stub_declarations.h"


/*
 * Returnvalue
 */
status TS_TESTOBJECT_RETURN;

/*
 * Stub Variables
 */
extern char TESSY_use_value(void);

/*
 * Receive Testdata from master
 */
void TESSY_receive_TD01(void) {

   /* Globals */
   if (TESSY_use_value()) {timedur = tstcomm_get_float();}
}

void TESSY_send_TD01(void) {

   /* Globals */
   tstcomm_put_float(distance);
}


/* Return */
void TESSY_send_return(void) {
   tstcomm_put_long((long)TS_TESTOBJECT_RETURN);
}

/*
 * DO NOT EDIT THIS FILE!
 *
 * This file is automatically generated each time a test
 * is executed and all changes made to this file will be lost.
 */
#include "ts_usr.h"
#include "ts_vehdist_s.h"


#include "tsteval.h"

#ifndef TS_CURRENT_TESTCASE_DEFINED
	/* Current Testcase / Teststep and repeatcount*/
	extern TESSY_uint32   TS_CURRENT_TESTCASE;
	extern TESSY_uint32   TS_CURRENT_TESTSTEP;
	extern TESSY_uint32   TS_REPEAT_COUNT;
#endif


/*
 * User definitions
 */


/*
* User code to execute before test execution starts.
 */
void ts_tobj_prolog (void) {

}

/*
* User code to execute after test execution finished.
 */
void ts_tobj_epilog (void) {

}

/*
 * This function is called each time just before
 * a specific testcase and teststep is executed.
 */
void ts_tc_prolog (void) {
}


/*
 * This function is called each time just after
 * a specific testcase and teststep was executed.
 */
void ts_tc_epilog (void) {
}

void TESSY_TestobjectCall(void) {
   TS_TESTOBJECT_RETURN = vehdist();
}

