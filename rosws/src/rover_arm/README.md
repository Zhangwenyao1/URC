# Protocol Definition
## General

Baudrate: 9600

## TX1 -> Arduino

---

byte|null|null|...

The first byte (unsigned) is the command type. If it is not in [1, 2], discard the message.

| Value | Meaning |
| --- | --- |
| 1 | New setpoint list |
| 2 | Abort everything |

When aborting, there is no more data.

### Setpoint list format

After the message "header" (byte null null), 6 floats (IEE 754) are sent.

float|null|float|null ... float|null