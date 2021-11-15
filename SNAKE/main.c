// main file for running the schedule

/* Copyright 2021 John Lehner & Josiah Mortorff

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

//HARDWARE REQUIREMENTS
//stm32l053R8 Microcontroller
//breadboard
//EA DOGS102N-6 Display - x3 1uF Capacitors
//PEC12R - 12mm Incremental Encoder - x2 10k Ohm Resistors - x2 0.01uF Capacitors
//LED - 330 Ohm Resistor

//DISPLAY WIRING - display to stm32
//PIN 15 to 1uF capacitor to GND
//PIN 16 (VB1-) to 1uF capacitor to PIN 19 (VB1+)
//PIN 17 (VB0-) to 1uF capacitor to PIN 18 (VB0+)
//PIN 20 (VSS) to GND
//PIN 21 (VSS) to GND
//PIN 22 (VDD2/3) to 3.3v
//PIN 23 (VDD1) to 3.3v
//PIN 24 (SDA) to PA7
//PIN 25 (SCK) to PA5
//PIN 26 (CD) to PA1
//PIN 27 (RST) to PA0
//PIN 28 (CS0) to PA4

//KNOB WIRING - knob to stm32
//TERMINAL A to 10k Ohm resistor to 0.01uF capacitor to GND
//TERMINAL A to PB8
//TERMINAL B to 10k Ohm resistor to 0.01uF capacitor to GND
//TERMINAL B to PB9
//TERMINAL C to GND

//LED WIRING - LED to stm32
//Anode to 330 Ohm Resistor to PB13
//Cathode to GND


#include "main.h"
queue_t Direction;// queue for use from knob to game logic
queue_t Locations;
queue_t light;

int main()
{
	//queues for game logic to display
	init_queue(&Direction, 1);
	init_queue(&Locations, 2);
	//queue for game to led
	init_queue(&light, 1);
	
	while(1)
	{
		knob();
		game();
		led();
		Display();
	}
}