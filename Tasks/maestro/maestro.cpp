/*
 * maestro.cpp
 *
 *      Author: chris.barlow
 */
#include <arduino.h>
#include <Tasks.h>
#include "../motionControl/motionControl.h"

#include "maestro.h"


MaestroPlugin maestro;

servoControlSteps_t MaestroPlugin::maestroControlStep;
uint16_t MaestroPlugin::stepCount;
uint16_t *MaestroPlugin::servoSequence;
uint16_t MaestroPlugin::servoSpeeds[12];
uint16_t MaestroPlugin::servoAccels[12];
uint16_t MaestroPlugin::sequenceStep;
uint16_t MaestroPlugin::servoNum;


/* Use these values to tune the position of each joint TODO: open this up to the plugin API */
legPositions_t servoTuningValues = {
	{0, 0, 0, 0, 0, 0},	/* Hips */
	{0, 0, 0, 0, 0, 0}	/* Knees */
};


void MaestroPlugin::maestroCommandLeg(uint8_t servo, uint8_t cmd, uint16_t value){
	Serial.write(cmd);
	Serial.write(servo);
	Serial.write(value & 0x7F);
	Serial.write((value >> 7) & 0x7F);
	Serial.read();
}

void MaestroPlugin::maestroCommandAllLegs(uint8_t offset, uint8_t cmd, uint16_t value){
	uint8_t i;
	for(i = 0; i < NUM_LEGS; i++){
		maestroCommandLeg(i+offset,cmd,value);
	}
}

uint8_t MaestroPlugin::maestroGetState(void){
	uint8_t state = 0xFF;

	Serial.write(MAESTRO_GET_STATE);
	state = Serial.read();

	return state;
}

void MaestroPlugin::init(void){
	Serial.write(0xA1);
	Serial.read();

	sequenceStep = 0;
	servoNum = 0;
	maestroControlStep = SEQUENCE_FINISHED;
}


void MaestroPlugin::update(void){
	int i = 0;
	int tunedValue;
	uint8_t state;

	switch(maestroControlStep){
		default:
		case SEQUENCE_FINISHED:
			/* Do nothing, wait for new sequence */
			break;

		case SENDING_SEQUENCE:
			/* Set command values are in 1/4 microseconds */
			i = servoNum + (sequenceStep*12);
			tunedValue = ((servoSequence[i] * 4) + servoTuningValues.knee[servoNum]);
			if(tunedValue < 0){
				tunedValue = 0;
			}
			maestroCommandLeg(servoNum, MAESTRO_SET_TARGET, (uint16_t)tunedValue);

			if(++servoNum >= 12){
				maestroControlStep = WAIT_FOR_STOP;
				servoNum = 0;
			}
			break;

		case WAIT_FOR_STOP:
			// Serial.write('~');
			// Serial.write(maestroControlStep);
			// Serial.write('~');
#ifdef PRETEND_TO_BE_STOPPED
#warning "test mode won't wait for servos to stop"
			state = 0;
#else
			state = maestroGetState();
#endif
			// Serial.print("State = ");
			// Serial.println(state);

			if((state == 0x00) && (++sequenceStep >= stepCount)){
				sequenceStep = 0;
				maestroControlStep = SEQUENCE_FINISHED;
			}
			else if(state == 0x00){
				maestroControlStep = SENDING_SEQUENCE;
			}

			// Serial.write('~');
			// Serial.write(sequenceStep);
			// Serial.write('~');
			// Serial.write(stepCount);
			// Serial.write('~');
			// Serial.write(maestroControlStep);
			// Serial.write('~');

			break;
	}
}

/* Helpers for external tasks */
servoControlSteps_t MaestroPlugin::checkUpdateStatus(void){
	return maestroControlStep;
}

void MaestroPlugin::startNewSequence(uint16_t *sequence, uint16_t count){
	if(maestroControlStep == SEQUENCE_FINISHED){
		servoSequence = sequence;
		stepCount = count;
		// Serial.write('{');
		// Serial.write(stepCount);
		// Serial.write('}');

		sequenceStep = 0;
		maestroControlStep = SENDING_SEQUENCE;
	}
	else{
		/* TODO: sequence queueing? */
	}
}

void MaestroPlugin::setSpeeds(uint16_t speeds[]){
	static bool speedSet = false;
	int i;

	if(speedSet == false){
		for(i = 0; i < 12; i++){
			servoSpeeds[i] = 0xFFFF;
		}
		speedSet = true;
	}

	for(i = 0; i < 12; i++){
		if(speeds[i] != servoSpeeds[i]){
			maestroCommandLeg(i, MAESTRO_SET_SPEED, speeds[i]);
			servoSpeeds[i] = speeds[i];
		}
	}
}

void MaestroPlugin::setAccelerations(uint16_t accels[]){
	static bool accelSet = false;
	int i;

	if(accelSet == false){
		for(i = 0; i < 12; i++){
			servoAccels[i] = 0xFFFF;
		}
		accelSet = true;
	}

	for(i = 0; i < 12; i++){
		if(accels[i] != servoAccels[i]){
			maestroCommandLeg(i, MAESTRO_SET_ACCEL, accels[i]);
			servoAccels[i] = accels[i];
		}
	}
}
