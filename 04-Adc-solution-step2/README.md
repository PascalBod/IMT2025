# ADC exercise solution - step 2

In order to perform repeated conversions, the overall code must do something similar to this:
```
start a conversion

while (true)

    wait for end of conversion
    get conversion result, calculate associated value, display it

    wait for 1 s
    start a conversion
```

An infinite while loop should not be inserted into `app_process_action`. This would prevent any other piece of code having to run concurrently from being executed.

Note: in our very simple application, there is no such piece of code. But that's a good practice to implement a future-proof architecture.

So, `app_process_action` should return quite rapidly, performing only a few actions at each call. But, of course, the current state (we are waiting for the end of converion, or we are waiting before starting a new conversion) should be remembered between two successive calls. A clean way to do this is to use a Finite State Automaton (FSA) (or Finite State Machine - FSM). The solution implements such an FSA.