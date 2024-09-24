/**
 * @file exo_os_common.h
 *
 * @brief This file contains RAL related header file inclusion.
 *
 * @copyright Copyright 2024 Antaris, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef OS_COMMON_H
#define OS_COMMON_H

#include <stdio.h>
#include "exo_ral_common.h"
#include "exo_ral_cmn.h"

#ifdef LINUX_TEMP_PORT
#include "exo_ral_linux_os.h"
#else
#include "exo_ral_cmsis_os.h"
#include "cmsis_os2.h"
#endif

#endif /*OS_COMMON_H*/
