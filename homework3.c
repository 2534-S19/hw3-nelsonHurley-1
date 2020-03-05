#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "homework3.h"
#include "myGPIO.h"
#include "myTimer.h"
//Nelson Hurley 3/4/20
int main(void)
{
    // Count variables to control the LEDs.
    unsigned int count0 = 0;
    unsigned int count1 = 0;

    // TODO: Declare the variables that main uses to interact with your state machine.

    unsigned char button_Press = 'p';
    bool debounced = false;
    // Stops the Watchdog timer.
    initBoard();
    // Initialize the GPIO.
    // YOU MUST WRITE THIS FUNCTION IN myGPIO.c
    initGPIO();
    // Initialize Timer0 to provide a one second count interval for updating LED2.
    // YOU MUST WRITE THIS FUNCTION IN myTimer.c
    initTimer(TIMER0, TIMER0_PRESCALER, TIMER0_COUNT);
    // Initialize Timer1 to provide a one millisecond count interval for updating the button history.
    // YOU MUST WRITE THIS FUNCTION IN myTimer.c
    initTimer(TIMER1, TIMER1_PRESCALER, TIMER1_COUNT);

    while(1)
    {
        // Update the color of LED2 using count0 as the index.
        // YOU MUST WRITE THIS FUNCTION BELOW.
        changeLaunchpadLED2(count0);
        // Update the color of the Boosterpack LED using count1 as the index.
        // YOU MUST WRITE THIS FUNCTION BELOW.
        changeBoosterpackLED(count1);

        // TODO: If Timer0 has expired, increment count0.
        // YOU MUST WRITE timer0expired IN myTimer.c
        if(timer0Expired())
            count0++;



        // TODO: If Timer1 has expired, update the button history from the pushbutton value.
        // YOU MUST WRITE timer1expired IN myTimer.c

        if(checkStatus_BoosterpackS1()==PRESSED)
        {
            if(timer1Expired())
            {
                button_Press = 'd';
            }
        }



        // TODO: Call the button state machine function to check for a completed, debounced button press.
        // YOU MUST WRITE THIS FUNCTION BELOW.
        debounced = fsmBoosterpackButtonS1(button_Press);

        // TODO: If a completed, debounced button press has occurred, increment count1.
        if(debounced == true)
        {
            count1++;
            button_Press = 'p';
        }


    }
}

void initBoard()
{
    WDT_A_hold(WDT_A_BASE);
}

// TODO: Map the value of a count variable to a color for LED2.
// Since count is an unsigned integer, you can mask the value in some way.
void changeLaunchpadLED2(unsigned int count)
{

    static State LED = zero;
    int true_count = mask&count;

    switch (LED)
    {
    case zero:
        if(true_count ==zero)
        {
            turnOff_LaunchpadLED2Red();
            turnOff_LaunchpadLED2Green();
            turnOff_LaunchpadLED2Blue();
            LED = one;
        }
        break;
    case one:
        if(true_count == one)
        {
            turnOn_LaunchpadLED2Red();
            LED = two;
        }
        break;
    case two:
        if(true_count==two)
        {
            turnOff_LaunchpadLED2Red();
            turnOn_LaunchpadLED2Green();
            LED = three;
        }
        break;
    case three:
        if(true_count==three)
        {
            turnOn_LaunchpadLED2Red();
            LED = four;
        }
        break;
    case four:
        if(true_count==four)
        {
            turnOff_LaunchpadLED2Red();
            turnOff_LaunchpadLED2Green();
            turnOn_LaunchpadLED2Blue();
            LED = five;
        }
        break;
    case five:
        if(true_count==five)
        {
            turnOn_LaunchpadLED2Red();
            LED = six;
        }
        break;
    case six:
        if(true_count==six)
        {
            turnOff_LaunchpadLED2Red();
            turnOn_LaunchpadLED2Green();
            LED = seven;
        }
        break;
    case seven:
        if(true_count==seven)
        {
            turnOn_LaunchpadLED2Red();
            LED = zero;
        }
        break;
    default:
            turnOff_LaunchpadLED2Red();
            turnOff_LaunchpadLED2Green();
            turnOff_LaunchpadLED2Blue();
    }
}

// TODO: Maybe the value of a count variable to a color for the Boosterpack LED
// This is essentially a copy of the previous function, using a different LED
void changeBoosterpackLED(unsigned int count)
{


        static State booster_Led = zero;
        int true_count2 = mask&count;

        switch (booster_Led)
        {
        case zero:
                if(true_count2 == zero)
                {
                    turnOff_BoosterpackLEDRed();
                    turnOff_BoosterpackLEDGreen();
                    turnOff_BoosterpackLEDBlue();
                    booster_Led = one;
                }
                break;
        case one:
                if(true_count2 == one)
                {
                    turnOn_BoosterpackLEDRed();
                    booster_Led = two;
                }
            break;
        case two:
                if(true_count2 == two)
                {
                    turnOff_BoosterpackLEDRed();
                    turnOn_BoosterpackLEDGreen();
                    booster_Led = three;
                }
            break;
        case three:
                if(true_count2 == three)
                {
                    turnOn_BoosterpackLEDRed();
                    booster_Led = four;
                }
            break;
        case four:
                if(true_count2 == four)
                {
                    turnOff_BoosterpackLEDRed();
                    turnOff_BoosterpackLEDGreen();
                    turnOn_BoosterpackLEDBlue();
                    booster_Led = five;
                }
            break;
        case five:
                if(true_count2 == five)
                {
                    turnOn_BoosterpackLEDRed();
                    booster_Led = six;
                }
            break;
        case six:
                if(true_count2 == six)
                {
                    turnOff_BoosterpackLEDRed();
                    turnOn_BoosterpackLEDGreen();
                    booster_Led = seven;
                }
            break;
        case seven:
                if(true_count2 == seven)
                {
                    turnOn_BoosterpackLEDRed();
                    booster_Led = zero;
                }
            break;
        default:
                turnOff_BoosterpackLEDRed();
                turnOff_BoosterpackLEDGreen();
                turnOff_BoosterpackLEDBlue();
        }


}

// TODO: Create a button state machine.
// The button state machine should return true or false to indicate a completed, debounced button press.
bool fsmBoosterpackButtonS1(unsigned char buttonhistory)
{
    bool pressed = false;
    if(checkStatus_BoosterpackS1()==UNPRESSED &&buttonhistory == 'd')
    {
       pressed = true;
    }


    return pressed;
}
