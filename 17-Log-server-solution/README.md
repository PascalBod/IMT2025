# Log server exercise solution

## How the project was created

See solution to exercise 12.

## Solution

## Note

The `logger_log` function accepts only one argument, a string which contains the log message. A better interface would accept the arguments accepted by `printf` and `app_log` functions: a format string and 0 to several arguments.

The way to go is to use `va_start`, `va_arg` and `va_end` C library functions. This is not done in this project so that the source code is kept quite simple.