/**
 * @file sm_api.c
 *
 * @brief This file contains functionalities for the state machine framework.
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
/*********************************************************************/
#include <sm_api.h>
#include <exo_osal_mem_management.h>

s_sm_obj sm[EXO_MAX_FSM];

/**
* @brief This API stores the input num_states to the num_states member
*        and assigns the address of the state_substate_map to the 
*        state_substate_map member of the s_sm_obj type
*/
e_sm_sts sm_alloc(uint8_t sm_id, uint8_t num_states)
{
    e_sm_sts status = SM_OK;

    uint8_t *state_substate_map = NULL;

    state_substate_map = (uint8_t *)os_malloc(sizeof(uint8_t));

    if(NULL != sm && NULL != state_substate_map)
    {
        sm[sm_id].state_substate_map = state_substate_map;
        sm[sm_id].num_states         = num_states;
    }
    else
    {
        status = SM_NULL_PTR;
    }

    return status;
}

/**
* @brief This API sets the state_substate_map member of the s_sm_obj type
*        to NULL.
*/
e_sm_sts sm_free(uint8_t sm_id)
{
    e_sm_sts status = SM_OK;

    if(NULL != sm)
    {
        sm[sm_id].state_substate_map = NULL;
    }
    else
    {
        status = SM_NULL_PTR;
    }

    return status;
}

/**
 * @brief This API stores the current state to the previous state and sets the
 *        current state to the passed in input state
 */
e_sm_sts sm_set_state(uint8_t sm_id, uint8_t state)
{
    e_sm_sts status = SM_OK;

    if(NULL != sm)
    {
        if (MAX_STATE_LIMIT < state)
        {
            status = SM_INVALID_STATE;
        }
        else
        {
            sm[sm_id].previous_state = sm[sm_id].current_state;
            sm[sm_id].current_state = state;
        }
    }
    else
    {
        status = SM_NULL_PTR;
    }

    return status;
}

/**
 * @brief This API stores the current sub state to the previous sub state
 *        and sets the current sub state to the passed in input sub_state
 */
e_sm_sts sm_set_substate(uint8_t sm_id, uint8_t sub_state)
{
    e_sm_sts status = SM_OK;

    if(NULL != sm)
    {
        if (MAX_STATE_LIMIT < sub_state)
        {
            status = SM_INVALID_STATE;
        }
        else
        {
            sm[sm_id].previous_substate = sm[sm_id].current_substate;
            sm[sm_id].current_substate = sub_state;
        }
    }
    else
    {
        status = SM_NULL_PTR;
    }

    return status;
}

/**
 * @brief This API stores the current state to the previous state and sets the
 *        current state as RESET_STATE
 */
e_sm_sts sm_reset_state(uint8_t sm_id)
{
    e_sm_sts status = SM_OK;

    if(NULL != sm)
    {
            sm[sm_id].previous_state = sm[sm_id].current_state;
            sm[sm_id].current_state = RESET_STATE;
    }
    else
    {
        status = SM_NULL_PTR;
    }

    return status;
}
/**
 * @brief This API return module current state
 * based in sm id
 *
 */
uint8_t sm_get_state(uint8_t sm_id)
{
    uint8_t crnt_state;
    crnt_state = sm[sm_id].current_state;
    return crnt_state;
}
