# Smart Trash Bin – Arduino Project

This Arduino-based project controls an automated smart trash bin that opens its lid when a hand is detected, alerts the user with a buzzer, and visually indicates the fill level of the bin using ultrasonic distance sensing and LEDs.

## 🔧 Hardware Used

- Arduino UNO R3
- 2x HC-SR04 ultrasonic sensors
- SG90 Servo motor
- 3x LEDs (green, yellow, red)
- 3x 220Ω resistors (for LEDs)
- Buzzer (active)
- External 5V or 9V power source (optional for standalone use)
- Breadboard and jumper wires

## 📌 Features

- **Hand detection** using HC-SR04: opens the lid via servo motor and activates a buzzer.
- **Auto-closing** after 10 seconds.
- **Fill-level detection** using a second HC-SR04:
  - Green LED → bin is empty
  - Yellow LED → bin is partially filled
  - Red LED → bin is full

## 📎 Pin Mapping

| Component       | Arduino Pin |
|----------------|-------------|
| HC-SR04 (hand) – TRIG | D4 |
| HC-SR04 (hand) – ECHO | D5 |
| HC-SR04 (level) – TRIG | D6 |
| HC-SR04 (level) – ECHO | D7 |
| Buzzer         | D8 |
| Servo          | D9 |
| Green LED      | D10 |
| Yellow LED     | D11 |
| Red LED        | D12 |

## 🧠 How It Works

- When an object (e.g. a hand) is detected at less than 10 cm above the bin, the servo opens the lid and the buzzer activates.
- The lid stays open for 10 seconds, then closes and stops the buzzer.
- Continuously, the second ultrasonic sensor measures the distance to the trash. Based on this:
  - Green LED is turned on if distance > 15 cm
  - Yellow LED is turned on if distance between 2–15 cm
  - Red LED is turned on if distance < 2 cm
