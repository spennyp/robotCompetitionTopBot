// Claw.h

#ifndef _CLAW_h
#define _CLAW_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Claw {
    private:
        void raise();
        void lower();
        void open();
        void close();
        void dump(int numberOfTeddiesGrabbed);
        void positionForBridgeDrop();
        void switchToTopBot();
        bool bottomBot;
        bool grabbed;
        friend void testClaw(); // These are for testing purposes
        friend void testClawBridgeDropPosition();
        friend void systemTest();
    public:
        Claw();
        void grab();
        void reset();
        bool poll(int numberOfTeddiesGrabbed = 0);
};

#endif



