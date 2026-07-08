--- July 4th, 2026 --- 
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
1. Design the housing in CAD to abstract all of the electronics

--- July 5th, 2026 ---
Learnt about AC and DC voltage in capacitors and inductors. Shamefully it genuinely took the whole day and I’m not sure why. I think it’s because I really didn’t understand any of it and still kind of don’t fully. Did not decide to post anything today because I was embarrassed that I cooked my brain trying to learn simple electronics and didn’t have anything tangible to show for it so I’m instead just logging it here. I’m going to post tomorrow on LinkedIn no matter what and complete the signal conditioning tomorrow. Will post on both LinkedIn and Instagram.
I have to remember that I don’t need to know everything all at once and I just need to know enough and build on that learning. I can’t waste more full days like this since I’m on a time crunch.

--- July 6th, 2026 ---
1st attempt at the analog front end circuit: - 11:52 PM

2nd attempt
Changes made:
-> Added an op amp (buffer configuration) after the AC coupling (using the capacitor) to procure the signal easily. 
-> Modified the voltage divider resistors to use much less current and realized as long as you use 2 of the same resistors you can half the reference voltage. Starting to better understand this relationship of current-voltage and how it operates in the microcontroller and in a circuit. Switched from 1.65K to 10K resistors.

3rd Attempt: 
Added resistors in front of the diodes 
And switched over to LT_Spice to test the circuit:

4th attempt: 
Added a capacitor
10th attempt: 
Incorrectly added a voltage divider and realized all I’m doing is measuring the AC noise around DC signals since all circuits are DC signals.

--- July 7th, 2026 ---
Remade the project plan and completely simplified the circuit since all I’m doing is measuring the voltage whether it’s AC or DC doesn’t matter. The real challenge will be implementing the signal image scaling.

P1: Analog Front End
1.	Measure signals without probes acting as heavy loads on the source (high input impedance buffering).
2.	Protect ADC pins from voltages outside 0–3.3V after signal conditioning (clamping diodes).
3.	(Optional/stretch) Variable gain stage for volts/div control, either via a potentiometer in the op-amp feedback path or via software scaling based on a pot read through a spare ADC channel.
P2: Data Acquisition
1.	Use DMA to store the acquired signal instead of relying on the CPU for each sample.
2.	Implement a trigger (e.g., edge-detect at a threshold voltage) to determine when to start/stop capturing data.
3.	Implement time/div control by reading a potentiometer via ADC and mapping its value to sample rate/capture window length.
P3: Frame Buffers for LCD Pixels
1.	Allocate a complete screen array in memory on the microcontroller to represent display pixels.
P4: Displaying the Waveform
1.	Transmit each framebuffer instance over SPI using a second DMA channel, offloading transmission from the CPU.
2.	Apply volts/div scaling (software-based, using potentiometer input), when rendering the captured samples to the framebuffer.
P5: Project Housing
1.	Design a CAD housing to enclose and abstract all electronics in a PCB or protoboard based on project timeline.

-> Finalized the circuit needed for measuring signal votlages and cleaned it up. Also tested for measuring DC, AC and PWM signals. 


