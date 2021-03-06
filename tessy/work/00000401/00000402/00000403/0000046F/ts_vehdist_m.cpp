/*
 * Testdriver source generated by TESSY
 *
 * (c) Razorcat Development GmbH
 *
 * DO NOT EDIT THIS FILE !
 *
 *
 * File          : Master Source (ts_vehdist_m.cpp)
 * Testpath      : C:/Users/Sowjanya/Projects/TESSY/REQ_MN~3/tessy\work\00000401\00000402\00000403\0000046F
 * Modulename    : New Module
 * Testobjectname: vehdist
 * Date          : 21.07.2020
 * Time          : 09:51:02
 * Tessy Version : 4.2.8
 *
 */

#include <stdio.h>
#include "library/librazorcat.h"
#include "library/ts_stringlist.h"

#include "idb/ifobjects.h"
#include "comm/tstcomm.h"
#include "s/tssacc_types.h"
#include "idb/idbdef.h"
#include "driver/ts_master.h"
#include "driver/ite_types.h"
#include "driver/eval.h"
#include "ts_env.h"

#ifndef NULL
   #define NULL ((void *) 0)
#endif

#ifdef EXECUTE
   #undef EXECUTE
#endif
#define EXECUTE(s) if (TS_SUCCESS != s) tstcomm_error_exit(TSTCOMM_ERROR_GENERAL_MASTER);

#define TS_ROOT_FOLDER      "C:/Users/Sowjanya/Projects/TESSY/REQ_MN~3/tessy"
#define TS_PROJECT_ID        1024
#define TS_MODULE_ID         1027
#define TS_TESTOBJECT_ID     1135
#define TS_TESTOBJECT_IDB_ID 2

#define TS_MODULE     "New Module"
#define TS_TESTPATH "C:/Users/Sowjanya/Projects/TESSY/REQ_MN~3/tessy\\work\\00000401\\00000402\\00000403\\0000046F"
#define TS_TESTOBJECT "vehdist"

#define TDB_LOAD_INPUT_TABLE		0x00000001
#define TDB_LOAD_EXPECTED_TABLE	0x00000002
#define TDB_LOAD_ACTUAL_TABLE    0x00000004
#define TDB_FLAG_INHERITED		   0x00040000

#define TARGET_KIND_NULL    0
#define TARGET_KIND_DYNAMIC 1
#define TARGET_KIND_NORMAL  2

typedef struct tag_IDNAME {
   int   Id;
   const char  *Name;
   bool  asap;
} IDNAME;

IDNAME ts_NameTable[] =
{
   {6, "distance", false},
   {7, "timedur", false},
   {5, "vehdist", false},
   {0, ""}
};

unsigned long   ts_testcase_order_number;
unsigned long   ts_teststep_order_number;
unsigned long   ts_teststep_id;

/* Testdata */
static char *ts_value;
using namespace Driver;

static Master  ts_master(true);
/*
 * Helper for Value
 */
static IDNAME *ts_getNameEntry(long tid) {
   for (int i = 0; ts_NameTable[i].Id != 0; i++) {
      if (ts_NameTable[i].Id == tid) {
         return &ts_NameTable[i];
      }
   }
   return NULL;
}

static bool ts_save = true;

static void ts_save_actual_value(IDB_TYPEID tid, IDB_TYPEID id, SACC_TYPE_CODE typecode, int size=0) {
   if (!ts_save) return;

   IDNAME *nameentry = ts_getNameEntry(tid);
   const char *name  = nameentry != NULL ? nameentry->Name : NULL;
   bool asap         = nameentry != NULL ? nameentry->asap : false;
   ts_master.setActualValue(tid, id, typecode, size, ts_value, name, asap);
}

static char ts_use_value(const char* value) {
   char use;
   if (value) {
      use = 1;
      strcpy(ts_value, value);
   }
   else {
      use = 0;
   }
   tstcomm_put_char(use);
   return use;
}

static SACC_TYPE_CODE ts_get_enum_typecode(SACC_TYPE_CODE tc) {
   if (tc == SACC_TYPE_AFZ) {
      return 10;
   }
   return tc;
}

static bool constwarned = false;
static CTStringList constwarnings;
static void ts_const_warning(CTIFObject *ifobject) {
   SACC_TYPE_CODE ptc = ifobject->GetParent() ? ifobject->GetParent()->GetTypeCode() : SACC_TYPE_NONE;
   if (ifobject->GetParent() && (SACC_TYPE_POINTER_OR_REFERENCE(ptc) || ptc == SACC_TYPE_FELD)) {
      ifobject = ifobject->GetParent();
   }
   string name; ifobject->getFullName(name, true);
   if (!constwarned && !constwarnings.hasString(name)) {
      constwarnings.add(name);
      LIB_REPORT_WARNING(TESSY_FACILITY_DRV, "Setting value of const variable '%s'", name.c_str());
   }
}

static void ts_send_value(SACC_TYPE_CODE typecode, int tid, int arrayid, int size=0) {
   IDNAME *nameentry = ts_getNameEntry(tid);
   const char *name  = nameentry != NULL ? nameentry->Name : NULL;
   if (ts_use_value(ts_master.getInputValue(tid, arrayid, typecode, size, name))) {
      EXECUTE(tstcomm_put_value(typecode, ts_value))
   }
}

static void ts_send_value(CTIFObject* ifobject, int arrayid, int size=0) {
   if (!ifobject->IsIN()) {
      tstcomm_put_char(0);
   }
   else {
      if ((ifobject->GetTypeModifier() & SACC_TYPE_MOD_CONST) && !(ifobject->getScope() & IDB_SCOPE_PARAMETER)) {
         ts_const_warning(ifobject);
      }
      ts_send_value(ts_get_enum_typecode(ifobject->GetTypeCode()), ifobject->GetTypeId(), arrayid, size);
   }
}

static void ts_receive_value(SACC_TYPE_CODE typecode, int tid, int arrayid, bool save, int size=0)
{
   {EXECUTE(tstcomm_get_value(typecode, ts_value))}
   if (save) {
      ts_save_actual_value(tid, arrayid, typecode, size);
   }
}

static void ts_receive_value(CTIFObject *ifobject, int arrayid, int size=0)
{
   ts_receive_value(ts_get_enum_typecode(ifobject->GetTypeCode()), ifobject->GetTypeId(), arrayid, ifobject->IsOUT(), size);
}


/*
 * Send/receive data for dynamic objects
 */

/*
 * Send Testdata to slave
 */
void ts_send_TD(void) {
   CTIFObject *ifobject(0);

   /* Globals */
   ifobject = ts_master.getIFObject(8, 7);
   if (!ifobject) {LIB_REPORT_WARNING(TESSY_FACILITY_DRV,"%s", "NULL ifobject id 7\n");}
   ts_send_value(ifobject, 0);
   if (!constwarnings.Is_Empty() && !constwarned) {
      constwarned = true;
      LIB_REPORT_WARNING(TESSY_FACILITY_DRV,"%s", "Setting a const variable may result in undefined behaviour. Set the variable passing IRRELEVANT in those cases");   }
}


/*
 * Receive Actual Data from slave
 */
static void ts_receive_AD(void)
{
   CTIFObject *ifobject(0);

   /* Globals */
   ifobject = ts_master.getIFObject(2, 6);
   if (!ifobject) {LIB_REPORT_WARNING(TESSY_FACILITY_DRV,"%s", "NULL ifobject id 6\n");}
   ts_receive_value(ifobject, 0);

   /* Return */
   ifobject = ts_master.getIFObject(16, 5);
   if (!ifobject) {LIB_REPORT_WARNING(TESSY_FACILITY_DRV,"%s", "NULL ifobject id 5\n");}
   ts_receive_value(ifobject, 0);
}


/* Include helper functions */
#include "driver/ts_master.cc"

/* Execute a Teststep */
uint64_t ts_execute_teststep(unsigned long repeatCount, Teststep *teststep)
{
   uint64_t state_mask = 0;
   unsigned char result;
   unsigned long flags = TDB_LOAD_INPUT_TABLE | TDB_LOAD_EXPECTED_TABLE;

   flags |= (teststep->isInherited() ? TDB_FLAG_INHERITED : 0);

   ts_master.load(teststep, flags);

   tstcomm_put_ulong(ts_teststep_order_number);
   tstcomm_put_ulong(repeatCount);

#if defined TS_SUPPORT_SCRIPT
   tstcomm_user_script(TSTCOMM_PROLOG, ts_testcase_order_number, ts_teststep_order_number);
   tstcomm_user_script(TSTCOMM_EPILOG, ts_testcase_order_number, ts_teststep_order_number);
#endif /* TS_SUPPORT_SCRIPT */

   ts_send_TD();
   ts_master.update(teststep);

   result = ts_wait_for_slave();
   if (result != 0) {
      LIB_REPORT_ERROR(TESSY_FACILITY_DRV,"Test object '%s' terminated with exit code %d", result);
   }
   ts_receive_AD();
   state_mask = ts_master.save();
   return state_mask;
}


/*
 * main
 */
int main(int argc, char* argv[])
{
   int            result;
   unsigned long  repeat;
   TestcaseList   *testcase_list;
   TeststepList   *teststep_list;
   /* disable Windows(TM) crash dialogue */
   DWORD dwMode = SetErrorMode(0);
   SetErrorMode(dwMode | SEM_NOGPFAULTERRORBOX);

   /**/
   ts_value = (char*)calloc(256, sizeof(char));

   if (argc > 1 && 0 == strcmp(argv[1], "-break")) {
      _TessyEnvironment[3] = strdup("vehdist");
   }

   TS_CommChecksum = 0;

   TS_CommCompress = 0;

   TS_CommTransferLimit = 0;


   /* init master object */
   ts_master.init(TS_ROOT_FOLDER, TS_PROJECT_ID, TS_MODULE_ID, TS_TESTOBJECT_ID);

  /* load testcase list */
   testcase_list = ts_master.getTestcaseList();
   if (0 == testcase_list->getCount()) {
      LIB_REPORT_ERROR(TESSY_FACILITY_DRV,"%s","No test cases available");
   }

   /* prepare Communication */
   if (TS_SUCCESS != (result = tstcomm_open())) {
      LIB_REPORT_ERROR(TESSY_FACILITY_DRV,"Failed to establish communication; error %d", result);
   }
   /* testobject prolog */
#if defined TS_SUPPORT_SCRIPT
   tstcomm_user_script(TSTCOMM_PROLOG, 0, 0);
#endif /* TS_SUPPORT_SCRIPT */

   /* loop over testcases */
   for (Testcase * testcase = testcase_list->getNext(); testcase; testcase = testcase_list->getNext()) {
      if (!testcase->isExecutable()) {continue;}

      /* testcase */
      ts_testcase_order_number = testcase->getTestcaseNumber();
      uint64_t state_mask = 0;
      teststep_list = testcase->getTeststepList();
      if (0 == teststep_list->getCount()) {
         LIB_REPORT_ERROR(TESSY_FACILITY_DRV,"Failed to load test steps for test case %lu", ts_testcase_order_number);
      }

         tstcomm_put_ulong(ts_testcase_order_number);
         tstcomm_put_uchar(testcase->hasFaultInjection() ? 1 : 0);
#if defined TS_SUPPORT_SCRIPT
         tstcomm_user_script(TSTCOMM_PROLOG, ts_testcase_order_number, 0);
#endif /* TS_SUPPORT_SCRIPT */
      // ts_set_timer(TDB, TS_TIMER_START);

      /* loop over teststeps */
      for (Teststep * teststep = teststep_list->getNext(); teststep; teststep = teststep_list->getNext()) {
         if (!teststep->isExecutable()) {continue;}

         /* teststep */
         ts_teststep_order_number = teststep->getTeststepNumber();
         ts_teststep_id           = teststep->getId();
         repeat                   = teststep->getRepeatCount();

         state_mask |= ts_execute_teststep(repeat, teststep);
      // ts_set_timer(TDB, TS_TIMER_STOP);
      }
      tstcomm_put_ulong(0);
#if defined TS_SUPPORT_SCRIPT
      tstcomm_user_script(TSTCOMM_EPILOG, ts_testcase_order_number, 0);
#endif /* TS_SUPPORT_SCRIPT */
      /* free memory */
      delete teststep_list;
      testcase->setExecuted(state_mask);
      testcase->flush();
   }
   tstcomm_put_ulong(0);
#if defined TS_SUPPORT_SCRIPT
   tstcomm_user_script(TSTCOMM_EPILOG, 0, 0);
#endif /* TS_SUPPORT_SCRIPT */
   tstcomm_close();

   ts_master.shutdown();
   TerminateProcess(GetCurrentProcess(), 0);
}
