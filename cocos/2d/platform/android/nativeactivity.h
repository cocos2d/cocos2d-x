#ifndef __COCOSNATIVEACTIVITY_H__
#define __COCOSNATIVEACTIVITY_H__

/**
 * This is the interface to the Android native activity
 */

void enableAccelerometerJni(void);
void disableAccelerometerJni(void);
void setAccelerometerIntervalJni(float interval);

#endif // __COCOSNATIVEACTIVITY_H__
