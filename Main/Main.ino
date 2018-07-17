#include "Globals.h"
#include "MenuItem.h"
#include "MotorWheel.h"
#include "Claw.h"
#include <phys253.h>
#include <avr/EEPROM.h>
#include <LiquidCrystal.h>

uint16_t MenuItem::MenuItemCount = 0;
/* Add the menu items here */
MenuItem Speed = MenuItem("Speed");
MenuItem ProportionalGain = MenuItem("P-gain");
MenuItem DerivativeGain = MenuItem("D-gain");
MenuItem IntegralGain = MenuItem("I-gain");
MenuItem PIDThreshold = MenuItem("PID-thresh");
MenuItem menuItems[] = { Speed, ProportionalGain, DerivativeGain };

Claw claw;
MotorWheel motorWheel(Speed, PID(ProportionalGain, DerivativeGain, IntegralGain, PIDThreshold));

void setup() {
	#include <phys253setup.txt>
	Serial.begin(9600);
	LCD.clear();
	LCD.print("Uploaded :)");

	// Swithing first row of digital ins to outs
	pinMode(0, OUTPUT);
	pinMode(1, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);

	delay(1000);
}

void loop() {
	LCD.clear(); LCD.home();
	LCD.print("Start -> Run PID");
	LCD.setCursor(0, 1);
	LCD.print("Stop -> Menu");
	delay(100);

	if (stopbutton()) {
		delay(100);
		if (stopbutton()) {
			Menu();
		}
	}
	else if (startbutton()) {
		delay(100);
		if (startbutton()) {
			Run();
		}
	}
}

void Menu() {
	LCD.clear(); LCD.home();
	LCD.print("Entering menu");
	delay(500);

	while (true) {
		/* Show MenuItem value and knob value */
		int menuIndex = knob(6) * (MenuItem::MenuItemCount) / 1024;
		LCD.clear(); LCD.home();
		LCD.print(menuItems[menuIndex].Name); LCD.print(" "); LCD.print(menuItems[menuIndex].Value);
		LCD.setCursor(0, 1);
		LCD.print("Set to "); LCD.print(knob(7)); LCD.print("?");
		delay(100);

		/* Press start button to save the new value */
		if (startbutton()) {
			delay(100);
			if (startbutton()) {
				menuItems[menuIndex].Value = knob(7);
				menuItems[menuIndex].Save();
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

void Run() {
	unsigned long prevLoopStartTime = millis();
	
	//Check Sensors
	//Drive
	//Deploy Claw
	//Deploy Bridge
	//Deploy Small Bot

	// Calls switchToSmallBot when appropriate

	LCD.clear(); LCD.print("Running PID"); LCD.setCursor(0, 1); LCD.print("Stop to return");
	while(true) {
		//Regulate speed of the main loop to 10 ms
		while (millis() - prevLoopStartTime < 10) {}
		prevLoopStartTime = millis();

		claw.poll();
		motorWheel.poll();

		if (stopbutton()) {
			delay(100);
			if (stopbutton()) {
				loop();
			}
		}
	}
}

void switchToTopBot() {
	claw.switchToTopBot();
	// MotorWheel::switchToTopBot();
}

