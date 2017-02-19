# Protocol Definition
## General

* Baudrate: 9600
* Sent over serial

## Message format

The data can be sent from

### Header

---
byte|null|null|...

---

The first byte (unsigned) is the command type. If it is not in the table below, discard the message.

| Value | Meaning when sent from the TX1 | Meaning when sent from the Arduino |
| --- | :---: | :---: |
| 1 | New setpoint list, arm data | New arm joint data |
| 2 | Abort everything | Request to stop |
| 3 | New setpoint list, gripper data | New gripper joint data |
| 4 | Path has ended | unused

### Setpoint/joint data format

After the message header, either 2 or 4 floats (IEE 754) are sent.

When the arm data is sent, 4 floats are sent representing these joints (in order):

* shoulder, connecting the spinning thing to the first arm segment (pitch)
* elbow, connecting the first arm segment to the second (pitch)
* lower_elbow, (I didn't name these), connecting the second arm segment to the piece that holds the gripper base (pitch) 
* hip, the spinning thing at the base (yaw)

Whilst when the gripper is sent, these 2 are sent:

* grip_twist, the part that twists the gripper (roll)
* grip, the part that actually moves, (prismatic)

Rotations are in radians, and the gripper is in metres.

The floats are packed like this:

---
float|null|float|null ... float|null

---

### Abort/path end format
Abort contains nothing after the header.

## Behavior

When the TX1 receives a new path, it sends a type 1/3 message corresponding to the type of movement.
It then waits for a similarly typed message from the arduino. It then checks if there are anymore messages to send.
If there are, then repeat, else send a type 4.

If at anytime anything is wrong, the arduino should send a type 2 message, and if tolerances are violated/a stop request is sent to the TX1,
it will send a type 2 message. When the arduino sends or receives a type 2 message, it should stop moving immediately and act as if the path has finished.
If the TX1 sends or receives one, it will set the result to `ABORTED` and stop sending messages until it gets a new path.
 