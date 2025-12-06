# Concept and Prototype for the “Retro-futuristic” Age-Friendly Smart Home Project

[中文版](README_ZH.md) is available.

### Overview: This project aims to build a modular smart home system prototype centered on offline operation and grounded in “retrofuturism” philosophy. It serves elderly users through minimalist physical interactions, adhering to core engineering principles of open-source design, reliability, and repairability.

## Motivation and Concept

This project stems from my observations and reflections on the lives of the elderly, particularly those struggling to adapt to modern technological products.

I aspire for individuals in their twilight years—even when facing declining health or memory loss—to live with dignity. This pursuit is fundamentally detached from economic trends; it represents my most primal and essential motivation.

Thus, designing an age-friendly smart home system is imperative. Its foundational principles are “low learning curve, robustness, and core open-source.” It must achieve:


### Design Principle 1: Instinctive Interaction

My grandmother cannot learn to use any smart devices. She relies solely on landline phones, radios, and televisions for external information, along with appliances like washing machines and refrigerators. My ultimate goal is to enable seniors like her to use this system effortlessly.
Thus, I will adopt a “retrofuturistic” design philosophy, minimizing redundant “tech” elements and employing intuitive, skeuomorphic forms for user comprehension.

The original iPhone exemplifies this success. A five-year-old with no prior exposure to smart devices could master its operation within minutes. This was achieved through its skeuomorphic UI design (e.g., settings icons resembling metal gears, the phone icon as a handset) and intuitive interaction patterns. My system must carry forward this legacy.


### Design Principle 2: Offline-first & Reliability

Technology should serve people, not enslave them. Hardware devices (or business strategies) that force users into frequent updates, cloud service subscriptions, or vendor lock-in are profoundly inhumane.

Good devices should operate like my grandmother's radio and landline phone—working silently in the background, unnoticed yet consistently reliable. My ideal smart home system resembles traditional appliances: anyone can install it, it lasts for years once set up, and it's easy to repair or replace.

Therefore, it should has modularity, making no critical decisions dependent on cloud services. All data resides locally. The vast majority of interactions utilize mechanical components (buttons, knobs, light/sound/vibration feedback) to ensure stable operation in offline environments.


### Design Principle Three: Open Source & Sovereignty

For commercialization, paid services can be offered to users with more complex needs. However, the core system components must remain open source—never monopolized. Technical sovereignty must always belong to the user.

## Project Roadmap & Hardware Solution

### Phase One: Environment & Perception - Focus on the Embedded Core to Anchor System Stability

Main Control Core: ESP32 | Environmental Sensing: DHT11 (low accuracy), BME280 (planned) | Status Indication: Onboard/External LEDs

### Goal: Build a minimal system capable of reliably collecting environmental data (temperature, humidity, barometric pressure), processing it locally, and providing physical feedback (via lights) during network outages.

Key Tasks:

1. Hardware Finalization: Replace DHT11 with BME280 sensor to resolve accuracy and latency issues.

2. Stability Optimization: Migrate prototype circuit from breadboard to perforated board soldering, implement independent power supply to eliminate random reboots.

3. Data Pipeline Validation: Implement stable data reading and Kalman filtering on ESP32 (already achieved), and verify dual-path data upload via Wi-Fi/future 4G module. (Wi-Fi path verified; 4G path pending module readiness)

Success Criteria: Device operates stably for over 72 hours post-powerup outside debugging environments, with clear status indication via physical buttons or lights.


### Phase Two: Interaction & Autonomy - Breakthrough in Communication & System Integration for Independent Operation

Offline Communication: 4G Module | Physical Interaction: Physical Buttons, Rotary Encoder, Buzzer | Power Management: 5V/2A Standalone Power Module, Lithium Battery Charge/Discharge Management

### Goal: Achieve fully offline, independent device operation while establishing intuitive physical interaction channels to form a deliverable terminal product prototype.


### Phase Three: Expansion and Deepening - Focusing on Architecture and Experience to Make Technology Truly Serve People

Perception Expansion: Millimeter-wave radar, infrared arrays | Actuator Units: Relay modules, smart sockets | Local Hub: Raspberry Pi/old smartphones

### Goal: Expand the system's perception and execution capabilities, explore a locally centralized hub architecture, and achieve more complex scenario-based automation.

### Regarding Program Annotations and Explanatory Documentation: Chinese will be prioritized during the prototyping phase to ensure development speed and accuracy of explanations. Subsequent software configurations and critical interface documentation will be translated in the future.

## This repository will evolve alongside project iterations, comprehensively documenting every thought, line of code, and failure from prototype to product. This represents my initial practice of the engineering principles I firmly believe in: openness, low cost, reproducibility, and verifiability.

