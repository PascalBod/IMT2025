# Timer interrupt exercise solution

## How the project was created

Start from *Empty C Project* with BRD2601B Rev A01 board as target.

Add following components:
* **Services > IO Stream > IO Stream: STDLIB Configuration**
* **Services > IO Stream > Driver > IO Stream: USART** - instance name: `vcom`
* **Services > IO Stream > IO Stream: Retarget STDIO**
* **Application > Utility > Log**
* **Services > Timers > Sleep Timer**
