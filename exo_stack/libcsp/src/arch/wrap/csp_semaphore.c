/*
Cubesat Space Protocol - A small network-layer protocol designed for Cubesats
Copyright (C) 2012 Gomspace ApS (http://www.gomspace.com)
Copyright (C) 2012 AAUSAT3 Project (http://aausat3.space.aau.dk) 

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "csp_semaphore.h"
#include "csp_debug.h"


#ifndef OSAL_EN //ANTARIS_PORT
int csp_mutex_create(csp_mutex_t * mutex) {
	*mutex = xSemaphoreCreateMutex();
	if (*mutex) {
		return CSP_SEMAPHORE_OK;
	} else {
		return CSP_SEMAPHORE_ERROR;
	}
}

int csp_mutex_remove(csp_mutex_t * mutex) {
	return csp_bin_sem_remove(mutex);
}

int csp_mutex_lock(csp_mutex_t * mutex, uint32_t timeout) {
	return csp_bin_sem_wait(mutex, timeout);
}

int csp_mutex_unlock(csp_mutex_t * mutex) {
	return csp_bin_sem_post(mutex);
}

int csp_bin_sem_create(csp_bin_sem_handle_t * sem) {
	vSemaphoreCreateBinary(*sem);
	return CSP_SEMAPHORE_OK;
}

int csp_bin_sem_remove(csp_bin_sem_handle_t * sem) {
	if ((sem != NULL) && (*sem != NULL)) {
		vSemaphoreDelete(*sem);
	}
	return CSP_SEMAPHORE_OK;
}

int csp_bin_sem_wait(csp_bin_sem_handle_t * sem, uint32_t timeout) {
	csp_log_lock("Wait: %p", sem);
	if (timeout != CSP_MAX_TIMEOUT) {
		timeout = timeout / portTICK_RATE_MS;
	}
	if (xSemaphoreTake(*sem, timeout) == pdPASS) {
		return CSP_SEMAPHORE_OK;
	}
	return CSP_SEMAPHORE_ERROR;
}

int csp_bin_sem_post(csp_bin_sem_handle_t * sem) {
	csp_log_lock("Post: %p", sem);
	if (xSemaphoreGive(*sem) == pdPASS) {
		return CSP_SEMAPHORE_OK;
	}
	return CSP_SEMAPHORE_ERROR;
}

int csp_bin_sem_post_isr(csp_bin_sem_handle_t * sem, CSP_BASE_TYPE * pxTaskWoken) {
	csp_log_lock("Post: %p", sem);
	if (xSemaphoreGiveFromISR(*sem, pxTaskWoken) == pdPASS) {
		return CSP_SEMAPHORE_OK;
	} else {
		return CSP_SEMAPHORE_ERROR;
	}
}
#else
int csp_mutex_create(csp_mutex_t * mutex)
{
	os_status_t sts = os_mutex_create(mutex);
	if (sts==ral_success) {
		return CSP_SEMAPHORE_OK;
	} else {
		return CSP_SEMAPHORE_ERROR;
	}
}
int csp_mutex_remove(csp_mutex_t * mutex)
{
	return os_mutex_delete(*mutex);
}
int csp_mutex_lock(csp_mutex_t * mutex, uint32_t timeout)
{
	return os_mutex_take(*mutex,timeout);
}
int csp_mutex_unlock(csp_mutex_t * mutex) {
	return os_mutex_give(*mutex);
}
int csp_bin_sem_create(csp_bin_sem_handle_t * sem)
{
	os_sem_create_bin(sem);
	return CSP_SEMAPHORE_OK;
}
int csp_bin_sem_remove(csp_bin_sem_handle_t * sem)
{
	return os_sem_delete(*sem);
}
int csp_bin_sem_wait(csp_bin_sem_handle_t * sem, uint32_t timeout)
{
	if (os_sem_take(*sem,timeout) == os_success) {
		return CSP_SEMAPHORE_OK;
	}
	return CSP_SEMAPHORE_ERROR;
}
int csp_bin_sem_post(csp_bin_sem_handle_t * sem)
{
	if (os_sem_give(*sem) == os_success)
	{
		return CSP_SEMAPHORE_OK;
	}
	return CSP_SEMAPHORE_ERROR;

}
int csp_bin_sem_post_isr(csp_bin_sem_handle_t * sem, CSP_BASE_TYPE * pxTaskWoken)
{
	return os_sem_give(*sem);
}
#endif
