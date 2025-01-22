# Queue exercise solution

## How the project was created

See solution to exercise 12.

## Solution

To simulate some processing time in the consumer task, first define a time period:
```
#define PROCESSING_PERIOD_MS 200
```

Then add the waiting period:
```
  while (true) {
      os_rs = xQueueReceive(queue, &message, QUEUE_ITEM_WAIT_PERIOD_MS);
      if (os_rs == pdFALSE) {
          app_log_info("Consumer - Queue empty\n");
          continue;
      }
      app_log_info("Consumer - Received %lu from %u\n",
                   message.counter, message.producer_id);
      vTaskDelay(pdMS_TO_TICKS(PROCESSING_PERIOD_MS));
  }
```

A value of 470 ms starts producing some "queue full" log messages, around every 30 seconds.

One possible calculation, to find the maximum value for the processing period is as follows:
* In one minute, i.e. 60000 ms, the number of messages sent by producer 1 is 60000 / 800 = 75.
* In one minute, producer 2 sends 60000 / 1100 = around 55.
* So the total number of messages received by the consumer is 130. If they must all be processed in the same minute, the maximum time spent on processing one message must be 60000 / 130 = around 462.

This is consistent with the experimental value.

Increasing the size of the queue can't be a solution. Simply, this would delay the time when the queue is full. If processing a message can't keep up with message generation pace, there is a design problem. Solutions could be to reduce the number of generated messages, or to increase the processing capability, for instance by increasing CPU frequency, or by using a multicore microcontroller.

`xQueueSendToFront` can be used for prioritary messages, i.e. messages which must be received before the ones already waiting in the queue.