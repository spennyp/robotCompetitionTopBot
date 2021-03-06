// Test.h

#ifndef _TEST_h
#define _TEST_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


// Diagnostics

extern void systemDiagnostics();


// Sensor Test

extern void sensorTest();
extern void testPidQRD();
extern void testCliffQRD();
extern void testClawIR();
extern void testTouchSensor();
extern void testCommunicationIn();
extern void testLeftSideQRD();


// System Test

extern void systemTest();
extern void testDump();
extern void testClaw();
extern void testClawBridgeDropPosition();
extern void testBridge();
extern void testTurning();
extern void testLeftSweep();
extern void testHardStop();



#endif