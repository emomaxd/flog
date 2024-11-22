# flog - C++ Logging Library

**flog** is a simple and efficient C++ logging library that supports basic logging functionalities, see below.

Features:
---------
- **Log Levels**: TRACE, DEBUG, INFO, WARN, ERROR, CRITICAL.
- **Color-Coded Output**: Different log levels are colored for easier reading in the console.
- **Async Logging**: Can offload logging to a thread pool for non-blocking log writes.
- **Custom File Logging**: Ability to configure log file path and log rotation parameters.
- **Log Rotation**: Automatically rotates log files when they exceed a specified size.

Usage
-----
To use the flog logging system, you need to **include the "flog.h" header file** and follow the steps below.
-----

0. **Use default logger**
    ```cpp
    // Logging with default logger
    flog::trace("Scientific notation: {s}", 123456.789);  // Logs in scientific notation
    flog::debug("Formatted float: {.3}", 3.14159);  // Logs float with 3 decimal places
    flog::info("Binary format with positional parameter: {1:b}", 255, 12);  // Logs in binary format
    flog::warn("Hex format: {x}", 255);  // Logs in hex format (lowercase)
    flog::trace("Hex format: {X}", 255);  // Logs in hex format (uppercase)
    ```

1. **Create a Logger**:
   The Logger class is the central component. You can create a Logger instance using the LoggerManager.

   Example:
   ```cpp
   auto logger = flog::LoggerManager::createLogger("MyLogger", std::cout);
   ```

2. **Log Messages**:
   Instead of using the default logger you can use the logger you have created.

   Example:
   ```cpp
    logger.trace("Trace level log.");
    logger.debug("Debug level log with number: {}", 42);
   ```

3. **Asynchronous Logging**:
   You can enable asynchronous logging by setting up a thread pool. Async logging offloads log writes to background threads for non-blocking performance.

   Example:
   ```cpp
    // Enable async logging
    flog::ThreadPool pool(4);  // 4 threads in the thread pool
    logger->enableAsync(pool);
   ```

4. **Log Rotation**:
   The log files will rotate automatically when the size of the log file exceeds the configured limit. The system keeps a specified number of backup files.

   Example:
   ```cpp
   logger->enableFileLogging("log.txt", 1024 * 1024); //(Optional) Rotate after 1MB
   ```

5. **Flushing Logs**:
   You can flush the log output (both console and file) manually using the `flush` method.

   Example:
   ```cpp
   logger->flush();
   ```

Example Usage:
--------------
```cpp
#include "flog.h"

int main() {
    // Create a ThreadPool for async logging
    flog::ThreadPool pool(4);  // 4 threads for async logging

    // Create a logger with default output stream (std::cout)
    flog::Logger logger("ExampleLogger", std::cout);
    
    // Enable async logging
    logger.enableAsync(pool);
    
    // Enable file logging
    logger.enableFileLogging("log.txt", 5 * 1024 * 1024); //(Optional) File rotating - rotate after 5MB
    
    // Set periodic flush (every 3 seconds)
    logger.setPeriodicFlush(std::chrono::seconds(3));
    
    // Set the backtrace threshold for flushing the log buffer
    logger.setBacktraceThreshold(5);
    
    // Logging some messages with various levels
    logger.trace("Trace level log.");
    logger.debug("Debug level log with number: {}", 42);
    logger.info("Info level log: {0} is the current value of {1}", 13, 10);
    logger.warn("Warning log: Low disk space.");
    logger.error("Error log: Failed to load configuration.");
    logger.critical("Critical log: System failure imminent!");
    
    // Demonstrating file logging and rotation
    logger.info("This will be logged to the file.");
    for (int i = 0; i < 1000; ++i) {
        logger.info("Logging to file: {}", i);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    // Test logging with scientific, binary, hex formatting
    double pi = 3.141592653589793;
    int number = 255;
    logger.info("Scientific notation: {.3}", pi);
    logger.info("Binary format: {b}", number);
    logger.info("Hexadecimal format: {X}", number);

    // Demonstrating the default static logger
    flog::trace("Using default logger trace.");
    flog::debug("Using default logger debug with value: {}", 123);
    //flog::info("Using default logger info: {}", "message");

    // Allow async tasks to complete
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Shutdown the logger and thread pool
    flog::LoggerManager::shutdown();

    return 0;
}
```