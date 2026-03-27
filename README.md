simavr - A Lean and Mean Atmel AVR Simulator
=============================================

_simavr_ is a high-performance AVR simulator for Linux or any platform using avr-gcc.
 It is designed to be small, compact, and hackable, allowing for rapid prototyping and firmware validation.

The original repository is from /buserror.

**Note:** This version of _simavr_ has been modernized to use the **Meson** build system and includes custom auditing tools for peripheral exploration.

Key Features
------------
* ELF Loading: Loads ELF files directly, including .elf sections for simulation parameters.
* VCD Support: Built-in logic analyzer that generates .vcd files for visualization in gtkwave.
* GDB Support: Fully working GDB bridge for interactive debugging.
* Extensible: Extremely easy to add new MCU cores and custom peripherals.

Installation & Building
-----------------------
This project uses the Meson build system for fast, reliable builds.

1. Prerequisites
Ensure you have meson, ninja, and libelf installed:

    sudo apt-get install meson ninja-build libelf-dev

2. Compile

    meson setup builddir
    meson compile -C builddir

3. Run Tests
Validate the core library and tools:

    meson test -C builddir

Internal Hardware Auditing (avr-probe)
----------------------------------------
I have included a specialized tool, avr-probe, to explore the internal "hooks" of any simulated MCU. Use this to find available IRQs, Timers, and Ports before writing your bridge code.

    # List all supported cores
    ./builddir/avr-probe --list

    # Find all MCUs with USB support
    ./builddir/avr-probe --search usb

    # Audit a specific MCU (e.g., ATtiny4313)
    ./builddir/avr-probe -m attiny4313

Supported IOs
--------------
* EEPROM & Watchdog
* IO Ports (including pin interrupts)
* Timers (8 & 16-bit, PWM, CTC, Overflow)
* UART (including TX/RX interrupts and loopback)
* SPI & I2C (Master/Slave)
* ADC & Analog Comparators
* USB (on supported chips like AT90USB162)

Emulated Cores
--------------
The simulator supports a vast range of cores, searchable via avr-probe --list. Highlights include:
* Mega: 2560, 1280, 128, 328p, 168, 88, 48, 32, 16, 8
* Tiny: 2313a, 4313, 85, 45, 25, 13a, 44, 84
* Specialty: AT90USB162, ATMega128RFA1 (Wireless)

Contributing
------------
Patches and new core definitions are always welcome! Please submit your changes via Github pull requests.

