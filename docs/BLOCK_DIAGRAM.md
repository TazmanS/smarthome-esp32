# SmartHome ESP32 - Block Diagram

This file provides a compact block diagram for project review and defense.

## Functional Block Diagram

```mermaid
graph LR
    subgraph Inputs[Inputs]
        LM35[LM35 Temperature]
        PHOTO[Photocell]
        PIR[PIR Motion]
        IR[IR Receiver]
        BTN[Buttons]
    end

    subgraph MCU[ESP32 Firmware]
        ADC[ADC Driver]
        RMT[RMT Driver]
        GPIOI[GPIO ISR]
        T1[SendTempTask]
        T2[SendPhotocellTask]
        T3[IRTask]
        T4[DisplayTask]
        T5[MQTTTask]
        T6[LogTask]
        Q[FreeRTOS Queues]
        WDT[Task Watchdog]
        CPUMON[CPU Monitor Task]
    end

    subgraph Outputs[Outputs]
        LCD[LCD1602 I2C]
        LED[LEDs]
        MOTOR[Motor]
        SERVO[Servo]
        CLOUD[MQTT Broker]
    end

    LM35 --> ADC
    PHOTO --> ADC
    ADC --> T1
    ADC --> T2

    IR --> RMT --> T3
    PIR --> GPIOI
    BTN --> GPIOI

    T1 --> Q
    T2 --> Q
    T3 --> Q
    Q --> T4
    Q --> T5
    Q --> T6

    T4 --> LCD
    GPIOI --> LED
    T5 --> MOTOR
    T5 --> SERVO
    T5 --> CLOUD

    WDT --> T1
    WDT --> T2
    WDT --> T3
    WDT --> T4
    WDT --> T5
    WDT --> T6
    CPUMON --> T5
```

## Notes

- Data flow: `LM35/Photocell -> ADC -> SendTempTask/SendPhotocellTask -> MQTT Task -> Cloud Broker`
- Manual control: IR remote commands and GPIO buttons trigger actions via GPIO ISR
- Reliability: Watchdog is initialized with idempotent error handling and serviced in all active tasks (IR task uses 4s timeout)
- Asynchronous architecture: Sensor and control data exchanged through FreeRTOS queues
- Sensor data buffer: Fixed `key[32]` to safely hold topic strings like `sensor/temperature`
