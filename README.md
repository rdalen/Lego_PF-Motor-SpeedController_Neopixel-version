## Lego Power Function (PF) Motor speed controller with a 16 LED Neopixel Ring and a Rotary encoder

Earlier I made [this version](https://github.com/rdalen/Lego_PF-Motor-SpeedController) of a Lego speedcontroller based on the well known NE555 timer-IC.  

This [design](/docs/Lego%20PF%20Motor%20speed%20controller%20with%20Neopixel%20-%20Schematic.pdf) is based on an Arduino ProMini (or clone) and has a DRV8833 Motor driver module, a Rotary encoder and a 16 LED Neopixel Ring as forward/reverse speedindicator  
![Image](https://github.com/user-attachments/assets/53ff555d-a833-40cc-8e04-70d34815b413)

For the MCU modules both the Arduino ProMini and the [LGT8F328P LQFP32 MiniEVB](https://wolles-elektronikkiste.de/en/minievb-boards-an-overview) (Pro Mini Style) can be used or even the [LGT8F328P SSOP20 MiniEVB](https://wolles-elektronikkiste.de/en/minievb-boards-an-overview) (pseudo Pro Mini Style).  
![Image](https://github.com/user-attachments/assets/92f046ee-78c8-42a8-b996-337eff9ab6af)

### The PCB
The pcb design takes into account the footprint of the different MCU modules, however only 1 of the MCU modules needs to be placed.  
![Image](https://github.com/user-attachments/assets/7c215320-499c-41ac-976d-e5720ad172ec)  

I ordered the pcb's at JLCPCB
![Image](https://github.com/user-attachments/assets/d91549f5-1c7f-4ae1-9b96-8a0b97472900)

And this is what it looks like when assembled
![Image](https://github.com/user-attachments/assets/a1ad2bc3-2896-4e92-b623-1acb0c6bc26c)
See [here](https://youtube.com/shorts/omxZtgw-2hw) how it works.  

On AliExpress you can buy the PF connector and wire to make a DIY Lego PF connection cable.  
When assembling the PF cable, remove the C1 and C2 contacts from the Bottom part of the connector
so that only 1 connector is required to connect both the battery box and the motor
![Image](https://github.com/user-attachments/assets/0d40d8c7-a8f0-4172-9ac3-674145432b49)
