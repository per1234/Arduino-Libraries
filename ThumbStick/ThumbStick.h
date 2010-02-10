/*
 * ThumbStick.h
 * Kyle Isom <brokenlcd@gmail.com>
 *
 * Arduino library to abstract use of the thumb joystick sold on Sparkfun.
 * The vertical and horizontal axis are indicated on the breakout board.
 *
 * By default, the analog outputs are mapped to between -511 and 512.
 *
 * The center button (called select on the breakout board) is debounced using
 * the arduino's internal pullup. If you should choose to use an external
 * pullup, you will need to swap the SWITCH_STATE values.
 *
 */
 
#ifndef __THUMBSTICK_H
#define __THUMBSTICK_H
 
#include <inttypes.h>
#include "WProgram.h"

#define DEFAULT_HORIZ_PIN           0
#define DEFAULT_VERT_PIN            1
#define DEFAULT_SEL_PIN             2
#define DEBOUNCE_DELAY             40
#define SWITCH_STATE_PRESSED      LOW
#define SWITCH_STATE_NOTPRESSED  HIGH
#define CENTER_RANGE               10
#define analogLow                   0
#define analogHigh               1023

 class ThumbStick {
    public:
        
        /****************
         * CONSTRUCTORS *
         ****************/
         
         // constructor #1: user declares horizontal and vertical axis output
         // pin as well a select output pin.
        ThumbStick(int HorizPin, int VertPin, int SelectPin);
        
        // constructor #2: assumes the select button output is not wired to
        // the arduino. Requires explicit declaration of both analog outputs.
        ThumbStick(int HorizPin, int VertPin);
        
        // constructor #3: explicitly set all pins as well as both map_high 
        // and map_low
        ThumbStick(int MapLow, int MapHigh, int HorizPin, int VertPin, int SelectPin);
        
        // default constructor: will assume the horizontal axis output is wired
        // to analog pin 0, vertical axis output is wired to analog pin 1, and
        // the select button is wired to digital pin 2.
        ThumbStick();
        
        /**********************
         * ACCESSOR FUNCTIONS *
         **********************/
        
         // returns horizontal or vertical axis with map_low being far right /  
         // and map_high being far left.
        int getH(void); 
        int getV(void);
        int getMapLow(void) { return map_low; }
        int getMapHigh(void) { return map_high; }
        int getCenter(void) { return ( (map_low + map_high) / 2); }
        
        boolean isLeft(void) { return (getH() > (getCenter() + CENTER_RANGE) ? true : false); }
        boolean isRight(void) { return (getH() < (getCenter() - CENTER_RANGE) ? true : false); }
        boolean isUp(void) { return (getV() > (getCenter() + CENTER_RANGE) ? true : false); }
        boolean isDown(void) { return (getV() < (getCenter() - CENTER_RANGE) ? true : false); }
        boolean isPressed(void);

        /*************
         * MODIFIERS *
         *************/
        
         // will set center values
         void calibrate(void);
         
         
         
    private:
        int hpin;
        int vpin;
        int spin;
        int sel_last_state;
        int sel_last_debounce;
        signed int hcen;
        signed int vcen;
        signed int map_high;
        signed int map_low;
        static const signed int DEFAULT_MAP_HIGH = 512;
        static const signed int DEFAULT_MAP_LOW = -512;
     
        void _setup(void);
 };
 
 #endif