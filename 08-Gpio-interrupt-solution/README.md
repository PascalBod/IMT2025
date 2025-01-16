# GPIO interrupt exercise solution

## How the project was created

Start from *Empty C Project* with BRD2601B Rev A01 board as target.

Add following components:
* **Services > IO Stream > IO Stream: STDLIB Configuration**
* **Services > IO Stream > Driver > IO Stream: USART** - instance name: `vcom`
* **Services > IO Stream > IO Stream: Retarget STDIO**
* **Application > Utility > Log**
* **Platform > Driver > GPIOINT**

## Solution

The call to `GPIO_ExtIntConfig` configures the interrupt so that it is triggered when a rising edge or a falling edge appears at the GPIO pin. According to the Dev Kit schematic, the button connects the GPIO pin to ground when it is pressed. This means that when the button is released, a rising edge appears on the GPIO pin. Consequently, the call to `GPIO_ExtIntConfig` should be:
```
  GPIO_ExtIntConfig(BTN0_PORT,
                    BTN0_PIN,
                    EXT_PIN_INT,
                    true,     // Rising edge.
                    false,    // Falling edge.
                    true      // Enable the interrupt.
                    );
```

If the button was pressed very rapidly, the following succession of events could appear:
* Starting from idle state after a reset, `int_nb` and `prev_int_nb` are set to `0`
* The button is released and `int_nb` value is set to `1` by `on_gpio_change`
* Next time `app_process_action` is called, `int_nb` is compared to `prev_int_nb`. As they are now different, the statement between braces will be executed
* At that time, the button is released again, so `app_process_action` execution is stopped, and `on_gpio_change` is run, and sets `int_nb` to `2`
* The ISR returns and control is given back to `app_process_action`. It will display `2`, for the new number of interrupts, without having displayed `1`

Remember the exercise 2? The architecture of the solution (GPIO pin polling) was not able to keep up with very rapid successive button presses. Here, using an interrupt allows us to count the number of button releases in a far more accurate way.

If the button releases frequency was very very high, a new interrupt could be triggered while `on_gpio_change` is being executed. The interrupt would be kept on hold until the ISR returns and the nexecuted. So the value of `int_nb` would still be correct.

But if the button was released twice in a row while the ISR is being executed, the code would miss one interrupt.

A possible solution could be to use a microcontroller with a higher clock frequency.


