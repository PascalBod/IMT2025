# Shared structure bug exercise solution

## How the project was created

Start from *Empty C Project* with BRD2601B Rev A01 board as target.

Add following components:
* **Services > IO Stream > IO Stream: STDLIB Configuration**
* **Services > IO Stream > Driver > IO Stream: USART** - instance name: `vcom`
* **Services > IO Stream > IO Stream: Retarget STDIO**
* **Application > Utility > Log**
* **Services > Timers > Sleep Timer**
* **RTOS > FreeRTOS > FreeRTOS**

## Solution

You should have seen messages telling that `b` contains `2`.

The explanation is simple:
* Let's consider that `a` contains `1`
* Task2 performs the `(a == 1)` test, which succeeds. So task2 enters the `if` statement block, which contains a call to `vTaskDelay`, to simulate some processing. This call makes the scheduler switch to another task
* We can imagine that task1 is scheduled. It sets `a` to `1`. Then it calls `vTaskDelay`. The scheduler switchs to another task
* As task1 is waiting for quite a long period of time, the scheduler schedules task2. It sets `a` to `2`. Then it calls `vTaskDelay`. The scheduler switches to another task
* Let's consider the case where the scheduled task is task1. Its execution restarts from where it was, i.e. it assigns `a` to `b`. So, now `b` contains `2`

We will see in next sections how to prevent this kind of problem.

