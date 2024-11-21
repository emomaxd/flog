#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "flog.h"

int main() {
    // Create a ThreadPool for async logging
    flog::ThreadPool pool(4);  // 4 threads for async logging

    // Create a logger with default output stream (std::cout)
    flog::Logger logger("ExampleLogger", std::cout);
    
    // Enable async logging
    logger.enableAsync(pool);
    
    // Enable file logging
    logger.enableFileLogging("log.txt", 5 * 1024 * 1024); //(Optional) File rotating - 5MB
    
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
