# GPIO Output exercise solution

## Additional components

In addition to the components added in exercise 01, another one is added: **Services > Timers > Sleep Timer**. It provides access to timing functions.

## GPIO configuration

If you look at page 810 of the EFR32xG24 Reference Manual, you'll see that there are several different possibilities to configure a GPIO pin as an output. The one we choose for this exercise is *push-pull*. If you want to know more about the reason for choosing this mode, don't hesitate to ask.

## Why is the correspondence ticks / ms displayed?

At some point in the future, after board startup, the number of ticks returned by `sl_sleeptimer_get_tick_count64` will wrap, i.e. will go from 0xFFFFFFFFFFFFFFFF to 0. At this point, the substraction done in `app_process_action` (`ms - prev_ms`) will provide an inconsistent result. Consequently, it's important to know if this event will occur rapidly or not.

The displayed ticks / ms correspondence is 32768 ticks for 1 s. A few divisions allow to know that the wrap event will occur around 17.8 millions of years after board startup. So, we can ignore it when we substract the previous number of milliseconds to the current number of milliseconds.

## About errors

When a problem occurs in an embedded application, usually the application can't rely on a human being for a corrective action. So it has to handle the errors by itself.

In a real application, what is usually done is to reset the microcontroller, sometimes after having saved some context, so that a developer inspecting the application behavior later on can get some information about the last reset(s) on error.

In our exercises, we simply display an error message, as there will always be a human being not too far from the board.