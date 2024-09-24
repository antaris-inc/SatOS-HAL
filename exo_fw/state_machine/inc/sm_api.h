/**
 * @file sm_api.h
 *
 * @brief This file contains prototypes of the functionalities
 *        for the state machine framework.
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

#ifndef SM_API_H_
#define SM_API_H_

#include "exo_ral_cmn.h"

#ifdef __cplusplus
extern "C" {
#endif
/**@}*/
/**\name C standard macros */
#ifndef NULL
#ifdef __cplusplus
#define NULL                                      0
#else
#define NULL                                      ((void *) 0)
#endif
#endif
/** 
  * @brief  Error code enumeration
  */
typedef enum
{
  SM_OK = 0,             ///< Success return value
  SM_NULL_PTR = -1,      ///< Null pointer return value
  SM_INVALID_STATE = -2  ///< Invalid state
}e_sm_sts;

/** 
  * @brief  Exo state code enumeration
  */
typedef enum
{
  OBC_MAIN_FSM = 0,     ///< OBC MAIN FSM
  COMMS_SBAND_FSM,      ///< COMMS SBAND FSM
  COMMS_UHF_FSM,      ///< COMMS UHF FSM
  COMMS_XBAND_FSM,      ///< COMMS XBAND FSM
  ADCS_FSM,             ///< ADCS FSM
  EXO_MAX_FSM           ///< Maximum limit
}e_exo_fsm;

/** 
  * @brief  State code enumeration
  */
typedef enum
{
  RESET_STATE = 0,           ///< Reset state
  MAX_STATE_LIMIT = 255      ///< Maximum state limit
}e_sm_state;

/**
  * @brief state machine parameters structure definition
  *
  */
typedef struct
{
    uint8_t   current_state;           /*!< Current state of the system */
    uint8_t   previous_state;          /*!< Previous state of the system */
    uint8_t   current_substate;        /*!< Current sub state */
    uint8_t   previous_substate;       /*!< Previous sub state */
    uint8_t   *state_substate_map;     /*!< Pointer to state and sub state map table */
    uint8_t   num_states;              /*!< Number of states */
}s_sm_obj;

/**
 * @brief This API stores the input num_states to the num_states member
 *        and assigns the address of the state_substate_map to the
 *        state_substate_map member of the s_sm_obj type
 *
 * @param[in] sm_id : state machine id
 * @param[in] num_states : Number of states
 *
 * @return Result of API execution status
 * @retval SM_OK -> Success, SM_NULL_PTR -> Error.
 */
e_sm_sts sm_alloc(uint8_t sm_id, uint8_t num_states);

/**
 * @brief This API sets the state_substate_map member of the s_sm_obj type
 *        to NULL.
 *
 * @param[in] sm_id : state machine id
 *
 * @return Result of API execution status
 * @retval SM_OK -> Success, SM_NULL_PTR -> Error.
 */
e_sm_sts sm_free(uint8_t sm_id);

/**
 * @brief This API stores the current state to the previous state and sets the
 *        current state to the passed in input state
 *
 * @param[in] sm_id : state machine id
 * @param[in] state : system state
 *
 * @return Result of API execution status
 * @retval SM_OK -> Success, SM_NULL_PTR -> Error.
 */
e_sm_sts sm_set_state(uint8_t sm_id, uint8_t state);

/**
 * @brief This API stores the current sub state to the previous sub state
 *        and sets the current sub state to the passed in input sub_state
 *
 * @param[in] sm_id : state machine id
 * @param[in] sub_state : sub state id
 *
 * @return Result of API execution status
 * @retval SM_OK -> Success, SM_NULL_PTR -> Error.
 */
e_sm_sts sm_set_substate(uint8_t sm_id, uint8_t sub_state);

/**
 * @brief This API stores the current state to the previous state and sets the
 *        current state as RESET_STATE
 *
 * @param[in] sm_id : state machine id
 *
 * @return Result of API execution status
 * @retval SM_OK -> Success, SM_NULL_PTR -> Error.
 */
e_sm_sts sm_reset_state(uint8_t sm_id);

/**
 * @brief This API return module current state
 *  based in sm id
 *
 * @param[in] sm_id : Module ID
 *
 * @return current state
 */
uint8_t sm_get_state(uint8_t sm_id);

#ifdef __cplusplus
}
#endif
#endif /*SM_API_H_ */
