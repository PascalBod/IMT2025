# ADC exercise solution - step 1

`app_process_action` must wait for the result of the conversion. To do this, we can use the `IADC_getSingleFifoCnt` function, which returns the number of conversion results in the single channel conversion FIFO. If the number of conversions is 0, this means that the result is not available yet.

Once the result is available, it is read thanks to `IADC_pullSingleFifoResult`.

Then, the returned value must be transformed into the voltage value. Refer to the comments in the source code.