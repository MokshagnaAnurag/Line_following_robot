# Line Following Robot for Arduino Uno

A simple and efficient line-following robot implementation using Arduino Uno with IR (Infrared) sensors and DC motors.

## Overview

This project implements a basic autonomous line-following robot that uses two IR sensors to detect a black line on a white surface and follows it using motor control.

## Hardware Requirements

### Microcontroller
- **Arduino Uno** (or compatible board)

### Sensors
- **2x IR Sensor Module** (digital output type)
  - Detects black line on white surface
  - Output: HIGH (white/no line), LOW (black/line detected)

### Motors & Motor Driver
- **2x DC Motors** (3-6V, ~100-200 RPM recommended)
- **Motor Driver Module** (L298N or similar 2-channel DC motor driver)
  - Supports PWM speed control
  - Can drive 2 independent motors

### Power Supply
- **Battery Pack** (6V-12V depending on motor specs)
- **USB Cable** (for Arduino programming)

### Mechanical Components
- Robot chassis with wheels
- Castor wheel or ball bearing for balance
- Motor mounts
- Sensor mounting brackets

## Pin Configuration

### Motor Control Pins
| Component | Pin | Type | Purpose |
|-----------|-----|------|---------|
| Motor A Enable | 5 | PWM | Left motor speed control |
| Motor A Input 1 | 8 | Digital | Left motor direction |
| Motor A Input 2 | 9 | Digital | Left motor direction |
| Motor B Enable | 6 | PWM | Right motor speed control |
| Motor B Input 3 | 10 | Digital | Right motor direction |
| Motor B Input 4 | 11 | Digital | Right motor direction |

### Sensor Pins
| Component | Pin | Type | Purpose |
|-----------|-----|------|---------|
| Left IR Sensor | 2 | Digital | Detect line on left side |
| Right IR Sensor | 3 | Digital | Detect line on right side |

## Wiring Diagram

```
Arduino Uno
├─ Pin 5 (PWM)  ──→ Motor Driver IN1 (Motor A Enable)
├─ Pin 6 (PWM)  ──→ Motor Driver IN3 (Motor B Enable)
├─ Pin 8        ──→ Motor Driver IN2 (Motor A Direction)
├─ Pin 9        ──→ Motor Driver IN4 (Motor A Direction)
├─ Pin 10       ──→ Motor Driver IN5 (Motor B Direction)
├─ Pin 11       ──→ Motor Driver IN6 (Motor B Direction)
├─ Pin 2        ──→ Left IR Sensor
├─ Pin 3        ──→ Right IR Sensor
├─ GND          ──→ Motor Driver GND
└─ 5V (if needed) ──→ IR Sensor VCC

Motor Driver Module
├─ OUT1, OUT2   ──→ Motor A (Left)
├─ OUT3, OUT4   ──→ Motor B (Right)
└─ Power Supply  ──→ Battery Pack
```

## How It Works

### Logic Flow
1. **Read Sensors**: Check if black line is detected by left and right IR sensors
2. **Decision Making**:
   - **Both sensors LOW (on line)**: Move forward
   - **Left sensor LOW, Right sensor HIGH**: Turn left
   - **Left sensor HIGH, Right sensor LOW**: Turn right
   - **Both sensors HIGH (off line)**: Stop or search

3. **Motor Control**: Adjust motor speeds accordingly

### Motor Control Functions
- **moveForward()**: Both motors at same speed forward
- **moveBackward()**: Both motors at same speed backward
- **turnLeft()**: Left motor slower, right motor faster
- **turnRight()**: Left motor faster, right motor slower
- **stopRobot()**: All motors stopped

## Customization

### Speed Adjustment
Edit these constants in the code:

```cpp
#define MAX_SPEED 255      // Maximum PWM value (0-255)
#define BASE_SPEED 200     // Forward movement speed
#define TURN_SPEED 150     // Turning movement speed
```

Lower values = slower movement, higher values = faster movement

### Sensor Sensitivity
Adjust IR sensor sensitivity using the potentiometer on the sensor module for different line thicknesses or surface conditions.

## Installation & Upload

1. **Download Arduino IDE** from [arduino.cc](https://www.arduino.cc/en/software)

2. **Connect Arduino to Computer** using USB cable

3. **Open the Arduino IDE** and load the `line_follower_robot.ino` file

4. **Select Board**: Tools → Board → Arduino Uno

5. **Select Port**: Tools → Port → COM port of your Arduino

6. **Upload Code**: Click Upload button or press Ctrl+U

7. **Monitor**: Open Serial Monitor (Ctrl+Shift+M) to see debug output at 9600 baud

## Troubleshooting

| Problem | Solution |
|---------|----------|
| Robot doesn't move | Check motor connections and battery voltage |
| Robot moves in circles | Calibrate motor speeds or check wheel alignment |
| Sensors not detecting line | Adjust sensor sensitivity or check sensor connections |
| Erratic movement | Reduce speed or check battery voltage |
| Robot follows line incorrectly | Ensure sensors are aligned properly and facing the surface |

## Performance Tips

1. **Surface Contrast**: Use high-contrast lines (black on white) for best results
2. **Sensor Height**: Adjust sensor height ~5-10mm above the surface
3. **Motor Balance**: Ensure both motors have similar power output
4. **Weight Distribution**: Keep weight centered for stable movement
5. **Line Width**: Test with different line widths for optimal performance

## Future Enhancements

- Add PID (Proportional-Integral-Derivative) control for smooth turns
- Implement adaptive speed based on turn angles
- Add obstacle detection and avoidance
- Use multiple sensors for better tracking
- Add Bluetooth control for remote operation
- Implement UV or ambient light sensors for different lighting conditions

## License

This project is provided as-is for educational purposes.

## Support

For issues or questions, ensure:
- All connections are secure
- Battery voltage is sufficient
- Arduino IDE is up-to-date
- Code is properly uploaded to Arduino
- Serial monitor shows sensor readings
