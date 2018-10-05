#ifndef OSAL_H
#define OSAL_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */
#include "data_type.h"




/*********************************************************************
 * FUNCTIONS
 */

/*** Task Synchronization  ***/

  /*
   * Set a Task Event
   */
  extern uint8 osal_set_event( uint8 task_id, uint16 event_flag );


  /*
   * Clear a Task Event
   */
  extern uint8 osal_clear_event( uint8 task_id, uint16 event_flag );


/*** Task Management  ***/

  /*
   * One Pass Through the OSAL Processing Loop
   */
  extern void osal_run_system( void );

#ifdef __cplusplus
}
#endif

#endif /* OSAL_H */
