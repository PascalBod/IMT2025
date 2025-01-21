# Semaphore exercise solution

## How the project was created

See solution to exercise 12.

## Note about the log messages

When the `app_log` functions are called from different tasks at almost the same time, the resulting log messages are not printed correctly: the log functions are not *thread safe*. We will see farther how to deal with this problem.