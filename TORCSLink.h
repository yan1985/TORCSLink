#ifndef TORCSLINK_H
#define TORCSLINK_H

#ifdef _WIN32
	#include <windows.h>
#endif

/* Enable this if you have modified your TORCS sourcecode to perform integration of 
position data in doule precision rather than the default float. See <Insert link here> */
#define TL_USE_DOUBLE_POSITION

/* Enale this if you have modified your TORCS sourcecode to allow robots to restart races
See here: http://torcs.sourceforge.net/index.php?name=Sections&op=viewarticle&artid=30#c6_8 */
#define TL_ENABLE_RESTARTS


/* Number of vehicles 
10 seems to be the maximum values here */
#define N_VEHICLES 10

/* Define some control flags for the robot */
#define TL_NO_DATA 0			// There is no new data available
#define TL_NEW_DATA 1			// There is new data available
#define TL_RESTART_RACE 2		// Robot should restart the race (if available)
#define TL_READY 255			// Robot is ready

/* Structures for vehicle data */
/* Use double for all floating point values for easy compatibility with Simulink */

/* Vehicle Control Data*/
typedef struct vehicleControlStruct {
	double throttle;			// Throttle value, (0-1)
	double brake;				// Brake value, (0-1)
	double clutch;				// Clutch value, (0-1)
	double steering;			// Steering value (-1-1)
	int gear;					// Gear (-1-6)
} vehicleControl_t;

/* Vehicle Data */
typedef struct vehicleDataStruct {
	double position[3];			// Global position [m]
	double velocity[3];			// Global velocity [m/s]
	double acceleration[3];		// Global acceleration [m/s/s]
	double angle[3];			// Roll/Pitch/Yaw [rad]
	double angularVelocity[3];	// Roll/Pitch/Yaw rates [rad/s]
	double headingError;		// Error between vehicle heading and track heading (at current location) [rad]
	double lateralError;		// Lateral error between car (CoG) and track centreline (at current location) [m]
	double roadDistance;		// Distance travelled along track from start/finish line [m]
	double roadCurvature;		// Curvature of track (at current location), left turns = +ve curvature, right turns = -ve curvature 
	double engineRPM;			// Engine RPM
} vehicleData_t;

/* Total vehicle data */
typedef struct vehicleStruct {
	vehicleControl_t control;
	vehicleData_t data;
} vehicle_t;

/* Structure to be shared between processes */
typedef struct TOCSDataStruct {
	int enable;
	int controlFlag;
	vehicle_t vehicle[N_VEHICLES];
} TORCSData_t;

/* Location of shared memory */
TCHAR FileMapName[] = TEXT("Local\\TORCSDataStore");

#endif