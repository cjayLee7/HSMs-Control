This repository contains supplementary materials for the paper:  
**"Enhancing Position Tracking of Hybrid Stepper Motors using Lyapunov-Based Current Controllers"**  
Published in *Electronics* .  

### 1. MATLAB/Simulink Models  
The simulation models (`stepper_model.slx` and `untitled.m`) are developed in MATLAB R2021b. The Simulink model can be directly executed.

### 2. STM32 Embedded C Code  
The firmware supports STM32F407IGT6 microcontrollers. Key components include:  
- **Algorithm implementation** (`MotorDrive/Src/`): Contains the current-loop interrupt service routines (`foc_it.c`) and initialization logic (`loop.c`). The Lyapunov-based controller runs at 35 kHz (current loop) and 3.5 KHz (torque loop).  
- **Peripheral drivers** (`MotorDrive/bsp/`): Implements UART communication using the JustFloat protocol (`usart.c`) for data exchange with the VOFA+ host PC tool.  

### 3. Usage Notes  
- Code comments are fully documented in English, with explicit references to equations in the paper.  
- Hardware-specific configurations (e.g., PWM pins, ADC channels) need to be adapted to your setup.  
- Critical parameters (control gains, sampling frequencies) are centralized in `parameter.c` for easy customization.  
