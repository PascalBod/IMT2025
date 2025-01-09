# GPIO Input exercise solution

## GPIO configuration

When reading the GPIO documentation, you perhaps saw that it's possible to configure a GPIO input pin with an internal pullup or pulldown resistor. As the Dev Kit board uses an external pullup resistor, the internal one should not be activated.

You perhaps also saw that it's possible to activate a filter, which can help in debouncing the input signal. Again, as the Dev Kit board provides external components for this function, no need to activate the internal one.

## Answer to the question

The button state is read in the `app_process_action` function. This function is repeatedly called in the infinite while loop in `main`. But this loop also calls the `sl_system_process_action` function. We don't know how long it takes to be executed, but we are sure it takes some time.

When a push/release cycle is very rapid, it may occur while `sl_system_process_action` is being executed. In this case, it will not be seen by the application. This means that the application may miss some information about what is happening to the button. For this exercise, this is no big deal. In some real life systems, it can be catastrophic.

We will see a better way to check button state changes later on.