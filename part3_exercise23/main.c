#include "msp.h"
#include <stdint.h>
#include <stdio.h>
#include "game.h"
#include "buttons/buttons.h"
#include "LED/led.h"
#include "Analog/analog.h"
#include "timer/timer.h"

// where you write your application.

/**
 * main.c
 */


void main(void)
{
    // Declaration of variables
    // WARNING: always declare variables at the very beginning of function
    uint8_t menu, menu_option, game, error;
    uint16_t x = 0, y = 0;
    
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // Stop WDT

    // Enable global interrupt and initialize
    _enable_interrupts();
    Init_Game();        // Requires interrupts
    init_buttons_int(); //    init_buttons() upgrade-> init_buttons_int()
//    init_rgb();         // initial led
    init_adc14();       // initial adc config

    config_joystic(); 
    // config_accel();
    config_blue_pwm();
    config_red_green_pwm();
    menu_option = 0;
    while (1) // Super Loop
    {
        Create_Menu();
        menu = 1; // The menu is running
        while (menu)
        {
            error = Show_Menu(menu_option);
            if (error)
            {
                show_error("PARAM", "ERROR");
            }
            if (check_and_clear_any_button_flag(B_BU)) // TODO: Go down the menu if bottom button is pressed
            {
                menu_option = (menu_option + 1) % 3;
                // TODO: Add 1 to menu_option taking care that there are 3 options
            }
            if (check_and_clear_any_button_flag(B_UP)) // TODO: Choose the color if the upper buttons is pressed
            {
                // TODO: Call library function Set_Car_Color. ATTENTON. You MUST check the correctnes of the parameter before calling Set_Car_Color().
                led_on(menu_option);
                Set_Car_Color(menu_option);
            }
            if (check_and_clear_any_button_flag(B_JS)) // TODO: if joystick button end menu loop and go to next loop
            {
                menu = 0;
                // TODO: How do you end the menu loop?
            }
        }
        
        Init_Game(); //
        game = 1;    // Let's play!!!
        
        while (game)
        {
            if (check_SysTick_flag()) // SysTick event every 40ms
            {
                Draw_Road();
                Draw_Car();
                better_control(&x,&y);
                printf("x:%d,y:%d \n",x,y);
                Steering_Wheel(x);
                change_speed(y);
                
                if (check_and_clear_any_button_flag(B_JS)) // TODO: if joystick button is pressed, end game loop
                {
                    game = 0;
                    // TODO: How do you end the game loop?
                }
                
            }
        }
    }
}

