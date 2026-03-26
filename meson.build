project('simavr', 'c', version: '1.7')

cc = meson.get_compiler('c')
elf_dep = cc.find_library('elf', required: true)
m_dep = cc.find_library('m', required: true)

# Include directories based on your tree
# Note: we add 'simavr' to the path because that's where the .h files live
sim_inc = include_directories('simavr/sim', 'simavr/cores')

simavr_sources = files(
    # Core Engine (from simavr/sim/)
    'simavr/sim/sim_avr.c',
    'simavr/sim/sim_elf.c',
    'simavr/sim/sim_core.c',
    'simavr/sim/sim_hex.c',
    'simavr/sim/sim_irq.c',
    'simavr/sim/sim_interrupts.c', # Fixed name from tree
    'simavr/sim/sim_io.c',
    'simavr/sim/sim_utils.c',
    'simavr/sim/sim_cycle_timers.c',
    'simavr/sim/sim_gdb.c',
    'simavr/sim/sim_vcd_file.c',

    # Standard Peripherals (from simavr/sim/)
    'simavr/sim/avr_ioport.c',
    'simavr/sim/avr_uart.c',
    'simavr/sim/avr_timer.c',
    'simavr/sim/avr_adc.c',
    'simavr/sim/avr_spi.c',
    'simavr/sim/avr_twi.c',
    'simavr/sim/avr_eeprom.c',
    'simavr/sim/avr_watchdog.c',
    'simavr/sim/avr_extint.c',
    'simavr/sim/avr_acomp.c',
    'simavr/sim/avr_flash.c',
    'simavr/sim/avr_bitbang.c',

    # MCU Cores (from simavr/cores/)
    'simavr/cores/sim_megax8.c', # ATmega328P and brothers
    'simavr/cores/sim_tinyx5.c', # ATtiny85 and brothers
    'simavr/cores/sim_megax4.c', # ATmega644 etc
    'simavr/cores/sim_mega128.c'
)

# Build as a static library
libsimavr = static_library('simavr',
    simavr_sources,
    include_directories: sim_inc,
    dependencies: [elf_dep, m_dep],
    c_args: [
        '-D_GNU_SOURCE',
        '-Wno-unused-result', # simavr can be chatty with warnings
    ]
)

# Export the dependency for AVR-labs
simavr_dep = declare_dependency(
    link_with: libsimavr,
    include_directories: sim_inc
)
