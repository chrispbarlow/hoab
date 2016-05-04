/*
 * maestro.cpp
 *
 *      Author: chris.barlow
 */
#include <arduino.h>
#include "maestro.h"
#include "../motionControl/motionControl.h"

#define HIP_SERVOS	(0)
#define KNEE_SERVOS	(NUM_LEGS)

static servoControlSteps_t maestroControlStep;
static int sequenceStep;

/* Use these values to tune the position of each joint */
legPositions_t servoTuningValues = {
	{0, 0, 0, 0, 0, 0},	/* Hips */
	{0, 0, 0, 0, 0, 0}	/* Knees */
};

typedef struct{
  legPositions_t* servoSequence;
  uint16_t walkingSpeed;
}motionParameters_t;

static motionParameters_t commandedMotion;

static void maestroCommandLeg(uint8_t servo, uint8_t cmd, uint16_t value){
	Serial.write(cmd);
	Serial.write(servo);
	Serial.write(value & 0x7F);
	Serial.write((value >> 7) & 0x7F);
	Serial.read();
}

static void maestroCommandAllLegs(uint8_t offset, uint8_t cmd, uint16_t value){
	uint8_t i;
	for(i = 0; i < NUM_LEGS; i++){
		maestroCommandLeg(i+offset,cmd,value);
	}
}

static uint8_t maestroGetState(void){
	uint8_t state = 0xFF;

	Serial.write(MAESTRO_GET_STATE);
	state = Serial.read();

	return state;
}

void maestro_Init(void){
	int i;
	Serial.write(0xA1);
	Serial.read();

	maestroCommandAllLegs(HIP_SERVOS, MAESTRO_SET_SPEED, HIP_BASE_SPEED);
	maestroCommandAllLegs(KNEE_SERVOS, MAESTRO_SET_SPEED, KNEE_BASE_SPEED);

	maestroCommandAllLegs(HIP_SERVOS, MAESTRO_SET_ACCEL, 50);
	maestroCommandAllLegs(KNEE_SERVOS, MAESTRO_SET_ACCEL, 100);

	maestroControlStep = SEQUENCE_FINISHED;
}


void maestro_update(void){
	int i, tunedValue;
	uint8_t state;

	switch(maestroControlStep){
		default:
		case SEQUENCE_FINISHED:
			/* Do nothing, wait for new sequence */
			break;

		case SET_KNEES:
			/* Set command values are in 1/4 microseconds */
			for(i = 0; i < NUM_LEGS; i++){
				tunedValue = ((commandedMotion.servoSequence[sequenceStep].knee[i] * 4) + servoTuningValues.knee[i]);
				if(tunedValue < 0){
					tunedValue = 0;
				}
				maestroCommandLeg((KNEE_SERVOS+i), MAESTRO_SET_TARGET, (uint16_t)tunedValue);
			}
			maestroControlStep = SET_HIPS;
			break;

		case SET_HIPS:
			/* Set command values are in 1/4 microseconds */
			for(i = 0; i < NUM_LEGS; i++){
				tunedValue = ((commandedMotion.servoSequence[sequenceStep].hip[i] * 4) + servoTuningValues.hip[i]);
				if(tunedValue < 0){
					tunedValue = 0;
				}
				maestroCommandLeg((HIP_SERVOS+i), MAESTRO_SET_TARGET, (uint16_t)tunedValue);
			}
			maestroControlStep = WAIT_FOR_STOP;
			break;

		case WAIT_FOR_STOP:
			maestroCommandAllLegs(HIP_SERVOS, MAESTRO_SET_SPEED, commandedMotion.walkingSpeed);

			state = maestroGetState();
			if((sequenceStep >= (NUM_SEQ_STEPS-1)) && (state == 0x00)){
				maestroControlStep = SEQUENCE_FINISHED;
			}
			else if(state == 0x00){
				sequenceStep++;
				maestroControlStep = SET_KNEES;
			}
			break;
	}
}

/* Helpers for external tasks */
servoControlSteps_t maestro_checkUpdateStatus(void){
	return maestroControlStep;
}

void maestro_startNewSequence(void *sequence){
	if(maestroControlStep == SEQUENCE_FINISHED){
		commandedMotion.servoSequence = (legPositions_t*)sequence;
		sequenceStep = 0;
		maestroControlStep = SET_KNEES;
	}
	else{
		/* TODO: sequence queueing? */
	}
}

void maestro_setWalkingSpeed(uint16_t speed){
	commandedMotion.walkingSpeed = speed;
}
