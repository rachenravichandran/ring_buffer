/******************************************************************************
 *   File Name   :   ring_buffer.h
 *	 Author      :   Rachen Ravichandran
 *	 Purpose     :   Implementation of Circular/Ring/Circular Queue Buffer
 *   Date        :   15.03.2018
******************************************************************************/

#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include<stdlib.h>
#include<stdint.h> 

#define RING_BUFFER_LENGTH 5U
/* Length of the Ring Buffer */
#define BUFFER_TYPE signed int
/* Data Type of Ring Buffer */

typedef struct RingBuffer{
                            BUFFER_TYPE ringBufferArrayPtr[RING_BUFFER_LENGTH];      /* Ring Buffer Array */
                            uint32_t head;      /* Read counter which is the index for read position */
                            uint32_t tail;      /* Write counter which is the index for write position */
                         }t_RingBuffer;

typedef enum boolean{
                        FALSE = 0,
                        TRUE = 1
                    }BOOL;

/* enum declaration for successful or failure write status */                                  
typedef enum write_status{
                            BUFFER_WRITE_SUCCESS = 0,
                            BUFFER_WRITE_FAIL = 1
                         }WRITE_STATUS;
                         
/* enum declaration for successful or failure read status */                        
typedef enum read_status{
                            BUFFER_READ_SUCCESS = 0,
                            BUFFER_READ_FAIL = 1
                        }READ_STATUS;

/*
 *   Function Name   :   initRingBuffer
 *	 Purpose         :   1. Fills the Ring Buffer array with a value specified by user
 *                       2. Initializes tail and head to -1
 *   Input           :   Ring Buffer Structure, fill_value
 *   Output          :   None
 *   Global Variable :   None
*/
void initRingBuffer(t_RingBuffer *ring_buffer, BUFFER_TYPE fill_value);

/*
 *   Function Name   :   writeRingBuffer
 *	 Purpose         :   Pushes a data into the Ring Buffer array
 *   Input           :   Ring Buffer Structure, data to be written
 *   Output          :   Returns whether the buffer write operation is SUCCESSFUL or FAIL
 *   Global Variable :   None
*/
WRITE_STATUS writeRingBuffer(t_RingBuffer *ring_buffer, BUFFER_TYPE data);

/*
 *   Function Name   :   readRingBuffer
 *	 Purpose         :   1. Pops the data out of the Ring Buffer array into a variable passed
 *                       2. Once popped, that data in the Buffer is replaced by fill_value
 *   Input           :   Ring Buffer Structure, variable into which data is to be read, fill_value
 *   Output          :   The data in the Ring Buffer is returned in FIFO mode
 *   Global Variable :   None
*/
READ_STATUS readRingBuffer(t_RingBuffer *ring_buffer, BUFFER_TYPE *readData, BUFFER_TYPE fill_value);

/*
 *   Function Name   :   isRingBufferEmpty
 *	 Purpose         :   Checks whether the Ring Buffer is EMPTY
 *   Input           :   Ring Buffer Structure
 *   Output          :   Returns 1 or TRUE if Ring Buffer is EMPTY, else returns 0 or FALSE
 *   Global Variable :   None
*/
BOOL isRingBufferEmpty(t_RingBuffer *ring_buffer);

/*
 *   Function Name   :   isRingBufferFull
 *	 Purpose         :   Checks whether the Ring Buffer is FULL
 *   Input           :   Ring Buffer Structure
 *   Output          :   Returns 1 or TRUE if Ring Buffer is FULL, else returns 0 or FALSE
 *   Global Variable :   None
*/
BOOL isRingBufferFull(t_RingBuffer *ring_buffer);

#endif /* end ifndef RING_BUFFER_H */
