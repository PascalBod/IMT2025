# I2C exercise solution

## How the project was created

Start from *Empty C Project* with BRD2601B Rev A01 board as target.

Add following components:
* **Services > Timers > Sleep Timer**
* **Services > IO Stream > IO Stream: STDLIB Configuration**
* **Services > IO Stream > Driver > IO Stream: USART** - instance name: `vcom`
* **Services > IO Stream > IO Stream: Retarget STDIO**
* **Application > Utility > Log**
* **Platform > Driver > I2C > I2CSPM** - instance name: `si7021`

The installation of the IC2SPM component triggers the installation of the **Platform > Peripheral > I2C** component.

Configure the IC2SPM component with the following values:
* **Selected Module**: **I2C0**
* **SCL**: **PC04**
* **SDA**: **PC05**

## I2C initialization

The I2C initialization code can be found in the following way:
* In `main.c`, right-click the call to `sl_system_init` and select **Open Declaration**. This opens the `sl_system_init.c` file
* In this file, right-click the call to `sl_driver_init`, to open its declaration. The `sl_event_handler.c` file is displayed
* In this file, right-click the call to `sl_i2cspm_init_instances`, to open its declaration. The `sl_ic2spm_init.c` file is displayed

`sl_i2cspm_init_instances` calls `I2CSPM_Init` with an initialization block generated according to the configuration of the I2CSPM component.

`I2CSPM_Init` performs the low-level initialization:
* It enables the I2C block clock
* It configures the two GPIO pins used for SCL and SDA
* It connects the I2C block signals to the GPIO pins
* It initializes the I2C block

## Solution

### Maximum number of temperature samples per second

In page 5 of the Si7021 data sheet, table 2 provides the typical conversion time for temperature: 7 ms, for a 14-bit definition (the default value).

Consequently, the maximum number of temperature samples per second that can be retrieved, without considering th I2C communication time, is 1000 / 7 i.e. around 143 samples per second.

### Time to retrieve a temperature sample.

The maximum I2C clock frequency is presented in table 3, on page 5 : 400 kHz. The default configuration set by the I2CSPM component is 100 kb/s (or 100 kHz).

The minimal interaction to read a temperature sample is described on page 20 of the data sheet:
* To the sensor: start condition + 8 bits for salve address and write bit
* From the sensor: acknowledge bit
* To the sensor: 8 bits for the command
* From the sensor: acknowledge bit
* To the sensor : 8 bits for the slave address and read bit
* From the sensor: acknowledge bit
* From the sensor: 8 bits for the MSB
* To the sensor: acknowledge bit
* From the sensor: 8 bits for the LSB
* To the sensor: 1 bit for negative acknowledge + stop condition

The total number of exchanged bits is 45. At 100 kb/s, and if consider that the start and stop conditions are equivalent each to one bit, the total duration of the interaction is: (45 + 2) / 100000 = 470 µs.

### Maximum number of samples retrieved per second

The above period corresponds to a 2128 Hz frequency: 2128 samples per second can be retrieved. This is far more than the maximum number of provided samples.