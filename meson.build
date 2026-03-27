project('simavr', 'c', version: '1.7')

cc = meson.get_compiler('c')
elf_dep = cc.find_library('elf', required: true)
m_dep = cc.find_library('m', required: true)

# Include directories based on your tree
sim_inc = include_directories('simavr/sim', 'simavr/cores')

simavr_sources = files(
    # Core Engine (from simavr/sim/)
    'simavr/sim/sim_avr.c',
    'simavr/sim/sim_elf.c',
    'simavr/sim/sim_core.c',
    'simavr/sim/sim_hex.c',
    'simavr/sim/sim_irq.c',
    'simavr/sim/sim_interrupts.c', 
    'simavr/sim/sim_io.c',
    'simavr/sim/sim_utils.c',
    'simavr/sim/sim_cycle_timers.c',
    'simavr/sim/sim_gdb.c',
    'simavr/sim/sim_vcd_file.c',
    'simavr/sim/sim_cmds.c',

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
    'simavr/sim/avr_usb.c',
    'simavr/sim/avr_usi.c',
    'simavr/sim/avr_lin.c',
)

# MCU Core source files
mcu_sources = files(
    'simavr/cores/sim_mega1280.c',
    'simavr/cores/sim_mega1281.c',
    'simavr/cores/sim_mega1284.c',
    'simavr/cores/sim_mega128.c',
    'simavr/cores/sim_mega128rfa1.c',
    'simavr/cores/sim_mega128rfr2.c',
    'simavr/cores/sim_mega164.c',
    'simavr/cores/sim_mega168.c',
    'simavr/cores/sim_mega169.c',
    'simavr/cores/sim_mega16.c',
    'simavr/cores/sim_mega16m1.c',
    'simavr/cores/sim_mega2560.c',
    'simavr/cores/sim_mega324a.c',
    'simavr/cores/sim_mega328.c',
    'simavr/cores/sim_mega328pb.c',
    'simavr/cores/sim_mega32.c',
    'simavr/cores/sim_mega32u4.c',
    'simavr/cores/sim_mega48.c',
    'simavr/cores/sim_mega644.c',
    'simavr/cores/sim_mega64m1.c',
    'simavr/cores/sim_mega88.c',
    'simavr/cores/sim_mega8.c',
    'simavr/cores/sim_megax4.c',
    'simavr/cores/sim_megax8.c',
    'simavr/cores/sim_megax.c',
    'simavr/cores/sim_megaxm1.c',
    'simavr/cores/sim_tiny13.c',
    'simavr/cores/sim_tiny1634.c',
    'simavr/cores/sim_tiny2313a.c',
    'simavr/cores/sim_tiny2313.c',
    'simavr/cores/sim_tiny24.c',
    'simavr/cores/sim_tiny25.c',
    'simavr/cores/sim_tiny4313.c',
    'simavr/cores/sim_tiny44.c',
    'simavr/cores/sim_tiny45.c',
    'simavr/cores/sim_tiny84.c',
    'simavr/cores/sim_tiny85.c',
    'simavr/cores/sim_tinyx4.c',
    'simavr/cores/sim_tinyx5.c',
    'simavr/cores/sim_usb162.c'
)

# Build as a static library
libsimavr = static_library('simavr',
    [simavr_sources, mcu_sources],
    include_directories: sim_inc,
    dependencies: [elf_dep, m_dep],
    c_args: [
        '-D_GNU_SOURCE',
        '-Wno-unused-result',
        '-DAVR_COMMAND_FREE_UNUSED=1', # Might enable command logic in sim_core
    ]
)

# 1. First, make sure we have the dependency handle
simavr_dep = declare_dependency(
    include_directories : sim_inc,
    link_with : libsimavr
)

# 2. Define the tool in the 'tools' subdirectory
avr_probe_bin = executable(
    'avr-probe',
    'tools/avr-probe.c',            # Path to your renamed file
    dependencies : simavr_dep,      # Links to the library
    include_directories : sim_inc,      # Ensures headers are found
    install : true
)

# Optional: Register it as a formal Meson test
test('core_listing_test', avr_probe_bin, args: ['--list'])
test('audit_tiny2313', avr_probe_bin, args: ['--mcu', 'attiny2313a'])
test('search_usb_feature', avr_probe_bin, args: ['--search', 'usb'])
test('help_menu_check', avr_probe_bin, args: ['--help'])

