/*---------------------------- Inlcude ---------------------------------------*/
#include <CoOS.h>			              /*!< CoOS header file	         */

/*---------------------------- Symbol Define -------------------------------*/
#define STACK_SIZE_TASKA 128              /*!< Define "taskA" task size */
#define STACK_SIZE_TASKB 128              /*!< Define "taskA" task size */
#define STACK_SIZE_TASKC 128              /*!< Define "taskA" task size */

/*---------------------------- Variable Define -------------------------------*/
OS_STK     taskA_stk[STACK_SIZE_TASKA];	  /*!< Define "taskA" task stack */
OS_STK     taskB_stk[STACK_SIZE_TASKB];	  /*!< Define "taskB" task stack */
OS_STK     taskC_stk[STACK_SIZE_TASKC];	  /*!< Define "led" task stack   */

typedef struct
		{
	long m1;
	unsigned long m2;
	long m3;
		}test_t;

const test_t par={345,20,130};

//void taskA (unsigned int st);
//void taskB (test_t* p);
//void taskC (void* pdata);


/**
 *******************************************************************************
 * @brief       "taskA" task code
 * @param[in]   None	
 * @param[out]  None
 * @retval      None	 
 * @par Description
 * @details    This task use to crate mutex and flags,print message "taskA running". 
 *             Indicate "taskA" had been executed.  
 *******************************************************************************
 */
void taskA (unsigned int st)
{
  unsigned int led_num;
  led_num=st;
  for (;;) {
	led_num++;       
	CoTickDelay (50);
  }
}


/**
 *******************************************************************************
 * @brief       "taskB" task code
 * @param[in]   None	
 * @param[out]  None
 * @retval      None	 
 * @par Description
 * @details    This task use to print message "taskB running". Indicate "taskB"
 *             had been executed.  
 *******************************************************************************
 */
void taskB (test_t* p){
  unsigned int led_num;
  led_num=p->m3;
  for (;;) {
	led_num++;       
	CoTickDelay (50);
  }
}


/**
 *******************************************************************************
 * @brief       "led" task code
 * @param[in]   None	
 * @param[out]  None
 * @retval      None	 
 * @par Description
 * @details    This function use to blink led,and set flag for "taskA" and "taskB".
 *******************************************************************************
 */
void taskC (void* pdata){
  unsigned int led_num;

  for (;;) {
	led_num++;       
	CoTickDelay (50);
  }
}


/**
 *******************************************************************************
 * @brief		main function	   
 * @param[in] 	None	 
 * @param[out] 	None  
 * @retval		None	 
 *******************************************************************************
 */
int main (){
  CoInitOS ();				 /*!< Initial CooCox CoOS          */

  /*!< Create three tasks	*/
  CoCreateTask ((FUNCPtr)taskA,(void *)123,0,&taskA_stk[STACK_SIZE_TASKA-1],STACK_SIZE_TASKA);
  CoCreateTask ((FUNCPtr)taskB,(void *)&par,1,&taskB_stk[STACK_SIZE_TASKB-1],STACK_SIZE_TASKB);
  CoCreateTask ((FUNCPtr)taskC,(void *)0,2,&taskC_stk[STACK_SIZE_TASKC-1],STACK_SIZE_TASKC);
  CoStartOS ();			    /*!< Start multitask	           */  

  while (1);                /*!< The code don''t reach here	   */
}