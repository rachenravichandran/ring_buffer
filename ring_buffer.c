/******************************************************************************
 *   File Name   :   ring_buffer.c
 *	 Author      :   Rachen Ravichandran
 *	 Purpose     :   Implementation of Circular/Ring/Circular Queue Buffer
 *   Date        :   15.03.2018
******************************************************************************/

#include"ring_buffer.h"

/*
 *   Function Name   :   initRingBuffer
 *	 Purpose         :   1. Fills the Ring Buffer array with a value specified by user
 *                       2. Initializes tail and head to -1
 *   Input           :   Ring Buffer Structure, fill_value
 *   Output          :   None
 *   Global Variable :   None
*/
void initRingBuffer(t_RingBuffer *ring_buffer, BUFFER_TYPE fill_value)
{
    uint32_t count = 0U;
    while(count < RING_BUFFER_LENGTH)
    {
        ring_buffer->ringBufferArrayPtr[count++] = fill_value;
    }
    /*Fills the Ring Buffer with the fill_value passed to the function*/
    
    ring_buffer->tail = -1;
    ring_buffer->head = -1;
    /*tail = head = -1 indicates the initial or underflow condition*/
}

/*
 *   Function Name   :   writeRingBuffer
*	 Purpose         :   Pushes a data into the Ring Buffer array
 *   Input           :   Ring Buffer Structure, data to be written
 *   Output          :   Returns whether the buffer write operation is SUCCESSFUL or FAIL
 *   Global Variable :   None
*/
WRITE_STATUS writeRingBuffer(t_RingBuffer *ring_buffer, BUFFER_TYPE data)
{
    WRITE_STATUS returnStatus;
    if((ring_buffer->tail == ring_buffer->head && ring_buffer->head != -1) || 
       (ring_buffer->tail == RING_BUFFER_LENGTH - 1 && ring_buffer->head == -1))
    /* When head equals tail, except at initial condition ( = -1) OR */
    /* When tail reaches RING BUFFER LENGTH and no data is read yet i.e., head = -1, the Buffer is FULL */
    {
        returnStatus = BUFFER_WRITE_FAIL;
    }
    else
    {   
        ring_buffer->tail = (++ring_buffer->tail)%RING_BUFFER_LENGTH;
        /*When tail exceeds the RING BUFFER LENGTH, it is reset to 0*/
        ring_buffer->ringBufferArrayPtr[ring_buffer->tail] = data;
        /*Data is written to the Ring Buffer Array at the tail index*/
        returnStatus = BUFFER_WRITE_SUCCESS;
    }
    return returnStatus;    
}

/*
 *   Function Name   :   readRingBuffer
 *	 Purpose         :   1. Pops the data out of the Ring Buffer array into a variable passed
 *                       2. Once popped, that data in the Buffer is replaced by fill_value
 *   Input           :   Ring Buffer Structure, variable into which data is to be read, fill_value
 *   Output          :   The data in the Ring Buffer is returned in FIFO mode
 *   Global Variable :   None
*/
READ_STATUS readRingBuffer(t_RingBuffer *ring_buffer, BUFFER_TYPE *readData, BUFFER_TYPE fill_value)
{
    READ_STATUS returnStatus;
    if(ring_buffer->tail == -1 && ring_buffer->head == -1)
    /*tail = head = -1 indicates the initial or underflow condition*/
    {
        returnStatus = BUFFER_READ_FAIL;
    }
    else
    {
        ring_buffer->head = (++ring_buffer->head)%RING_BUFFER_LENGTH;
        /*When head exceeds the RING BUFFER LENGTH, it is reset to 0*/
        *readData = ring_buffer->ringBufferArrayPtr[ring_buffer->head];
        /*Element is read from the Ring Buffer Array at the head index */
        /*and stored in the address of the readData variable passed by the function*/
        
        ring_buffer->ringBufferArrayPtr[ring_buffer->head] = fill_value;
        /*Once popped, that data in the Buffer is replaced by fill_value*/ 
        if(ring_buffer->tail == ring_buffer->head)
        /*This condition indicates an underflow, immediately after a read operation*/
        {
            ring_buffer->tail = -1;
            ring_buffer->head = -1;
            /*head and tail is reset to -1 to indicate initial or underflow condition*/
        }
        returnStatus = BUFFER_READ_SUCCESS;
    }
    return returnStatus;
    
}

/*
 *   Function Name   :   isRingBufferEmpty
 *	 Purpose         :   Checks whether the Ring Buffer is EMPTY
 *   Input           :   Ring Buffer Structure
 *   Output          :   Returns 1 or TRUE if Ring Buffer is EMPTY, else returns 0 or FALSE
 *   Global Variable :   None
*/
BOOL isRingBufferEmpty(t_RingBuffer *ring_buffer)
{
    BOOL returnStatus;
    if(ring_buffer->tail == -1 && ring_buffer->head == -1)
    /*tail = head = -1 indicates the initial or underflow condition*/
    {
        returnStatus = TRUE;
    }
    else
    {
        returnStatus = FALSE;
    }
    return returnStatus;
}

/*
 *   Function Name   :   isRingBufferFull
 *	 Purpose         :   Checks whether the Ring Buffer is FULL
 *   Input           :   Ring Buffer Structure
 *   Output          :   Returns 1 or TRUE if Ring Buffer is FULL, else returns 0 or FALSE
 *   Global Variable :   None
*/
BOOL isRingBufferFull(t_RingBuffer *ring_buffer)
{
    BOOL returnStatus;
    if((ring_buffer->tail == ring_buffer->head && ring_buffer->head != -1) || 
       (ring_buffer->tail == RING_BUFFER_LENGTH - 1 && ring_buffer->head == -1))
    /* When head equals tail, except at initial condition ( = -1) OR */
    /* When tail reaches RING BUFFER LENGTH and no data is read yet i.e., head = -1, the Buffer is FULL */
    {
        returnStatus = TRUE;
    }
    else
    {
        returnStatus = FALSE;
    }
    return returnStatus;
}
