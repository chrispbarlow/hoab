/*
 * motionControl.h
 *
 *  Created on: 4 Apr 2014
 *      Author: chris.barlow
 */

#ifndef motionControl_H_
#define motionControl_H_

#define NUM_SEQ_STEPS 	(6)
#define NUM_LEGS	(6)
#define HIP_BASE_SPEED (400)
#define KNEE_BASE_SPEED (0)

/* 6-step sequences for hips and knees */
typedef struct {
	int hip[NUM_LEGS];
	int knee[NUM_LEGS];
} legPositions_t;

typedef enum{DIR_A = 0, DIR_B = 1, DIR_C = 2, DIR_D = 3, DIR_E  = 4, DIR_F = 5}directions_t;
typedef enum{STOP, WALK, ROTATE_L, ROTATE_R, RESET}movement_t;

void motionControl_Init(void);
void motionControl_update(void);


#endif /* motionControl_H_ */