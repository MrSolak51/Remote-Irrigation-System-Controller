# Remote-Irrigation-System-Controller
A Controller for control the irrigation system.


Okay, so for this project we need to make 2 modules. 
The first module will replace the LAY5-BE101 that controls the irrigation system.

![LAY5-BE101](https://github.com/user-attachments/assets/cff31701-b1bd-4442-8fcb-e816658425cf)

Our second module will allow us to manage this controller remotely.
The irrigation controller we will control is GD100-2G2G-S2-PV, 
![GD100-2G2G-S2-PV](https://github.com/user-attachments/assets/38c85dce-1bd1-4547-8f3e-d5fa45853b20) ![GD100-2G2G-S2-PV(2)](https://github.com/user-attachments/assets/86860fce-3005-4b87-a648-20922da0b86c)

A device that provides excessive voltage for the Arduino. Therefore, we'll use a voltage reducer and reduce the 24V voltage to 5V. This way, the Arduino won't burn out.

![XL4015](https://github.com/user-attachments/assets/cf492f50-4085-4474-97e7-b14243b70070)

The Arduino pins can only provide 5V voltage. This is quite insufficient for triggering. To solve this, we will use an SSR.

![ssr](https://github.com/user-attachments/assets/7d3bf988-6e36-483e-8fe6-90c8055fe54b)

We will use LoRa to manage Arduino remotely.

![LoRa_Ra-01](https://github.com/user-attachments/assets/d023f4f5-d558-4328-a87f-e486efc59a9e) ![LoRa_Ra-01(2)](https://github.com/user-attachments/assets/452f217f-d8e7-475b-8867-80fa0b0f5347)

Our first module will open or close the ssr.

![ssrCircuit](https://github.com/user-attachments/assets/4b0b0774-5b57-4b2e-a997-b7bf6e04d6fb)


Our second module will send an on/off switch's on or off signal to the first module via LoRa. It will be battery-powered.

![controllerCircuit](https://github.com/user-attachments/assets/7b9cf1d2-4cd7-4431-8f7e-ab3373675153)


## Required products
- Arduino nano (2x)
- Ra-01 LoRa Module SX1278 (2x)
- XL4015
- SSR-10DD
- on-off switch
