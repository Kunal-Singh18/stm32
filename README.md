# **Bare-Metal System Implementation (Self-Learning Project)**  

[![GitHub](https://img.shields.io/badge/GitHub-Repository-blue)](https://github.com/Kunal-Singh18/stm32.git)  

## **Overview**  
This project involves writing **bare-metal code** for an **STM32** microcontroller, strictly adhering to the **CMSIS (Cortex Microcontroller Software Interface Standard)** without using external libraries. The goal is to develop a deeper understanding of microcontroller architecture by implementing low-level drivers and system functionalities from scratch.  

## **Features**  
- **Peripheral Configuration:**  
  - GPIO (General Purpose Input/Output)  
  - USART (Universal Synchronous/Asynchronous Receiver Transmitter)  
  - I2C (Inter-Integrated Circuit)  
  - SPI (Serial Peripheral Interface)  
  - DMA (Direct Memory Access)  
  - SysTick Timer (System Timer)  
- **Interrupt Handling:**  
  - Efficient usage of NVIC (Nested Vector Interrupt Controller)  
  - Custom interrupt service routines (ISRs)  
- **Performance Optimization:**  
  - Low-level hardware interactions for minimal latency  
  - Optimized memory usage and power efficiency  

## **Project Structure**  

bare-metal-project/ │-- Core/ │ ├── Inc/ # Header files │ ├── Src/ # Source files │ ├── startup/ # Startup code and linker scripts │ ├── system/ # System initialization and configuration │-- Drivers/ # Custom peripheral drivers │-- Docs/ # Documentation and reference materials │-- Makefile # Build automation │-- README.md # Project documentation │-- main.c # Main application code

markdown
Copy
Edit

## **Getting Started**  

### **Prerequisites**  
Ensure you have the following tools installed:  
- **ARM GCC Toolchain** – For compiling the code  
- **STM32CubeProgrammer** – For flashing the microcontroller  
- **OpenOCD** – For debugging  
- **A debugger** – Such as ST-LINK/V2  

### **Building the Project**  
To compile the project, run:  
```bash
make all
Flashing the Microcontroller
Upload the binary to the STM32 microcontroller using:

bash
Copy
Edit
make flash
Debugging
Use GDB and OpenOCD for debugging with:

bash
Copy
Edit
make debug
Code Highlights
GPIO Initialization (Example Code)
c
Copy
Edit
void gpio_init(void) {
    RCC->AHB1ENR |= (1 << 0); // Enable GPIOA clock
    GPIOA->MODER |= (1 << 10); // Set PA5 as output
}
USART Transmission (Example Code)
c
Copy
Edit
void usart_send_char(char c) {
    while (!(USART1->SR & (1 << 7))); // Wait for TXE flag
    USART1->DR = c; // Send character
}
Challenges Faced
Understanding the ARM Cortex-M4 architecture
Implementing custom ISRs with minimal latency
Optimizing peripheral access without HAL libraries
Future Improvements
Adding RTOS for multitasking capabilities
Implementing power management features
Extending the project to include sensor interfacing and data logging
References
CMSIS Documentation
STM32 Reference Manual
Contributing
Contributions are welcome! Feel free to submit issues or pull requests to enhance the project.

License
This project is licensed under the MIT License.
