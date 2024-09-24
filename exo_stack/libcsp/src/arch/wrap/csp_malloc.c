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

#include "csp_malloc.h"

#include <string.h>
#include "exo_osal.h"


#ifndef OSAL_EN
#include <FreeRTOS.h>

void * csp_malloc(size_t size) {
	return pvPortMalloc(size);
}

void * csp_calloc(size_t nmemb, size_t size) {
	size = (nmemb * size); 
	void * ptr = csp_malloc(size);
	if (ptr) {
		memset(ptr, 0, size);
	}
	return ptr;
}

void csp_free(void *ptr) {
	vPortFree(ptr);
}
#else
void * csp_malloc(size_t size) {
	return (os_malloc_eram((uint32_t)size));
}
void * csp_calloc(size_t nmemb, size_t size) {
	size = (nmemb * size);
	void * ptr = csp_malloc(size);
	if (ptr) {
		memset(ptr, 0, size);
	}
	return ptr;
}
void csp_free(void *ptr) {

	os_free(ptr);
	ptr = NULL;
}

#endif
