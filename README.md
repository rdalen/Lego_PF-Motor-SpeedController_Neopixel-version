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

This [design](/docs/Lego%20PF%20Motor%20speed%20controller%20with%20Neopixel%20-%20Schematic.pdf) is based on an Arduino ProMini (or clone) and has a DRV8833 Motor driver module, a Rotary encoder and a 16 LED Neopixel Ring as forward/reverse speedindicator  
![Image](https://github.com/user-attachments/assets/53ff555d-a833-40cc-8e04-70d34815b413)



### The PCB (v1.0)
The pcb design takes into account the footprint of the different MCU modules, however only 1 of the MCU modules needs to be placed.  
![Image](https://github.com/user-attachments/assets/7c215320-499c-41ac-976d-e5720ad172ec)  

I ordered the pcb's at JLCPCB
![Image](https://github.com/user-attachments/assets/d91549f5-1c7f-4ae1-9b96-8a0b97472900)

And this is what it looks like when assembled
![Image](https://github.com/user-attachments/assets/a1ad2bc3-2896-4e92-b623-1acb0c6bc26c)
See [here](https://youtube.com/shorts/omxZtgw-2hw) how it works.  

The PCB 1.0 has this [issue #1](https://github.com/rdalen/Lego_PF-Motor-SpeedController_Neopixel-version/issues/1).  
This is fixed in [v1.1](https://github.com/rdalen/Lego_PF-Motor-SpeedController_Neopixel-version/blob/main/src/KiCad9.0/Lego%20PF-Motor%20PWM%20Speedcontroller%20-%20Neopixel%20version-v1.1.zip)
___
The Lego Speed Controller can be powered by the Lego Battery Box or by an external 9Vdc power adapter.   

Before assembling the Input PF cable (connected to J11 in the schematic), removed first the C1 and C2 contacts from the Bottom part of the connector so that this connector can be used to connect both the battery box (via the 0V and 9V contacts in the BOTTOM part) as the Lego PF-motor as well (via the C1 and C2 contacts in the TOP part).  
![Image](https://github.com/user-attachments/assets/0d40d8c7-a8f0-4172-9ac3-674145432b49)  
The output PF cable (connected to J13 in the schematic) is not modified (so has all its contacts)  
