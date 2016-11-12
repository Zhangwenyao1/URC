#include "Arduino.h"
#include "Constants.h"

Consants::Constants{
  M0=0;
  M1=1;
  M2=2;
  M3=3;
  M4=4;
  M5=5;
  pot0=A0;
  pot1=A1;
  pot2=A2;
  pot3=A3;
  enca0=6;
  encb0=7;
}
Constants::getValue(String _key){
  switch _key:
    case "M0":
		return M0;
	case "M1":
		return M1;
	case "M2":
		return M2;
	case "M3":
		return M3;
	case "M4":
		return M4;
	case "M5"
		return M5;
	case "pot0":
		return pot0;
	case "pot1":
		return pot1;
	case "pot2":
		return pot2;
	case "pot3":
		return pot3;
	case "enca0":
		return enca0;
	case "encdb0":
		return encb0;
    
  
}

