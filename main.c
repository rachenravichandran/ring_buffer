/******************************************************************************
 *   File Name   :   main.c
 *	 Author      :   Rachen Ravichandran
 *	 Purpose     :   Verification of Ring Buffer
 *   Date        :   15.03.2018
******************************************************************************/

#include <stdio.h>

/* Includes the function and structure definitions for Ring Buffer */
#include "ring_buffer.h"

int main(void)
{
    uint32_t i;
    uint32_t choice;                 /* choice for Read or Write option */ 
    BUFFER_TYPE data;                /* Data to be written or read */
    t_RingBuffer ring_buffer;        /* Instance variable of ring buffer */
    initRingBuffer(&ring_buffer,0);  /* Initialize the Ring Buffer with fill_value = 0*/
    
    while(1)
    {
        printf("Do you want to read/write?\nPress 1 for write and any key for read. ");
        scanf("%d",&choice);
        
        if(choice == 1)
        {
            printf("Enter data\n");
            scanf("%d",&data);
            if(BUFFER_WRITE_FAIL == writeRingBuffer(&ring_buffer,data))  /* Checks whether buffer is full or not */
            {
                printf("Buffer Overflow\n");
            }
            else
            {
                printf("%d is written\n",data);
            }
            
            printf("\n|");
            for(i = 0; i<RING_BUFFER_LENGTH; i++)
            {
                printf(" %d |",ring_buffer.ringBufferArrayPtr[i]);     /* Print the elements of ring buffer */
            }
            printf("\n\n\n");
        }
        else
        {
            if(BUFFER_READ_FAIL == readRingBuffer(&ring_buffer,&data,0))  /* Checks whether buffer is empty or not */
            {
                printf("Buffer Underflow\n");
            }
            else
            {
                printf("%d is read\n",data);
            }
            
            printf("\n|");
            for(i = 0; i<RING_BUFFER_LENGTH; i++)
            {
                printf(" %d |",ring_buffer.ringBufferArrayPtr[i]);     /* Print the elements of ring buffer */
            }
            printf("\n\n\n");
        }
        
        fflush(stdin);
        printf("Press any key to continue...");
        getch();            /* Wait for a character */
        system("cls");      /* Clear the screen */
    }
    return 0;
}
