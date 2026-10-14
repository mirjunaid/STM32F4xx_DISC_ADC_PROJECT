# Bare-Metal STM32F407 Data Acquisition & Telemetry Pipeline

A modular, high-reliability embedded firmware pipeline developed from scratch in bare-metal C for the **STM32F407G-DISC1** board (ARM Cortex-M4) 

This project interfaces with an analog **KY-013 NTC Temperature Sensor** via direct hardware register manipulation—completely bypassing vendor HAL and LL libraries. It implements non-blocking hardware timekeeping, time-windowed moving average downsampling, and an atomic single-producer single-consumer (SPSC) ring buffer.

---

## Architecture Overview

The system follows a strict 3-layer architecture to ensure modularity, memory safety, and complete decoupling of hardware peripherals from data processing logic:

```text
┌────────────────────────────────────────────────────────┐
│                   Application Layer                    │
│                        (main.c)                        │
│   • Boot sequence, LED indicators (PD12)               │
│   • Acquisition loop & non-blocking execution pacing   │
└──────────────────────────┬─────────────────────────────┘
                           │
┌──────────────────────────▼─────────────────────────────┐
│               Middleware / Service Layer               │
│                     (telemetry.c)                      │
│   • 64-bit online running accumulator (adc_sum)        │
│   • Configurable time-window averaging (e.g., 10 min)  │
│   • Lock-free SPSC 16-bit Ring Buffer storage          │
└──────────────────────────┬─────────────────────────────┘
                           │
┌──────────────────────────▼─────────────────────────────┐
│             Low-Level Hardware Drivers                 │
│                 (ADC.c, systick.c)                     │
│   • Direct register access (MODER, SQR, CR2, SR, DR)   │
│   • SysTick core timer configuration & 1 ms heartbeat  │
└────────────────────────────────────────────────────────┘

Key Features
 * Direct Register-Level Drivers (No HAL): Full manual configuration of RCC clock gating, GPIO analog modes (MODER), ADC sequence and control registers (ADC_SQRx, ADC_CR2), and core registers (SysTick->CTRL, LOAD, VAL).
 * Lock-Free SPSC Ring Buffer: Fast, thread-safe circular FIFO queue storing uint16_t 12-bit ADC counts. Utilizes bitwise index wrapping (RING_BUFFER_SIZE - 1) and compiler memory fences (__atomic_signal_fence) to prevent race conditions without disabling interrupts.
 * Time-Windowed Data Decimation: Features an online accumulator (uint64_t adc_sum and uint32_t sample_count) that downsamples thousands of raw readings into deterministic time-averaged windows (e.g., 5 seconds for test/debug, 10 to 30 minutes for long-term logging).
 * Zero Floating-Point Overhead: Stores calibrated raw 12-bit counts directly in memory. This eliminates costly software floating-point conversions, prevents rounding truncation, and preserves original signal fidelity for backend post-processing.
 * Fixed-Point DSP Utilities: Includes an auxiliary library for Q16.16 fixed-point arithmetic (q16_add, q16_mul, q16_div) and Exponential Moving Average (EMA) filtering.
Hardware Configuration
| Component | Pin / Channel | Configuration / Notes |
|---|---|---|
| STM32F407G-DISC1 | — | Core running on default 16 MHz HSI |
| KY-013 Analog Sensor | PA1 (ADC1_IN1) | Configured in GPIO Analog Mode (0x3 << 2) |
| System Status LED | PD12 (Green) | General Purpose Output (asserted upon boot) |
| Auxiliary Output | PD13 (Orange) | General Purpose Output |
Repository Structure
The project is organized into modular layers located under Ext_Drivers:
├── Ext_Drivers/
│   ├── Inc/
│   │   ├── ADC.h           # ADC1 peripheral macros, clock enables, and prototypes
│   │   ├── ring_buffer.h   # SPSC ring buffer definitions and Q16.16 math types
│   │   ├── systick.h       # SysTick timebase and millisecond delay prototypes
│   │   └── telemetry.h     # Downsampling accumulator and telemetry interface
│   └── Src/
│       ├── ADC.c           # Register-level ADC initialization and polling read
│       ├── ring_buffer.c   # Atomic push/pop buffer implementation and fixed-point math
│       ├── systick.c       # SysTick core timer configuration and ISR handler
│       └── telemetry.c     # Windowed averaging engine and ring buffer instantiation[span_13](start_span)[span_13](end_span)
├── Inc/
├── Src/
│   ├── main.c              # Application entry point and scheduler loop[span_14](start_span)[span_14](end_span)[span_15](start_span)[span_15](end_span)
│   ├── syscalls.c[span_16](start_span)[span_16](end_span)
│   └── sysmem.c[span_17](start_span)[span_17](end_span)
├── Startup/                # Vector table and startup assembly[span_18](start_span)[span_18](end_span)
├── STM32F407VGTX_FLASH.ld  # GNU LD Flash linker script[span_19](start_span)[span_19](end_span)
└── README.md

Verification & Debugging
The pipeline has been validated over SWD using GDB and Live Expressions inside STM32CubeIDE:
 * raw: Tracks real-time 12-bit ADC counts from the KY-013 thermistor.
 * adc_rb.head: Verifiably increments each time an averaging window completes, advancing sequential writes.
 * adc_rb.buffer: Inspectable memory array verifying that downsampled mean values are stored accurately without type truncation.
 * g_system_ticks: Continuously updates via the internal SysTick_Handler ISR to guarantee non-blocking interval timing.
Getting Started
Prerequisites
 * Toolchain: arm-none-eabi-gcc
 * IDE / Debugger: STM32CubeIDE / GDB / OpenOCD
 * Hardware: STM32F4-Discovery (STM32F407VGT6) and KY-013 Analog Temperature Sensor
Build & Flash
 * Clone the repository into your local workspace:
   git clone https://github.com/mirjunaid/STM32F4xx_DISC_ADC_PROJECT.git

 * Open the project in STM32CubeIDE.
 * Build the project using the Debug configuration (Release optional).
 * Connect your discovery board via the ST-LINK Mini-USB port and click Debug (F11).
 * Add raw, adc_rb.head, and adc_rb.buffer to the Live Expressions pane to monitor acquisition in real time.
