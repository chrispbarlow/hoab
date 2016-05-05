#ifndef CONTROLSCRIPTS_H
#define CONTROLSCRIPTS_H

/* Array of legs containing the movement sequence (direction A) */
const legPositions_t resetLegScript[NUM_SEQ_STEPS] = {
        /* Step 0 */  {
        /* Hips */      {   0,    0,    0,    0,    0,    0},
        /* Knees */     {2000, 2000, 2000, 2000, 2000, 2000}
                },
        /* Step 1 */  {
        /* Hips */      {   0,    0,    0,    0,    0,    0},
        /* Knees */     {2000,  992, 2000,  992, 2000,  992}
                },
        /* Step 2 */  {
        /* Hips */      {   0, 1495,    0, 1495,    0, 1495},
        /* Knees */     {2000,  992, 2000,  992, 2000,  992}
                },
        /* Step 3 */  {
        /* Hips */      {   0, 1495,    0, 1495,    0, 1495},
        /* Knees */     {2000, 2000, 2000, 2000, 2000, 2000}
                },
        /* Step 4 */  {
        /* Hips */      {   0, 1495,    0, 1495,    0, 1495},
        /* Knees */     { 992, 2000,  992, 2000,  992, 2000}
                },
        /* Step 5 */  {
        /* Hips */      {1495, 1495, 1495, 1495, 1495, 1495},
        /* Knees */     { 992, 2000,  992, 2000,  992, 2000}
                },
            };

/* Array of legs containing the movement sequence (direction A) */
const legPositions_t sequenceLegScript[NUM_SEQ_STEPS] =  {
        /* Step 0 */  {
        /* Hips */      {1240, 1920,  992, 1255, 1920,  992},
        /* Knees */     { 992, 2000,  992, 2000,  992, 2000}
                },
        /* Step 1 */  {
        /* Hips */      {1240, 1920,  992, 1255, 1920,  992},
        /* Knees */     {2000, 2000, 2000, 2000, 2000, 2000}
                },
        /* Step 2 */  {
        /* Hips */      {1240, 1920,  992, 1255, 1920,  992},
        /* Knees */     {2000,  992, 2000,  992, 2000,  992}
                },
        /* Step 3 */  {
        /* Hips */      {2000,  992, 1755, 2000,  992, 1760},
        /* Knees */     {2000,  992, 2000,  992, 2000,  992}
                },
        /* Step 4 */  {
        /* Hips */      {2000,  992, 1755, 2000,  992, 1760},
        /* Knees */     {2000, 2000, 2000, 2000, 2000, 2000}
                },
        /* Step 5 */  {
        /* Hips */      {2000,  992, 1755, 2000,  992, 1760},
        /* Knees */     { 992, 2000,  992, 2000,  992, 2000}
                },
              };

/* TODO: Update these values */
const legPositions_t rotateLeftScript[NUM_SEQ_STEPS] =  {
        /* Step 0 */  {
        /* Hips */      {1240, 1920,  992, 1255, 1920,  992},
        /* Knees */     { 992, 2000,  992, 2000,  992, 2000}
                },
        /* Step 1 */  {
        /* Hips */      {1240, 1920,  992, 1255, 1920,  992},
        /* Knees */     {2000, 2000, 2000, 2000, 2000, 2000}
                },
        /* Step 2 */  {
        /* Hips */      {1240, 1920,  992, 1255, 1920,  992},
        /* Knees */     {2000,  992, 2000,  992, 2000,  992}
                },
        /* Step 3 */  {
        /* Hips */      {2000,  992, 1755, 2000,  992, 1760},
        /* Knees */     {2000,  992, 2000,  992, 2000,  992}
                },
        /* Step 4 */  {
        /* Hips */      {2000,  992, 1755, 2000,  992, 1760},
        /* Knees */     {2000, 2000, 2000, 2000, 2000, 2000}
                },
        /* Step 5 */  {
        /* Hips */      {2000,  992, 1755, 2000,  992, 1760},
        /* Knees */     { 992, 2000,  992, 2000,  992, 2000}
                },
              };

/* TODO: Update these values */
const legPositions_t rotateRightScript[NUM_SEQ_STEPS] =  {
        /* Step 0 */  {
        /* Hips */      {1240, 1920,  992, 1255, 1920,  992},
        /* Knees */     { 992, 2000,  992, 2000,  992, 2000}
                },
        /* Step 1 */  {
        /* Hips */      {1240, 1920,  992, 1255, 1920,  992},
        /* Knees */     {2000, 2000, 2000, 2000, 2000, 2000}
                },
        /* Step 2 */  {
        /* Hips */      {1240, 1920,  992, 1255, 1920,  992},
        /* Knees */     {2000,  992, 2000,  992, 2000,  992}
                },
        /* Step 3 */  {
        /* Hips */      {2000,  992, 1755, 2000,  992, 1760},
        /* Knees */     {2000,  992, 2000,  992, 2000,  992}
                },
        /* Step 4 */  {
        /* Hips */      {2000,  992, 1755, 2000,  992, 1760},
        /* Knees */     {2000, 2000, 2000, 2000, 2000, 2000}
                },
        /* Step 5 */  {
        /* Hips */      {2000,  992, 1755, 2000,  992, 1760},
        /* Knees */     { 992, 2000,  992, 2000,  992, 2000}
                },
              };

#endif /* CONTROLSCRIPTS_H */