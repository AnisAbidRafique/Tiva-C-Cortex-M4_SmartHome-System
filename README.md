# Tiva-C-Cortex-M4_SmartHome-System
## Smart Home System

![image](https://github.com/AnisAbidRafique/Tiva-C-Cortex-M4_SmartHome-System/assets/107189829/6ba9e103-325a-47f2-a600-b1f30e9190ef)


### Abstract

The main objective of this project is to develop a home automation system using Tiva c microcontroller using UART communication being remotely control by a windows application. As technology is advancing so houses are also getting smarter. Modern houses are gradually shifting from conventional switches to centralized control system, involving remote controlled switches. Presently, conventional wall switches located in different parts of the house makes it difficult for the user to go near them to operate. Even more it becomes more difficult for the elderly or physically handicapped people to do so. Remote controlled home automation system provides a most modern solution with smart devices. A GUI application on windows sends ON/OFF commands to the receiver where loads are connected. By touching the specified location on the GUI, the loads can be turned ON/OFF remotely through this technology. The loads are operated by Tiva c board through opto-isolators and thyristors using in Relay modules.

### Introduction

Nowadays, we have remote controls for our television sets and other electronic systems, which have made our lives really easy. Have you ever wondered about home automation which would give the facility of controlling tube lights, fans and other electrical appliances at home using an application? Off-course, Yes! But, are the available options cost-effective? If the answer is No, we have found a solution to it. We have come up with a new system called Tiva c based home automation using UART. This system is super-cost effective and can give the user, the ability to control any electronic device whether it is AC or DC Load without even spending so much money. This project helps the user to control all the electronic devices using his/her Windows Application. Time is a very valuable thing. Everybody wants to save time as much as they can. New technologies are being introduced to save our time. To save people’s time we are introducing Home Automation system using UART. With the help of this system, we can control our home appliances from a single application.

### Components
The major components used is this project is are as follow:
* Tiva c Microcontroller
* Relay Module
* LCD
* 7805 IC
* Capacitors
* 9V DC Battery
* Supply Board
The description of each component is as follow:

#### Tiva c Microcontroller

The Tiva™ C Series TM4C123G Launchpad Evaluation Board (EK-TM4C123GXL) is a low-cost evaluation platform for ARM® Cortex™-M4F-based microcontrollers. The Tiva C Series launchpad design highlights the TM4C123GH6PMI microcontroller USB 2.0 device interface, hibernation module, and motion control pulse-width modulator (MC PWM) module. The Tiva C Series Launchpad also features programmable user buttons and an RGB LED for custom applications. The stackable headers of the Tiva C Series TM4C123G launchpad Booster Pack XL interface demonstrate how easy it is to expand the functionality of the Tiva C Series Launchpad when interfacing to other peripherals on many existing booster Pack add-on boards as well as future products. Figure 1-1 shows a photo of the Tiva C Series Launchpad.
We use tm4c123gh6pm microcontroller to give control signals to the relay module but programming its relay pins respectively. In this way we can control the channels of the relay using Tiva c and the communication protocol that we use is the UART, which is the build in peripheral in this microcontroller. We send and receive information using UART0 peripheral of this controller.

![image](https://github.com/AnisAbidRafique/Tiva-C-Cortex-M4_SmartHome-System/assets/107189829/8d10d52d-6d04-4ff5-8e81-cd72fc1f9ce8)

#### Relay Module

A relay is an electrically operated switch. Many relays use an electromagnet to mechanically operate a switch, but other operating principles are also used, such as solid-state relays. Relays are used where it is necessary to control a circuit by a separate low-power signal, or where several circuits must be controlled by one signal.
In this experiment we use four channel relay modules as we are controlling four different AC load in this system. We give control signal to relay pins using tiva c controller. The relay module is completely isolated from the tiva c control voltages, so our controller remains safe in this way.

![image](https://github.com/AnisAbidRafique/Tiva-C-Cortex-M4_SmartHome-System/assets/107189829/14234536-e043-4598-8e40-22f07105399f)


#### LCD

We interface 1602 lcd module with our controller in order to show statues of the load in every case. It contains 16 rows and 2 columns to display information.
We refresh the statues after every switching of the channel, in this way a user can able to see which load switch is currently ON.

![image](https://github.com/AnisAbidRafique/Tiva-C-Cortex-M4_SmartHome-System/assets/107189829/308336f4-61a3-4037-8847-5e63b2c62bee)

#### Voltage Regulation using 7805 IC

We use a 7805 IC to make a voltage regulator of 5V using some capacitors and an external 9V DC battery source. We give this 5V supply to our relay module, as to protect our controller from noise of the circuit which can be generated while switching between the channels. In this way we can provide complete electrical isolation to our Microcontroller.
You can see voltage regulator circuit in figure 

![image](https://github.com/AnisAbidRafique/Tiva-C-Cortex-M4_SmartHome-System/assets/107189829/aed13a8c-a7ef-4f41-a1ae-256a62ba84a0)


We use two capacitors as to regulate our input voltage. First one is 0.22uF on the input and on the output, we use 0.1uF Capacitor.

#### Supply Board

We made a simple supply board using some power sockets and an AC control switch.
We can connect our load in the respective socket, you can see the board are as follow;

![image](https://github.com/AnisAbidRafique/Tiva-C-Cortex-M4_SmartHome-System/assets/107189829/b4f1ad4d-3f98-4c6a-9248-d4f894f9a0a9)

### Block Diagram
![image](https://github.com/AnisAbidRafique/Tiva-C-Cortex-M4_SmartHome-System/assets/107189829/9d23d179-082e-45e1-889f-6dd8bc346e10)

### Circuit Diagram

In the circuit, I use Ports B and F for LCD interfacing and Port E for relay switching.
Also, I made a voltage regulator to give 5v to our relay module.
8 pins od port B act as data bits for LCD and 3 pins of Port F as control pins.
Also, I use Port A0 and A1 for UART0 interfacing with my PC.
You can see the circuit diagram are as follow;

![Picture1](https://github.com/AnisAbidRafique/Tiva-C-Cortex-M4_SmartHome-System/assets/107189829/6a8f0cb0-fe16-40ed-ad25-0b5ddf56092b)



### GUI based Windows Application

I made the windows application using C# language on Microsoft Visual Studio 2019.
It basically gives input to the controller using UART transmission and when the controller receives the input, it acts accordingly.
You can see my application in the figure below;

![image](https://github.com/AnisAbidRafique/Tiva-C-Cortex-M4_SmartHome-System/assets/107189829/d100d7d2-fbcf-4755-8b45-6adfca89b750)


For example, we press button 3, in the coding it’ll write 3 on the serial monitor, so the read variable would get 3 and by using switch case statement case 3 will be selected and it’ll toggle port E pin connected to the 3rd channel of relay.

### Working

The smart home works on the commands which we give him using application and it reads the commands and act accordingly, following are some of the features of this system
* When we Press Button 1, the 1 character is transmitter through serial communication and our controller reads the value. By using switch case statement, it toggles the pin 1 of Port E to either make it High or Low.
* When we press All ON, it sends a character of 5 to the controller and the tiva c sets all the four channels of the relay.
* When we press All OFF, it sends a character of 6 to the controller and the tiva c resets all the four channels of the relay.

![image](https://github.com/AnisAbidRafique/Tiva-C-Cortex-M4_SmartHome-System/assets/107189829/5b220bd1-62ee-470b-a061-9cb996d1a382)
![image](https://github.com/AnisAbidRafique/Tiva-C-Cortex-M4_SmartHome-System/assets/107189829/39e36641-c9d0-4ce4-8973-86cee840fd2a)

### Applications

Below are some practical applications and advantages of the above system;
* Lighting Control
* Improve safety and Security
* Smart Energy management 
* Smart switches 

### Conclusion

The system as the name indicates, ‘Home automation’ makes the system more flexible and provides attractive user interface compared to other home systems. In this system we integrate smart devices into home automation systems. A novel architecture for a home automation system is proposed using the relatively efficient communication technologies. The system consists of mainly three components is a UART module, TIVA c microcontroller and Relay modules. Serial communication is used as to transmit data from User to the microcontroller using windows application. We hide the complexity of the notions involved in the home automation system by including them into a simple, but comprehensive set of related concepts. This simplification is needed to fit as much of the functionality on the limited space offered by a smart device. Hence, we can conclude that the required goals and objectives of home automation system have been achieved. The system design and architecture were discussed, and prototype presents the basic level of home appliance control and remote monitoring has been implemented. Finally, the proposed system is better from the scalability and flexibility point of view than the commercially available smart home systems.

### Coding of Tiva c

The code of the project is available on this GitHub repository. You can download, load and run this code in your tiva c processor.

If you still find some problem, you can watch my project video on YouTube as listed below;
https://www.youtube.com/watch?v=LcbUCdhjg4g
or comment here of any problem that you are facing

Hope it will help you in your project.
