// Menu.cpp

#include "Menu.h"
#include "Globals.h"
#include <LiquidCrystal.h>
#include <avr/EEPROM.h>
#include "Lifecycle.h"
#include "Test.h"


// configuationMenu

uint16_t MenuItem::menuItemCount = 0;

// Add Menu items here and in .h
MenuItem motorSpeed = MenuItem("Speed");
MenuItem proportionalGain = MenuItem("P-gain");
MenuItem derivativeGain = MenuItem("D-gain");
MenuItem pidThreshold = MenuItem("PID-thresh");
MenuItem cliffThreshold = MenuItem("Cliff-thresh");
MenuItem delayPerDegreeTurn = MenuItem("Delay/degTurn");
MenuItem winchSpeed = MenuItem("winchSpeed");
MenuItem configurationMenuItems[] = { motorSpeed, proportionalGain, derivativeGain, pidThreshold, delayPerDegreeTurn, winchSpeed };

void configurationMenu() {
	LCD.clear(); LCD.home();
	LCD.print("Entering"); LCD.setCursor(0, 1); LCD.print("Config menu");
	delay(500);

	while (true) {
		/* Show MenuItem value and knob value */
		int menuIndex = knob(6) * (MenuItem::menuItemCount) / 1024;
		LCD.clear(); LCD.home();
		LCD.print(configurationMenuItems[menuIndex].name); LCD.print(" "); LCD.print(configurationMenuItems[menuIndex].value);
		LCD.setCursor(0, 1);
		LCD.print("Set to "); LCD.print(knob(7)); LCD.print("?");
		delay(100);

		/* Press start button to save the new value */
		if (startbutton()) {
			delay(100);
			if (startbutton()) {
				configurationMenuItems[menuIndex].value = knob(7);
				configurationMenuItems[menuIndex].save();
				delay(250);
			}
		}

		/* Press stop button to exit menu */
		if (stopbutton()) {
			delay(100);
			if (stopbutton()) {
				LCD.clear(); LCD.home();
				LCD.print("Leaving menu");
				delay(500);
				return;
			}
		}
	}
}


// Run menu

String runBot = "Run Bot";
String runSystemTest = "Run System Test";
String runDiagonistics = "Run Diagonistics";
String runMenuItems[] = { runBot, runSystemTest, runDiagonistics };

void runMenu() {
	LCD.clear(); LCD.print("Entering"); LCD.setCursor(0, 1); LCD.print("Run menu"); 
	delay(500);

	while (true) {
		/* Show MenuItem value and knob value */
		int menuIndex = knob(6) * sizeof(runMenuItems) / sizeof(runMenuItems[0]) / 1024;
		LCD.clear(); LCD.home();
		LCD.print(runMenuItems[menuIndex]);
		LCD.setCursor(0, 1);
		LCD.print("select -> start");
		delay(100);

		/* Press start button to save the new value */
		if (startbutton()) {
			delay(100);
			if (startbutton()) {
				String menuSelection = runMenuItems[menuIndex];
				if(menuSelection == runBot) {
					run();
				} else if(menuSelection == runSystemTest) {
					testFullSystem();
				} else {
					systemDiagnostics();
				}
				return;
			}
		}

		/* Press stop button to exit menu */
		if (stopbutton()) {
			delay(100);
			if (stopbutton()) {
				LCD.clear(); LCD.home();
				LCD.print("Going home");
				delay(500);
				return;
			}
		}
	}
}

