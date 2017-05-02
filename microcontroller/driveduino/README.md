#Driveduino<br>
This is the code for the R3 URC17 rover - drive<br>
The code is organized as follows:<br>
<h1>SRC:</h1>
-DriveDuino<br>
-Constants<br>
<h2>Classes</h1>
<h2>Util</h2>
-Math Functions<br>
-Motor<br>
-Motor Controller<br>

The driveduino communicates to the TX1 via the serial port at a baud rate of 9600,
the custom serial protocal sends communicates via the following form:
	
C B1 B2 B3 .... Bn

Where:<br>
	C - is the command byte<br>
	Bn - is the action byte<br>

the following command bytes are used:<br>
1 - drive at given velocity<br>
2 - kill all<br>
3 - NULL<br>
