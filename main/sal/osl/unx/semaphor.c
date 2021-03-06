/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/




#include "system.h"

#include <osl/semaphor.h>
#include <osl/diagnose.h>

#ifndef OSL_USE_SYS_V_SEMAPHORE

/* This is the (default) POSIX thread-local semaphore variant */

/*
	Implemetation notes:
	The void* represented by oslSemaphore is used
	as a pointer to an sem_t struct
*/

/*****************************************************************************/
/* osl_createSemaphore  */
/*****************************************************************************/

oslSemaphore SAL_CALL osl_createSemaphore(sal_uInt32 initialCount) 
{
	int ret = 0;
	oslSemaphore Semaphore;

	Semaphore= malloc(sizeof(sem_t));

	OSL_ASSERT(Semaphore);		/* ptr valid? */

	if ( Semaphore == 0 )
	{
		return 0;
	}
	
	/* unnamed semaphore, not shared between processes */

   	ret= sem_init((sem_t*)Semaphore, 0, initialCount);

	/* create failed? */
	if (ret != 0)
	{
	    OSL_TRACE("osl_createSemaphore failed. Errno: %d; %s\n", 
				  errno, 
				  strerror(errno));

	    free(Semaphore);
	    Semaphore = NULL;
	}
	
	return Semaphore;
}

/*****************************************************************************/
/* osl_destroySemaphore  */
/*****************************************************************************/
void SAL_CALL osl_destroySemaphore(oslSemaphore Semaphore)
{
	if(Semaphore)			/* ptr valid? */
	{
		sem_destroy((sem_t*)Semaphore);
	    free(Semaphore);
	}
}

/*****************************************************************************/
/* osl_acquireSemaphore  */
/*****************************************************************************/
sal_Bool SAL_CALL osl_acquireSemaphore(oslSemaphore Semaphore) {
	
	OSL_ASSERT(Semaphore != 0);	/* abort in debug mode */

	if (Semaphore != 0)		/* be tolerant in release mode */
	{
	    return (sem_wait((sem_t*)Semaphore) == 0);
	}

	return sal_False;
}

/*****************************************************************************/
/* osl_tryToAcquireSemaphore  */
/*****************************************************************************/
sal_Bool SAL_CALL osl_tryToAcquireSemaphore(oslSemaphore Semaphore) {
	
	OSL_ASSERT(Semaphore != 0);	/* abort in debug mode */
	if (Semaphore != 0)		/* be tolerant in release mode */
	{
	    return (sem_trywait((sem_t*)Semaphore) == 0);
	}

	return sal_False;
}

/*****************************************************************************/
/* osl_releaseSemaphore  */
/*****************************************************************************/
sal_Bool SAL_CALL osl_releaseSemaphore(oslSemaphore Semaphore) {

	OSL_ASSERT(Semaphore != 0);		/* abort in debug mode */
	
	if (Semaphore != 0)			/* be tolerant in release mode */
	{
	    return (sem_post((sem_t*)Semaphore) == 0);
	}

	return sal_False;
}

#else /* OSL_USE_SYS_V_SEMAPHORE */

/*******************************************************************************/

/* This is the SYS V private semaphore variant */

/*
	Implemetation notes:
	The void* represented by oslSemaphore is used
	as a pointer to an osl_TSemImpl struct
*/


#if defined(NETBSD)
union semun {
        int     val;            /* value for SETVAL */
        struct  semid_ds *buf;  /* buffer for IPC_STAT & IPC_SET */
        u_short *array;         /* array for GETALL & SETALL */
};
#endif

typedef struct _osl_TSemImpl
{
  int m_Id;

} osl_TSemImpl;

/*****************************************************************************/
/* osl_createSemaphore  */
/*****************************************************************************/
oslSemaphore SAL_CALL osl_createSemaphore(sal_uInt32 initialCount) 
{
	union semun arg;
	
	oslSemaphore Semaphore;
	osl_TSemImpl* pSem;

	Semaphore= malloc(sizeof(osl_TSemImpl));
	OSL_POSTCOND(Semaphore, "malloc failed\n");		/* ptr valid? */

	pSem= (osl_TSemImpl*)Semaphore;


	/* unnamed (private) semaphore */

   	pSem->m_Id= semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);


	/* create failed? */
	if (pSem->m_Id < 0)
	{
	    OSL_TRACE("osl_createSemaphore failed (semget). Errno: %d; %s\n", 
			   errno, 
			   strerror(errno));

	    free(Semaphore);
	    return 0;
	}

    /* set initial count */

    arg.val= initialCount;

	if(semctl(pSem->m_Id, 0, SETVAL, arg) < 0)
	{
	    OSL_TRACE("osl_createSemaphore failed (semctl(SETVAL)). Errno: %d; %s\n", 
			   errno, 
			   strerror(errno));

		if(semctl(pSem->m_Id, 0, IPC_RMID, arg) < 0)
		{
		    OSL_TRACE("semctl(IPC_RMID) failed. Errno: %d; %s\n", errno, strerror(errno));
	    }
		
		free(Semaphore);
		return 0;
	}
    
	
	return Semaphore;
}

/*****************************************************************************/
/* osl_destroySemaphore  */
/*****************************************************************************/
void SAL_CALL osl_destroySemaphore(oslSemaphore Semaphore) {
	
	if(Semaphore)			/* ptr valid? */
	{
		union semun arg;

	    osl_TSemImpl* pSem= (osl_TSemImpl*)Semaphore;

		if(semctl(pSem->m_Id, 0, IPC_RMID, arg) < 0)

		{
		    OSL_TRACE("osl_destroySemaphore failed. (semctl(IPC_RMID)). Errno: %d; %s\n", 
				   errno, 
				   strerror(errno));			
	    }
		
	    free(Semaphore);
	}
}

/*****************************************************************************/
/* osl_acquireSemaphore  */
/*****************************************************************************/
sal_Bool SAL_CALL osl_acquireSemaphore(oslSemaphore Semaphore) {
	
	/* abort in debug mode */
	OSL_PRECOND(Semaphore != 0, "Semaphore not created\n");	


	if (Semaphore != 0)		/* be tolerant in release mode */
	{
	    struct sembuf op;
		osl_TSemImpl* pSem= (osl_TSemImpl*)Semaphore;

		op.sem_num= 0;
		op.sem_op= -1;
		op.sem_flg= SEM_UNDO;

		return semop(pSem->m_Id, &op, 1) >= 0;

	}

	return sal_False;
}

/*****************************************************************************/
/* osl_tryToAcquireSemaphore  */
/*****************************************************************************/
sal_Bool SAL_CALL osl_tryToAcquireSemaphore(oslSemaphore Semaphore) {
	
	/* abort in debug mode */
	OSL_PRECOND(Semaphore != 0, "Semaphore not created\n");	

	if (Semaphore != 0)		/* be tolerant in release mode */
	{
	    struct sembuf op;
		osl_TSemImpl* pSem= (osl_TSemImpl*)Semaphore;

		op.sem_num= 0;
		op.sem_op= -1;
		op.sem_flg= SEM_UNDO | IPC_NOWAIT;

		return semop(pSem->m_Id, &op, 1) >= 0;
	}

	return sal_False;
}

/*****************************************************************************/
/* osl_releaseSemaphore  */
/*****************************************************************************/
sal_Bool SAL_CALL osl_releaseSemaphore(oslSemaphore Semaphore) 
{

	/* abort in debug mode */
	OSL_PRECOND(Semaphore != 0, "Semaphore not created\n");	
	
	if (Semaphore != 0)			/* be tolerant in release mode */
	{
	    struct sembuf op;
		osl_TSemImpl* pSem= (osl_TSemImpl*)Semaphore;

		op.sem_num= 0;
		op.sem_op= 1;
		op.sem_flg= SEM_UNDO;

		return semop(pSem->m_Id, &op, 1) >= 0;
	}

	return sal_False;
}

#endif /* OSL_USE_SYS_V_SEMAPHORE */

