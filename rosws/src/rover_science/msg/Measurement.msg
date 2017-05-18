geographic_msgs/GeoPoint location
time time_recorded
uint8 data_completeness # bitfield, see data below

uint8 HAS_PH=1
uint8 HAS_TEMP=2
uint8 HAS_HUMIDITY=4
uint8 HAS_EC=8

float64 ph
float64 humidity
float64 temp
float64 ec