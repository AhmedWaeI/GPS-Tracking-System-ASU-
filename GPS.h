#ifndef GPS
#define GPS
float toRad (float angle);
float toDeg (float angle);
float getDistance (float startLong, float startLat,float endLong,float endLat);
void GPS_read ();
void GPS_format ();
#endif