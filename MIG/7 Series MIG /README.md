# IP MIG 7 Series

The practical work is focused on testing and verifying the operation of DDR memory on the Arty S7 FPGA board (Xilinx 7 Series).

The main goals and content of the work include:

    Verifying that the DDR memory installed on the board actually works.

    Learning how to configure and set up the DDR interface using the MIG IP core.

    Running and using the provided SDK Memory Tests application for basic DDR testing.

    Gaining practical experience creating a project in Vivado, setting up a Block Design, and integrating the DDR controller.

For this, we’ll need several other IP blocks — let’s briefly go over them.

## Processor System Reset

This is a special IP block from Xilinx designed for reliable reset signal management (reset) — especially when using processors (like MicroBlaze or Zynq), DDR, AXI peripherals, or multiple clock domains.

One (proc_sys_reset_0) for MicroBlaze, the other(rst_mig_7series_0_81M) for MIG.

For more information on how it works, you can refer to the 
### Processor System Reset Module v5.0 Product Guide (PG164).

![Example of the Processor System Reset Module Core](rst.png)

## Clocking Wizard v6.0

Clocking Wizard v6.0 is an IP core from Xilinx that:

Allows you to generate one or more clock signals from a single input clock (e.g., an external 100 MHz source).

Utilizes MMCM or PLL resources inside the FPGA.

Supports:

    Frequency, phase, and duty cycle configuration for each output.

    Clock buffering (BUFG) and control over reset/enable.

    An optional Phase Alignment feature for precise synchronization.

Can be used to create clocks for logic, memory (MIG), interfaces (AXI), processors (like MicroBlaze), and other subsystems.

This is a fairly complex IP block and should be studied separately.

For detailed information, refer to the 
### Clocking Wizard LogiCORE IP Product Guide (PG065).

## MicroBlaze

A programmable 32-bit soft-core CPU developed by Xilinx, implemented entirely in FPGA logic. It follows a RISC architecture, supports AXI interfaces, 
and can be customized to meet specific project requirements.

Related to it:

    Debug module for MicroBlaze Soft Processor
    A module that enables debugging features for the MicroBlaze processor (e.g., breakpoints, stepping, memory inspection via JTAG).

    microblaze_0_local_memory
    A local memory block (usually implemented using BRAM) that serves as internal memory directly connected to the MicroBlaze core for fast access.

### We will cover this IP block in a separate topic.

## AXI Interconnect 

The AXI Interconnect IP connects one or more AXI memory-mapped master devices to one or more AXI memory-mapped slave devices. It manages data flow, addressing, and arbitration between masters and slaves in an AXI-based system.

### We will also cover it in the topic on the AXI interface.

## UART for AXI Interface

    UART is a standard serial communication protocol (asynchronous, with start/stop bits, etc.).

    A Generic UART with an AXI interface is a hardware module that implements this UART protocol at the physical data transmission and reception level.

    The AXI interface is used for interaction with the processor or logic inside the FPGA — through the AXI bus, the processor reads and writes UART registers (such as transmit and receive buffers, baud rate settings, status registers).

In other words, the UART protocol runs externally on the UART lines, while inside the FPGA the module is controlled via AXI.
Why is UART needed in a DDR project on FPGA?

    Debugging and monitoring

    Data exchange with a PC

    Control and configuration

    Interface for user applications

## Memory Interface Generator

This Memory Interface Generator is a simple menu driven tool to generate advanced memory interfaces. This tool generates HDL and pin placement constraints that will help you design your application. Kintex-7 supports DDR3 SDRAM, DDR2 SDRAM, LPDDR2 SDRAM, QDR II+ SRAM, RLDRAMII and RLDRAMIII. Virtex-7 supports DDR3 SDRAM, DDR2 SDRAM, LPDDR2 SDRAM, QDR II+ SRAM, RLDRAMII and RLDRAMIII. Artix-7 supports DDR3 SDRAM, DDR2 SDRAM and LPDDR2 SDRAM. Zynq supports DDR3 SDRAM, DDR2 SDRAM and LPDDR2 SDRAM

Briefly about the internal settings:



Here is what our completed block design looks like:

![Block Design](block_design.png)