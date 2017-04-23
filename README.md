# Simple Real Time Arduino Components

The purpose of this library is to provide a simple interface to control hardware in a non-blocking way (Real-Time).  

Each library component of the library consists in two parts :
 - non-blocking functions using millis() to work
 - blocking functions using delay() (suffixed with `Sync`)

All components are C++ class following the same logic, they have a `constructor` who take the pin to which they are attached, a `setup()` method and a `loop()` method which must each be called in the global arduino `setup()` and `loop()` functions.

## Real Time Led

Control a blinking led on a pin.  

Usage:  
```c
#include "Led.cpp"

Led my_led(7); // Create a led on pin 7

void setup()
{
  my_led.setup(); // Setup the led
  my_led.startBlinking(200); // Start blinking every 200ms
}

void loop()
{
  my_led.loop(); // Event loop
}
```

You can use the following methods to control the component :  
```c
/* Simple functions */
my_led.turnOn(); // Turn on the led
my_led.turnOff(); // Turn off the led
my_led.toggle(); // Toggle the led on or off

/* Realtime blinking functions */
my_led.blinkOnce(500); // Blink one time with 500ms interval
my_led.startBlinking(500)// Blink continuously with 500ms interval
my_led.stopBlinking(); // Stop blinking

/* Non realtime blinking functions */
my_led.blinkOnceSync(500); // Blink one time with 500ms interval
```

## Real Time Button

Get inputs from a button.  
This component work with 2 callbacks, `onPressed` and `onReleased`. You can bind function to these events to execute an action when your button is pressed or released.  
The button can be setup only in [pull-down](https://www.arduino.cc/en/tutorial/button) mode and the component take care of the rebound effect (1 pressure = 1 action).  

Usage:  
```c

#include "Button.cpp"

void print_hello()
{
  Serial.println("Hello !");
}

void print_byebye()
{
  Serial.println("Bye !")
}

Button my_button(7); // Create a button on pin 7

void setup()
{
  Serial.begin(9600);

  my_button.setup(); // Setup the button
  my_button.onPressed(&print_hello); // Call the function `print_hello()` when button is pressed
  my_button.onReleased(&print_byebye); // Call the function `print_byebye()` when button is released
}

void loop()
{
  my_button.loop();
}
```
