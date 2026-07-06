July 4th, 2026: 
Turning the signal displayer into a working oscilloscope to measure signals between 0-3.3V.
Design Specifications:
Technical Specs: 
•	Bandwidth: 100kHz
•	Sampling Rate: (1 MSPS) -> Sampling at 1 million Samples per second
•	(SRAM) Memory Allocation: 
o	Framebuffer: 40 KB of space -> 128*160 * 2 bytes ≈ 40KB
o	Sample Buffer (Sampled ADC values) :160 * 2 bytes ≈ 320 Bytes
o	Remaining SRAM: ≈ 55 KB
•	Input Range: 0-3.3V (Possible Extension : Measuring –(ve) Voltages)
There are 3 phases of the project to complete:
P1: Analog Front End
1. Being able to measure signals without the probes working as conductors and loading the microcontroller. 
2. Some form of protection to the ADC pins from anything outside of the desired range of 0-3.3V after the signal is conditioned.
P2: Data Acquisition 
1. Using DMA to store the acquired signal instead of the CPU.
2. Implement some sort of trigger, to know when to start and stop collecting data, not sure how to do this ? 
P3: Using Frame Buffers to display pixels on the LCD 
1. Using the new microcontroller to allocate a complete screen array in memory.
P4: Displaying the Waveform 
1. Transmit each instance of the framebuffer over SPI using the second DMA channel so the CPU doesn’t have to deal with transmission. 
P5: Project Housing 
