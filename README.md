# Robotic-arm
This project is a 4 Degrees of Freedom (DOF) robotic arm designed for precision movement and object manipulation. It features modular control, smooth servo actuation, and customizable control inputs, making it ideal for hobbyists, educators, and research projects.

Features
4 Degrees of Freedom: Includes base rotation, shoulder, elbow, and wrist movements for versatile operation .
Gripper Mechanism: Equipped with a servo-powered gripper for holding objects.
Smooth Motion Control: Uses PWM control for seamless and precise servo actuation.
Customizable Inputs: Can be controlled via potentiometers, joysticks, or programmable interfaces like a microcontroller or computer.
Compact Design: Lightweight and sturdy structure suitable for small to medium loads

<p>
  <img width=80% src="IMAGES/IMG_20241207_125614.jpg">
</p>  
<p>
  <img width =80% src="IMAGES/IMG_20241129_195953.jpg">
</p>

# CIRCUIT
<p>
  <img width=30% src="IMAGES/IMG_20241130_122155.jpg">
</p>
With printed case:
<p>
  <img width=30% src="IMAGES/IMG_20241201_215521.jpg">
</p>

### **Microcontroller (Arduino) to PCA9685:**
| **Arduino** | **PCA9685** |
|------------|------------|
| 5V         | VCC        |
| GND        | GND        |
| SDA (A4)   | SDA        |
| SCL (A5)   | SCL        |

### **PCA9685 to Servos:**
| **Servo Channel** | **PCA9685 Output** |
|------------------|------------------|
| Servo 1 (Base)   | Channel 0 |
| Servo 2 (Shoulder) | Channel 1 |
| Servo 3 (Elbow) | Channel 2 |
| Servo 4 (Wrist) | Channel 3 |
| Servo 5 (Gripper) | Channel 4 |

### **Potentiometer Connections (to Arduino):**
| **Potentiometer** | **Arduino Pin** | **Connections** |
|------------------|----------------|----------------|
| Pot 1 (Base)    | A1             | VCC - Wiper - GND |
| Pot 2 (Shoulder) | A2             | VCC - Wiper - GND |
| Pot 3 (Elbow) | A3             | VCC - Wiper - GND |
| Pot 4 (Wrist) | A6             | VCC - Wiper - GND |
| Pot 5 (Gripper) | A7             | VCC - Wiper - GND |

### **Servo Power Supply:**
- **External 5V power supply** is needed for servos.
- **PCA9685 V+** should be powered with **5V** (common ground with Arduino).
- **Each servo's red wire** should be connected to **5V**, **black wire** to **GND**, and **yellow/white wire** to corresponding PCA9685 channels.

# STEP MODEL
<p>
  <img width =80% src="IMAGES/Screenshot 2024-10-29 192417.png">
</p>
