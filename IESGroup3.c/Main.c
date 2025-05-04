#include "GPIO.h"
#include "ADC.h"
#include "RGBLED.h"
#include "intrinsics.h"
#include "sensors.h"
#include "Servo.h"
#include "servo.h"

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    init_GPIO();
    initADC();
    RGB_Init();

    setRGBColor(0, 255, 0); // Green for idle
    __enable_interrupt();
    Servo_Control(OFF);
    
    while (1)
    {
        if (get_call_for_heat())
        {
            //  ignition sequence
            setRGBColor(255, 0, 0); // Blue means heat called
            Ign_LED(ON);
            
            while (readThermistor() < readPot()) // Decide if heat is necessary
            {
                setRGBColor(0, 0, 255); // Red for heat needed
                Servo_Control(ON); 
                Solenoid(ON);

                if (flame_Detect())
                {
                    Ign_LED(ON);
                    setRGBColor(255, 255, 255); // White for ignited
                    Servo_Control(ON);
                }
            }
        }
        else
        {
            Solenoid(OFF);
            Ign_LED(OFF);
            setRGBColor(0, 255, 0); // Green for idle
            Servo_Control(OFF);
            break;
        }
    }
}
