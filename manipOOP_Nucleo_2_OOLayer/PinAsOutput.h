/*********************************************************************************/
/* OO STM32 Library : PinAsOutput CLASS DECLARATION To configure GPIO Pins as Output 
   E.D - INSAT Nov 2021
        Default Constructor: Push-Pull
 
   Usage: PinAsOutput ObjectName(PA_i), 
          where X is for GPIOX (A, B, C, or D)
          i is the pin number (0 to 15)

   Example: PinAsOutput MyLed(PB_5);
************************************************************************************/

#include <stm32_wrapper_gpio.h>

namespace OOlayer {

class PinAsOutput {
    /** Attribute to save PinName */
    PinName thepin;

public:

    /** Constructor to create a PinAsOutput connected to the specified pin
     *
     *  @param pin PinAsOutput pin to connect to
     */
    PinAsOutput(PinName pin) : thepin(pin) { 
        gpio_init_out_def(pin); 
    }
    
    /** Constructor with mode
     *
     *  @param pin PinAsOutput pin to connect to
     *  @param mode the initial mode of the pin
     */
    PinAsOutput(PinName pin, PinOutMode mode) : thepin(pin) {
        gpio_init_out(pin, mode);
    }

    /** Constructor with mode and speed
     *
     *  @param pin PinAsOutput pin to connect to
     *  @param mode the initial mode of the pin
     *  @param speed the initial speed
     */
    PinAsOutput(PinName pin, PinOutMode mode, PinSpeed speed) : thepin(pin) {
        gpio_init_out_ex(pin, mode, speed);
    }

    /** Read the output pin state (0 or 1)
     *
     *  @returns
     *    An integer representing the state of the output pin,
     *    0 for logical 0, 1 for logical 1
     */
    int read() const {
        return gpio_read_out(thepin);
    }

    /** An operator shorthand for read()
     *
     *  Example: int LedState = MyLed;
     */
    operator int() const {
        return read();
    }

    /** Write a value (0 or 1) to the output pin
     *
     *  @param value The value to write (0 or 1)
     */
    void write(int value) {
        gpio_write(thepin, value);
    }

    /** Overload the assignment operator for `object = value`
     *
     *  @param value The value to assign (0 or 1)
     *  @returns Reference to the current object
     */
    PinAsOutput& operator=(int value) {
        write(value);
        return *this;
    }

    /** Overload the assignment operator for `object = object`
     *
     *  @param other Another PinAsOutput object
     *  @returns Reference to the current object
     */
    PinAsOutput& operator=(const PinAsOutput& other) {
        if (this != &other) {
            int state = other.read();   // Read the state of the other pin
            write(state);               // Write this state to the current pin
        }
        return *this;
    }
};

} // namespace OOlayer
