# Vehicle-Speed-and-Headlight-Control

# Description: 
The Smart Drive project enables users to command the speed of a vehicle and control the headlights through an LDR sensor or a touchpad. Users have access to various commands:- 
1) Eco : This will set the speed to 55% of its maximum speed
2) Normal : This will set the speed to 70% of its maximum speed
3) Sport : This will set the speed to 85% of its maximum speed
4) Track : This will set the speed to 95% of its maximum speed
5) Manualon : Will allow the headlight control with touchpad only
6) Manualoff : Will allow the headlight control with LDR sensor only (Automatic - No user input)
7) Help : This will print details about all available comands 

To fully grasp the project's functionality, it is recommended that users watch the 10-minute video. The video provides a comprehensive overview of the project, and users can then proceed to review the project's code. The video link :- https://youtu.be/ZDydGESPu1o (Please let me know if you face any issues with the link, so that I can slack you the link).

As stated in the preliminary design review (PDR), I was unable to acquire a motor with the exact specifications required for the project. Therefore, I have decided to simulate speed changes by adjusting the duty cycle. It is commonly known that the duty cycle and speed are directly proportional, so a 20% increase in duty cycle will result in a 20% increase in speed.

# Steps to run the project by end user

- To run and test the project, you will require an LDR sensor, a KL25Z Frdm board, and an oscilloscope.
- Connect the Vcc pin of the LDR to 3.3V, the ground of the LDR to the GND pin of the FRDM board, and the analog output pin of the LDR to PORTE Pin 20 of the FRDM board.
- To monitor changes in the duty cycle, connect PORTD Pin 2 of the FRDM board to an oscilloscope.

# Working of the code 

The project has different modules and the main file is named as "Smart_Drive_Final_Project.c". So the main file will call various functions from different modules to make the project work. Below is the sample flow diagram of the project :

![image](https://user-images.githubusercontent.com/86314597/236372752-9180759e-4a4c-4596-bc5c-0149fc5aae83.png)

# Screenshots of working serial terminal and PWM 

Eco Mode:

 
![image](https://user-images.githubusercontent.com/86314597/236374270-0348fc4f-acff-406d-836d-847c67301608.png)
![scope_5](https://user-images.githubusercontent.com/86314597/236374722-99d6de9c-85d0-42c5-8d6b-1efb8ad4a76e.png)


Normal Mode:


![image](https://user-images.githubusercontent.com/86314597/236374353-829d685e-ab54-47fd-adc3-58a5fd6bec62.png)
![scope_6](https://user-images.githubusercontent.com/86314597/236374755-cb6157e7-25bf-4632-9b93-ed45840e6c07.png)

Sport mode:


![image](https://user-images.githubusercontent.com/86314597/236374392-f595470b-5225-4330-b9a3-678bcee3e397.png)
![scope_7](https://user-images.githubusercontent.com/86314597/236374761-c00ae16d-d80e-4ffa-9787-38d4efcea154.png)

Track mode:


![image](https://user-images.githubusercontent.com/86314597/236374430-965530fb-9860-40e0-8569-46e5cfb4292c.png)
![scope_8](https://user-images.githubusercontent.com/86314597/236374779-58552555-5306-4425-bd61-27195202d15c.png)


Help command:


![image](https://user-images.githubusercontent.com/86314597/236374512-23605ec9-2295-4fe3-ac0a-80aa1bb22e2e.png)

# Test Cases:

Out of all the modules, only the command parser and UART modules can be tested using software. The other modules are entirely dependent on hardware and need to be tested on the DUT (Device Under Test) bench. Therefore, a video explanation demonstrating the bench test of the project (i.e., the working of the project with hardware) is provided and also screenshots are added. 

For software testing, I tested the UART module by enqueuing and dequeuing data for happy, error, and corner cases. Additionally, I tested the command parser module by passing valid or happy cases, invalid or error cases, and valid commands with whitespaces and different cases (capital or small), which fall under the category of corner cases. 

Once testing is completed, the PWM value is set to 0 before running the while(1) loop. This is necessary because the test cases may change the PWM value while calling the command parser. Therefore, we need to initialize the PWM to 0 before running the actual code.

# Few points about the project
1) In the main.c "Smart_Drive_Final_Project.c" inside the int main(), 

![image](https://user-images.githubusercontent.com/86314597/236378304-2a362651-3ec2-4a26-a447-dcb90350c170.png)

As you can see in the code, I have called all the init functions before the "Init board hardware" function, except for the "pwm_init()" function, which is called after "Init board hardware". The reason behind this is that all other functions do not depend on the board init hardware, but only the "pwm_init()" function is dependent on it. Moreover, after calling "Init board hardware", I encountered issues with the clock configuration of the UART init function, which caused the UART to malfunction. After conducting numerous trials, I realized that the board init hardware of PWM was the root cause of this problem. Therefore, I called the UART and other init functions before it to resolve the issue.   

2) In this project, macros are used for every magic number except for the generic values 0 or 1.
3) As it is expected to test the entire project, software tests can only be performed on two modules, and the remaining modules are bench tested using DUT (Device Under Test).
4) The interrupt is solely utilized for UART because speed control takes precedence over other operations, such as headlight control, which is performed by polling the touch and ADC values. One noteworthy observation is that utilizing an interrupt with ADC generates an interrupt for every single conversion. However, in practical scenarios, sunlight does not suddenly appear or disappear abruptly. Rather, it happens slowly, and there is no need to read every single conversion from the LDR sensor. Therefore, instead of using an interrupt, polling is employed for this purpose.
5) I used the sysclock configuration provided in assignment 6(Prof. Howdy code) for my uart configuration. 

# Mandatory Questions :
1) Scope changes: The project proposal has undergone minimal changes. The only modification made was to the method of command parsing. Initially, the plan was to use start and stop bits to identify the commands. The idea was to use a '@' start character and '#' stop character to delimit a packet, and then use parsing to determine the user's selected mode. However, during implementation, it became apparent that an invalid packet could also contain the same start and stop characters, causing the invalid command to be mistakenly accepted as valid. To overcome this, a command pattern was used, which examines the entire command instead of just the start and stop characters. This is an enhanced version of the proposed implementation, and I believe it should not impact my score adversely.

2) What worked and what did not work from your modified scope: Everything is working as expected. 
3) What were the key learnings : I have gained the valuable insight that testing each module individually can be highly beneficial. At first, I was impatient and tested the entire code, anticipating that all modules would function together. However, they did not work as expected. As a result, I began debugging each module one by one, which allowed me to identify issues and resolve them. This project has enhanced my testing skills and shifted my perception towards testing methodologies.
4) What would you do differently: I am satisfied with the final outcome of the project. However, if I had more time, I would like to incorporate an LCD display to show the current speed.

 
