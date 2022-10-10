# Car-simulation-for-PIC18
A car simulation using lights, dip-switch, variable resistor, and a PIC18F4331 microcontroller.

Car Simulation
Project Description:
The project is made to simulate driving a car using lights. Materials that will be used are the potentiometer, LEDs, and a switch. 
Each of these will be used to simulate the functionality of the car in a basic form. Driving, stopping, turning, and having a gas tank lights to warn
if they’re about to runout, allowing for a switch to be flipped to refuel. Failure to refuel the car before the red LED will cause the car to completely 
shut off with only the red brake LED on. 
The potentiometer is used to simulate the steering wheel. When turned left, it will light the green light to signal the car is going left, when it is 
turned to the right, the signal from the potentiometer will tell the software that the wheel is going right. The center of the potentiometer will result 
in both lights to be turned on to show that the car is travelling forward. 
The switch will serve as the major portion of the functionality of the project. The switch allows for the car to turn on by enabling switch 1 on the switch, 
which will result in a brake light to be turned on. Setting switch 2 on the switch will cause the car to begin driving, turning of the brake light while 
enabling the green lights. Switches on 7 and 8 will be used to enable the turning lights but when both are switched on, will be in sync when blinking to
represent the warning lights. Switching switch 4 will allow for a white LED to light up to represent headlights. Switch 5 will be used to refuel the car
over time until it hits the max defined fuel.

The LEDs are used to define the output of the interrupts that will be used throughout the project. As stated previously, the LEDs will serve a purpose of 
what direction the car is going. However, the LEDs will show an output of other parts of the project such that if the car is in motion, brake lights, 
headlights, turn lights, and a fuel gauge. The colors of lights go as follows:
Green LEDs will represent the motion of the car. Depending on how the Potentiometer is turned, will allow which lights are enabled if not both if on center.
One red LED will represent the braking of the car. 
The other red LED will be sitting next to a white LED to represent the gas count.
The brake will be turned on or off depending on if the car is in motion. The one that represents the gas will remain lit and only will
start blinking when it’s below a quarter of fuel left.
Yellow LEDs will be placed beside the green LEDs on opposite ends of each other. 
When they are turned on they will blink as if they’re either turning or applying the warning lights.
White Leds will be placed to represent the front head light and fuel count. White LED will be placed at the very front of the
“car” and the other white LED will be used along with a red LED as fuel count. Like the red LED it will remain on above 3 quarters
of the tank and will start blinking upon going below that. When it hits half tank, the white LED will shut off and will remain off until the car refuels.

List the PIC internal peripherals used: 
A2D
Timer
Why is each peripheral used in the project?
	Peripheral 1: The idea behind the A2D is so that the potentiometer can simulate a sensor in the steering, translating 
  the voltage into a digital signal that can be used to determine the direction the car is turning. When the potentiometer is
  turned to the left, it’ll send a digital signal to let the software know that the car is turning left. When the potentiometer is
  turned to the right, it’ll send the digital signal stating that the car will be turning right. When it’s at center, a signal sent will 
  result in both green lights on.
	Peripheral 2:  Timer is used to keep track of the amount of time that passes to generate a real time interrupt to tell the LEDs when they
  should be turned off for the gas gauge. The LEDs will follow a counter provided each time the timer completes a cycle and increments. 
  The values are all reset upon flipping the switch to refuel.



