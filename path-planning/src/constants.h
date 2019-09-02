#ifndef CONSTANTS
#define CONSTANTS

#define CONTROLLER_UPDATE_RATE 50
#define UPDATE_STEP_TIME 0.02
#define MAX_POINTS_PER_SEC 49.5
#define NUM_OF_PREVIOUS_POINTS 10
#define MAX_SPEED_MILES 50
#define MAX_SPEED_M MAX_SPEED_MILES*1.609*1000
#define MAX_SPEED_MS MAX_SPEED_MILES*0.44704
#define MAX_ACCELERATION 10
#define MAX_JERK 10
#define SPEED_INCREMENT 0.224
#define MIN_D 2
#define MAX_LANE_CHANGE_TIME 1.0
#define KEEP_LANE_CHANGE_TIME 1.0
#define PATH_TIMESTEP 0.02
#define WAYPOINTS 5
#define INTERPOLATION_DISTANCE 0.5
#define PATH_WAYPOINTS_PER_SEC 50
#define TRACK_LENGTH 6945.554
#define LANE_WIDTH 4
#define BUFFER_RANGE 20
#define RULES_COST 2.0
#define EFFICIENCY_COST 1.0
#define SAFETY_COST 2.0
#define MAX_COST 1

#endif