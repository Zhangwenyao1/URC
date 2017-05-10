# Site message
string site_name
Measurement[] measurements
# geometry_msgs/Polygon area maybe later
uint8 has_pano  # image flags

string pano_location
string closeup_location

uint8 HAS_PANO=1
uint8 HAS_CLOSEUP=2