# ARM Cortex-M4 SysTick & NVIC Drivers

Bare-metal **SysTick and NVIC drivers** implemented in Embedded C for the **TM4C123GH6PM (Tiva-C)** ARM Cortex-M4F microcontroller.

The project focuses on register-level programming of Cortex-M core peripherals, interrupt configuration, exception priorities, and timer-based functionality without relying on high-level peripheral libraries.

## Target Platform

**MCU:** TM4C123GH6PM
**Core:** ARM Cortex-M4F
**Language:** C
**Development Environment:** Code Composer Studio

## NVIC Driver

The NVIC driver provides interfaces for configuring external interrupts and system exceptions.

### Implemented APIs

| API                           | Purpose                                             |
| ----------------------------- | --------------------------------------------------- |
| `NVIC_EnableIRQ()`            | Enables an external interrupt request               |
| `NVIC_DisableIRQ()`           | Disables an external interrupt request              |
| `NVIC_SetPriorityIRQ()`       | Configures an external interrupt priority           |
| `NVIC_EnableException()`      | Enables supported configurable system exceptions    |
| `NVIC_DisableException()`     | Disables supported configurable system exceptions   |
| `NVIC_SetPriorityException()` | Configures programmable system-exception priorities |

The driver directly accesses Cortex-M NVIC and system-handler registers using memory-mapped register definitions.

## SysTick Driver

The SysTick driver provides timer and interrupt functionality using the Cortex-M SysTick peripheral.

### Implemented APIs

| API                       | Purpose                                                 |
| ------------------------- | ------------------------------------------------------- |
| `SysTick_Init()`          | Configures SysTick for a specified time interval        |
| `SysTick_StartBusyWait()` | Generates a blocking delay using SysTick                |
| `SysTick_SetCallBack()`   | Registers an application callback                       |
| `SysTick_Handler()`       | Executes the configured callback on a SysTick interrupt |
| `SysTick_Start()`         | Starts the SysTick timer                                |
| `SysTick_Stop()`          | Stops the SysTick timer                                 |
| `SysTick_DeInit()`        | Resets the SysTick configuration                        |

## Interrupt-Driven Operation

The SysTick driver supports callback-based application execution.

```text
SysTick Counter
      │
      ▼
SysTick Interrupt
      │
      ▼
SysTick_Handler()
      │
      ▼
Application Callback
```

This separates the timer interrupt handling from application-specific functionality.

## Repository Structure

```text
ARM-Cortex-M4-SysTick-NVIC-Drivers/
├── nvic.c
├── nvic.h
├── systick.c
├── systick.h
├── tm4c123gh6pm_registers.h
├── tm4c123gh6pm_startup_ccs.c
├── std_types.h
├── main.c
├── targetConfigs/
└── tm4c123gh6pm.cmd
```

## Concepts Applied

* ARM Cortex-M4 architecture
* Bare-metal Embedded C
* Memory-mapped register access
* Nested Vectored Interrupt Controller (NVIC)
* Interrupt enable/disable control
* Interrupt and exception priorities
* Cortex-M system exceptions
* SysTick timer configuration
* Interrupt handlers and callbacks
* Busy-wait timing
* Bit masking and register manipulation

## Build Environment

The project was developed using **Code Composer Studio** for the TM4C123GH6PM platform.

To inspect or build the project:

1. Clone the repository.
2. Import it as an existing CCS project.
3. Select the TM4C123GH6PM target configuration.
4. Build the project.

## Purpose

This project was developed to strengthen practical understanding of **ARM Cortex-M core peripherals, interrupt architecture, register-level programming, and low-level driver development**.

## Development Scope and Attribution

This project was completed as part of ARM architecture training instructed by **Mohamed Tarek — Edges for Training**.

The course provided starter/template files and function prototypes for selected modules.

My work focused on implementing the **NVIC and SysTick driver functionality**, including:

- External interrupt enable/disable control
- Interrupt priority configuration
- System-exception priority configuration
- SysTick initialization and timing
- Callback-based interrupt handling
- Busy-wait timing
- Start/stop/de-initialization functionality
- Register-level driver implementation for the TM4C123GH6PM

Template/source files originating from the course retain their original attribution.