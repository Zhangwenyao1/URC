#Armduino <br>
This is the code for the R3 URC17 rover - arm.<br>
The classes and files are organized as follows

<h1>SRC:</h1>
-ArmDuino <br>
-Constants <br>
<h2>-Classes:<br></h2>
	<h3>-Util:</h3>
		-Math Functions<br>
		-Motor<br>
		-Motor Controller<br>
		-Potentiometer<br>
		-Switch<br>
	<h3>-Compontents:</h3>
		-Gripper<br>
		-Joint<br>
		-Winch<br>

The armduino communicates to the TX1 via the serial port at a baud rate of 9600,
the custom serial protocal sends communicates via the following form:
	
C B1 B2 B3 .... Bn

Where:<br>
	C - is the command byte<br>
	Bn - is the action byte<br>

the following command bytes are used:<br>
1 - move joints to desired position, then return position<br>
2 - kill all movement<br>
3 - move the gripper to desired position, then return position<br>
4 - NULL<br>
