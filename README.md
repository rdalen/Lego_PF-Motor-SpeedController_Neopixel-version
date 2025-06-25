## Lego Power Function (PF) Motor speed controller with a 16 LED Neopixel Ring and a Rotary encoder

Inspired by the good old conventional Lego train speed regulator (2868), I made this design for controlling Lego PF Motors. It is based on an Arduino ProMini (or clone) and has a DRV8833 Motor driver module, a Rotary encoder and a 16 LED Neopixel Ring as forward/reverse speedindicator.
![Image](https://github.com/user-attachments/assets/080438ce-71e4-45de-afbd-547af4345155)

The conventional train regulator gives a analog 0-9V output signal. In this design, the PF motor is controlled with a Pulse Width Modulation (PWM) output signal. This means that the motor speed is controlled by varying the duty cycle of a square wave signal.

Earlier I made [another version](https://github.com/rdalen/Lego_PF-Motor-SpeedController) of a Lego speed controller based on the well known NE555 timer-IC. 

For the MCU modules both the Arduino ProMini and the [LGT8F328P LQFP32 MiniEVB](https://wolles-elektronikkiste.de/en/minievb-boards-an-overview) (Pro Mini Style) can be used or even the [LGT8F328P SSOP20 MiniEVB](https://wolles-elektronikkiste.de/en/minievb-boards-an-overview) (pseudo Pro Mini Style).  
![Image](https://github.com/user-attachments/assets/0f129618-70d6-4ebd-975c-3ff58fa520ff)  

You can buy the LGT8F328P MiniEVB modules on AliExpress very cheap.  
I used the 5V version, because not all types of Neopixels are compatible with 3V3.  
Furthermore, I use, among other things;  
- A DRV8833 Motor driver module  
- A Neopixel ring with 16 LEDs  
- An EC11 Rotary encoder with push button  
![Image](https://github.com/user-attachments/assets/06701ed0-27e3-411e-9106-8a072cb2fcc8)

### The Design
The [design](/docs/Lego%20PF%20Motor%20speed%20controller%20with%20Neopixel%20-%20Schematic.pdf) is made in KiCad 9.0 and is straight forward.  
It can be powered by, for example, a 9V Lego battery box (8881) or by an external 9Vdc power adapter.  
I first tested it in a breadboard setup.  
![Image](https://github.com/user-attachments/assets/53ff555d-a833-40cc-8e04-70d34815b413)

### The PCB (v1.0)
I designed a 76x100mm PCB, which I ordered from JLCPCB. 
![Image](https://github.com/user-attachments/assets/d91549f5-1c7f-4ae1-9b96-8a0b97472900)

The pcb design takes into account the footprint of the different MCU modules, however only 1 of the MCU modules needs to be placed.  
![Image](https://github.com/user-attachments/assets/7c215320-499c-41ac-976d-e5720ad172ec)  

The PCB 1.0 has this [issue #1](https://github.com/rdalen/Lego_PF-Motor-SpeedController_Neopixel-version/issues/1).  
This is fixed in [v1.1](https://github.com/rdalen/Lego_PF-Motor-SpeedController_Neopixel-version/blob/main/src/KiCad9.0/Lego%20PF-Motor%20PWM%20Speedcontroller%20-%20Neopixel%20version-v1.1.zip)

### The DIY PF Cable
On AliExpress you can buy PF connectors and 4 core wire and make your own Lego PF connection cables.
Before assembling the Input PF cable (connected to J11 in the schematic), I removed the C1 and C2 contacts from the Bottom part of the connector so that this connector can be used to connect both the battery box (via the 0V and 9V contacts in the BOTTOM part) as the Lego PF-motor as well (via the C1 and C2 contacts in the TOP part).  
![Image](https://github.com/user-attachments/assets/0d40d8c7-a8f0-4172-9ac3-674145432b49)  
The output PF cable (connected to J13 in the schematic) is not modified (so has all its contacts).
So the PF-motor can be connected or to the input connector (connected to the Battery box) or to the output connector.  

See [this article](https://www.philohome.com/pf/pf.htm) about the working of de LEGO Power Function cable.

### The Programming

To upload the sketch from your computer into the Arduino board you will need a FTDI USB to TTL Adapter.  
![Image](https://github.com/user-attachments/assets/b041cc7b-5861-4736-9400-6b8c63063f8f)

Then;  
1 - Install the following libraries:  
  - lgt8fx library (When you use a LGT8F328P MiniEVB Board)  
  - Neopixel library  
  - Rotary library  
2 - Download the sketch (You can also download the the sketch from my github)  
3 - Set the proper board settings (see picture for the LGT8F328P board settings) and upload the sketch

For clarification;
- The Neopixel ring indicates the output signal (similar to the big yellow button on the conventional Lego train speed regulator).  
- Turning the Rotary encoder knob to the right wll increase the speed in forward direction (Green color), turning to the left will decrease the speed to 0 (LED8 is the center of the indication scale) and then increases the speed in reverse direction (Red color).  
- Neopixel LED0 is set to blue as power-on indication. 
- When your Rotary encoder is equipped with a push button; a short button press will increase the brightness of the LEDs (in 9 steps) and a long button press (>2sec) will reset the brightness to the default 10% and set the speed to 0 (Stop).  

### The Result
And this is what it looks like when assembled
![Image](https://github.com/user-attachments/assets/a1ad2bc3-2896-4e92-b623-1acb0c6bc26c)
See [here](https://youtube.com/shorts/omxZtgw-2hw) how it works.  


___


