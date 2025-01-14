/*
 * Copyright (c) 2018 - 2021, Nordic Semiconductor ASA
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef NRF_CCM_H__
#define NRF_CCM_H__

#include <nrfx.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrf_ccm_hal AES CCM HAL
 * @{
 * @ingroup nrf_ccm
 * @brief   Hardware access layer for managing the AES CCM peripheral.
 */

/** @brief CCM tasks. */
typedef enum {
  NRF_CCM_TASK_KSGEN =
      offsetof(NRF_CCM_Type, TASKS_KSGEN), ///< Start generation of key-stream.
  NRF_CCM_TASK_CRYPT =
      offsetof(NRF_CCM_Type, TASKS_CRYPT), ///< Start encryption/decryption.
  NRF_CCM_TASK_STOP =
      offsetof(NRF_CCM_Type, TASKS_STOP), ///< Stop encryption/decryption.
#if defined(CCM_RATEOVERRIDE_RATEOVERRIDE_Pos) || defined(__NRFX_DOXYGEN__)
  NRF_CCM_TASK_RATEOVERRIDE = offsetof(
      NRF_CCM_Type,
      TASKS_RATEOVERRIDE), ///< Override DATARATE setting in MODE register.
#endif
} nrf_ccm_task_t;

/** @brief CCM events. */
typedef enum {
  NRF_CCM_EVENT_ENDKSGEN = offsetof(
      NRF_CCM_Type, EVENTS_ENDKSGEN), ///< Keystream generation complete.
  NRF_CCM_EVENT_ENDCRYPT =
      offsetof(NRF_CCM_Type, EVENTS_ENDCRYPT), ///< Encrypt/decrypt complete.
  NRF_CCM_EVENT_ERROR =
      offsetof(NRF_CCM_Type, EVENTS_ERROR), ///< CCM error event.
} nrf_ccm_event_t;

/** @brief Types of CCM shorts. */
typedef enum {
  NRF_CCM_SHORT_ENDKSGEN_CRYPT_MASK =
      CCM_SHORTS_ENDKSGEN_CRYPT_Msk, ///< Shortcut for starting
                                     ///< encryption/decryption when the
                                     ///< key-stream generation is complete.
} nrf_ccm_short_mask_t;

/** @brief CCM interrupts. */
typedef enum {
  NRF_CCM_INT_ENDKSGEN_MASK =
      CCM_INTENSET_ENDKSGEN_Msk, ///< Interrupt on ENDKSGEN event.
  NRF_CCM_INT_ENDCRYPT_MASK =
      CCM_INTENSET_ENDCRYPT_Msk, ///< Interrupt on ENDCRYPT event.
  NRF_CCM_INT_ERROR_MASK =
      CCM_INTENSET_ERROR_Msk, ///< Interrupt on ERROR event.
} nrf_ccm_int_mask_t;

/** @brief CCM modes of operation. */
typedef enum {
  NRF_CCM_MODE_ENCRYPTION = CCM_MODE_MODE_Encryption, ///< Encryption mode.
  NRF_CCM_MODE_DECRYPTION = CCM_MODE_MODE_Decryption, ///< Decryption mode.
} nrf_ccm_mode_t;

#if defined(CCM_MODE_DATARATE_Pos) || defined(__NRFX_DOXYGEN__)
/** @brief CCM data rates. */
typedef enum {
  NRF_CCM_DATARATE_1M = CCM_MODE_DATARATE_1Mbit, ///< 1 Mbps.
  NRF_CCM_DATARATE_2M = CCM_MODE_DATARATE_2Mbit, ///< 2 Mbps.
#if defined(CCM_MODE_DATARATE_125Kbps) || defined(__NRFX_DOXYGEN__)
  NRF_CCM_DATARATE_125K = CCM_MODE_DATARATE_125Kbps, ///< 125 Kbps.
#endif
#if defined(CCM_MODE_DATARATE_500Kbps) || defined(__NRFX_DOXYGEN__)
  NRF_CCM_DATARATE_500K = CCM_MODE_DATARATE_500Kbps, ///< 500 Kbps.
#endif
} nrf_ccm_datarate_t;
#endif // defined(CCM_MODE_DATARATE_Pos) || defined(__NRFX_DOXYGEN__)

#if defined(CCM_MODE_LENGTH_Pos) || defined(__NRFX_DOXYGEN__)
/** @brief CCM packet length options. */
typedef enum {
  NRF_CCM_LENGTH_DEFAULT = CCM_MODE_LENGTH_Default,   ///< Default length.
  NRF_CCM_LENGTH_EXTENDED = CCM_MODE_LENGTH_Extended, ///< Extended length.
} nrf_ccm_length_t;
#endif // defined(CCM_MODE_LENGTH_Pos) || defined(__NRFX_DOXYGEN__)

/** @brief CCM configuration. */
typedef struct {
  nrf_ccm_mode_t mode; ///< Operation mode.
#if defined(CCM_MODE_DATARATE_Pos) || defined(__NRFX_DOXYGEN__)
  nrf_ccm_datarate_t datarate; ///< Data rate.
#endif
#if defined(CCM_MODE_LENGTH_Pos) || defined(__NRFX_DOXYGEN__)
  nrf_ccm_length_t length; ///< Lenght of the CCM packet.
#endif
} nrf_ccm_config_t;

/**
 * @brief Function for activating a specific CCM task.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 * @param[in] task  Task to be activated.
 */
NRF_STATIC_INLINE void nrf_ccm_task_trigger(NRF_CCM_Type *p_reg,
                                            nrf_ccm_task_t task);

/**
 * @brief Function for getting the address of a specific CCM task register.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 * @param[in] task  Requested task.
 *
 * @return Address of the specified task register.
 */
NRF_STATIC_INLINE uint32_t nrf_ccm_task_address_get(NRF_CCM_Type const *p_reg,
                                                    nrf_ccm_task_t task);

/**
 * @brief Function for clearing a specific CCM event.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 * @param[in] event Event to clear.
 */
NRF_STATIC_INLINE void nrf_ccm_event_clear(NRF_CCM_Type *p_reg,
                                           nrf_ccm_event_t event);

/**
 * @brief Function for retrieving the state of a specific CCM event.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 * @param[in] event Event to be checked.
 *
 * @retval true  The event has been generated.
 * @retval false The event has not been generated.
 */
NRF_STATIC_INLINE bool nrf_ccm_event_check(NRF_CCM_Type const *p_reg,
                                           nrf_ccm_event_t event);

/**
 * @brief Function for getting the address of a specific CCM event register.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 * @param[in] event Requested event.
 *
 * @return Address of the specified event register.
 */
NRF_STATIC_INLINE uint32_t nrf_ccm_event_address_get(NRF_CCM_Type const *p_reg,
                                                     nrf_ccm_event_t event);

/**
 * @brief Function for enabling the specified shortcuts.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 * @param[in] mask  Shortcuts to be enabled.
 */
NRF_STATIC_INLINE void nrf_ccm_shorts_enable(NRF_CCM_Type *p_reg,
                                             uint32_t mask);

/**
 * @brief Function for disabling the specified shortcuts.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 * @param[in] mask  Shortcuts to be disabled.
 */
NRF_STATIC_INLINE void nrf_ccm_shorts_disable(NRF_CCM_Type *p_reg,
                                              uint32_t mask);

/**
 * @brief Function for setting the specified shortcuts.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 * @param[in] mask  Shortcuts to be set.
 */
NRF_STATIC_INLINE void nrf_ccm_shorts_set(NRF_CCM_Type *p_reg, uint32_t mask);

/**
 * @brief Function for enabling specified interrupts.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 * @param[in] mask  Interrupts to be enabled.
 */
NRF_STATIC_INLINE void nrf_ccm_int_enable(NRF_CCM_Type *p_reg, uint32_t mask);

/**
 * @brief Function for disabling specified interrupts.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 * @param[in] mask  Interrupts to be disabled.
 */
NRF_STATIC_INLINE void nrf_ccm_int_disable(NRF_CCM_Type *p_reg, uint32_t mask);

/**
 * @brief Function for checking if the specified interrupts are enabled.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 * @param[in] mask  Mask of interrupts to be checked.
 *
 * @return Mask of enabled interrupts.
 */
NRF_STATIC_INLINE uint32_t nrf_ccm_int_enable_check(NRF_CCM_Type const *p_reg,
                                                    uint32_t mask);

/**
 * @brief Function for enabling the CCM peripheral.
 *
 * @param[in] p_reg  Pointer to the structure of registers of the peripheral.
 */
NRF_STATIC_INLINE void nrf_ccm_enable(NRF_CCM_Type *p_reg);

/**
 * @brief Function for disabling the CCM peripheral.
 *
 * @param[in] p_reg  Pointer to the structure of registers of the peripheral.
 */
NRF_STATIC_INLINE void nrf_ccm_disable(NRF_CCM_Type *p_reg);

/**
 * @brief Function for setting the CCM peripheral configuration.
 *
 * @param[in] p_reg    Pointer to the structure of registers of the peripheral.
 * @param[in] p_config Pointer to the structure with configuration to be set.
 */
NRF_STATIC_INLINE void nrf_ccm_configure(NRF_CCM_Type *p_reg,
                                         nrf_ccm_config_t const *p_config);

#if defined(CCM_MAXPACKETSIZE_MAXPACKETSIZE_Pos) || defined(__NRFX_DOXYGEN__)
/**
 * @brief Function for setting the length of key-stream generated
 *        when the packet length is configured as extended.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 * @param[in] size  Maximum length of the key-stream.
 */
NRF_STATIC_INLINE void nrf_ccm_maxpacketsize_set(NRF_CCM_Type *p_reg,
                                                 uint8_t size);
#endif // defined(CCM_MAXPACKETSIZE_MAXPACKETSIZE_Pos) ||
       // defined(__NRFX_DOXYGEN__)

/**
 * @brief Function for getting the MIC check result.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 *
 * @retval true  The MIC check passed.
 * @retval false The MIC check failed.
 */
NRF_STATIC_INLINE bool nrf_ccm_micstatus_get(NRF_CCM_Type const *p_reg);

/**
 * @brief Function for setting the pointer to the data structure
 *        holding the AES key and the CCM NONCE vector.
 *
 * @param[in] p_reg  Pointer to the structure of registers of the peripheral.
 * @param[in] p_data Pointer to the data structure.
 */
NRF_STATIC_INLINE void nrf_ccm_cnfptr_set(NRF_CCM_Type *p_reg,
                                          uint32_t const *p_data);

/**
 * @brief Function for getting the pointer to the data structure
 *        holding the AES key and the CCM NONCE vector.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 *
 * @return Pointer to the data structure.
 */
NRF_STATIC_INLINE uint32_t *nrf_ccm_cnfptr_get(NRF_CCM_Type const *p_reg);

/**
 * @brief Function for setting the input data pointer.
 *
 * @param[in] p_reg  Pointer to the structure of registers of the peripheral.
 * @param[in] p_data Input data pointer.
 */
NRF_STATIC_INLINE void nrf_ccm_inptr_set(NRF_CCM_Type *p_reg,
                                         uint32_t const *p_data);

/**
 * @brief Function for getting the input data pointer.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 *
 * @return Input data pointer.
 */
NRF_STATIC_INLINE uint32_t *nrf_ccm_inptr_get(NRF_CCM_Type const *p_reg);

/**
 * @brief Function for setting the output data pointer.
 *
 * @param[in] p_reg  Pointer to the structure of registers of the peripheral.
 * @param[in] p_data Output data pointer.
 */
NRF_STATIC_INLINE void nrf_ccm_outptr_set(NRF_CCM_Type *p_reg,
                                          uint32_t const *p_data);

/**
 * @brief Function for getting the output data pointer.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 *
 * @return Output data pointer.
 */
NRF_STATIC_INLINE uint32_t *nrf_ccm_outptr_get(NRF_CCM_Type const *p_reg);

/**
 * @brief Function for setting the pointer to the scratch area used for
 *        temporary storage.
 *
 * @param[in] p_reg  Pointer to the structure of registers of the peripheral.
 * @param[in] p_area Pointer to the scratch area.
 */
NRF_STATIC_INLINE void nrf_ccm_scratchptr_set(NRF_CCM_Type *p_reg,
                                              uint32_t const *p_area);

/**
 * @brief Function for getting the pointer to the scratch area.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 *
 * @return Pointer to the scratch area.
 */
NRF_STATIC_INLINE uint32_t *nrf_ccm_stratchptr_get(NRF_CCM_Type const *p_reg);

#if defined(CCM_RATEOVERRIDE_RATEOVERRIDE_Pos) || defined(__NRFX_DOXYGEN__)
/**
 * @brief Function for setting the data rate override value.
 *
 * @param[in] p_reg    Pointer to the structure of registers of the peripheral.
 * @param[in] datarate Override value to be applied when the RATEOVERRIDE task
 *                     is triggered.
 */
NRF_STATIC_INLINE void
nrf_ccm_datarate_override_set(NRF_CCM_Type *p_reg, nrf_ccm_datarate_t datarate);
#endif // defined(CCM_RATEOVERRIDE_RATEOVERRIDE_Pos) ||
       // defined(__NRFX_DOXYGEN__)

#if defined(DPPI_PRESENT) || defined(__NRFX_DOXYGEN__)
/**
 * @brief Function for setting the subscribe configuration for a given
 *        CCM task.
 *
 * @param[in] p_reg   Pointer to the structure of registers of the peripheral.
 * @param[in] task    Task for which to set the configuration.
 * @param[in] channel Channel through which to subscribe events.
 */
NRF_STATIC_INLINE void nrf_ccm_subscribe_set(NRF_CCM_Type *p_reg,
                                             nrf_ccm_task_t task,
                                             uint8_t channel);

/**
 * @brief Function for clearing the subscribe configuration for a given
 *        CCM task.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 * @param[in] task  Task for which to clear the configuration.
 */
NRF_STATIC_INLINE void nrf_ccm_subscribe_clear(NRF_CCM_Type *p_reg,
                                               nrf_ccm_task_t task);

/**
 * @brief Function for setting the publish configuration for a given
 *        CCM event.
 *
 * @param[in] p_reg   Pointer to the structure of registers of the peripheral.
 * @param[in] event   Event for which to set the configuration.
 * @param[in] channel Channel through which to publish the event.
 */
NRF_STATIC_INLINE void nrf_ccm_publish_set(NRF_CCM_Type *p_reg,
                                           nrf_ccm_event_t event,
                                           uint8_t channel);

/**
 * @brief Function for clearing the publish configuration for a given
 *        CCM event.
 *
 * @param[in] p_reg Pointer to the structure of registers of the peripheral.
 * @param[in] event Event for which to clear the configuration.
 */
NRF_STATIC_INLINE void nrf_ccm_publish_clear(NRF_CCM_Type *p_reg,
                                             nrf_ccm_event_t event);
#endif // defined(DPPI_PRESENT) || defined(__NRFX_DOXYGEN__)

#ifndef NRF_DECLARE_ONLY

NRF_STATIC_INLINE void nrf_ccm_task_trigger(NRF_CCM_Type *p_reg,
                                            nrf_ccm_task_t task) {
  *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)task)) = 0x1UL;
}

NRF_STATIC_INLINE uint32_t nrf_ccm_task_address_get(NRF_CCM_Type const *p_reg,
                                                    nrf_ccm_task_t task) {
  return ((uint32_t)p_reg + (uint32_t)task);
}

NRF_STATIC_INLINE void nrf_ccm_event_clear(NRF_CCM_Type *p_reg,
                                           nrf_ccm_event_t event) {
  *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)event)) = 0x0UL;
  nrf_event_readback((uint8_t *)p_reg + (uint32_t)event);
}

NRF_STATIC_INLINE bool nrf_ccm_event_check(NRF_CCM_Type const *p_reg,
                                           nrf_ccm_event_t event) {
  return (bool)*(volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)event);
}

NRF_STATIC_INLINE uint32_t nrf_ccm_event_address_get(NRF_CCM_Type const *p_reg,
                                                     nrf_ccm_event_t event) {
  return ((uint32_t)p_reg + (uint32_t)event);
}

NRF_STATIC_INLINE void nrf_ccm_shorts_enable(NRF_CCM_Type *p_reg,
                                             uint32_t mask) {
  p_reg->SHORTS |= mask;
}

NRF_STATIC_INLINE void nrf_ccm_shorts_disable(NRF_CCM_Type *p_reg,
                                              uint32_t mask) {
  p_reg->SHORTS &= ~(mask);
}

NRF_STATIC_INLINE void nrf_ccm_shorts_set(NRF_CCM_Type *p_reg, uint32_t mask) {
  p_reg->SHORTS = mask;
}

NRF_STATIC_INLINE void nrf_ccm_int_enable(NRF_CCM_Type *p_reg, uint32_t mask) {
  p_reg->INTENSET = mask;
}

NRF_STATIC_INLINE void nrf_ccm_int_disable(NRF_CCM_Type *p_reg, uint32_t mask) {
  p_reg->INTENCLR = mask;
}

NRF_STATIC_INLINE uint32_t nrf_ccm_int_enable_check(NRF_CCM_Type const *p_reg,
                                                    uint32_t mask) {
  return p_reg->INTENSET & mask;
}

NRF_STATIC_INLINE void nrf_ccm_enable(NRF_CCM_Type *p_reg) {
  p_reg->ENABLE = (CCM_ENABLE_ENABLE_Enabled << CCM_ENABLE_ENABLE_Pos);
}

NRF_STATIC_INLINE void nrf_ccm_disable(NRF_CCM_Type *p_reg) {
  p_reg->ENABLE = (CCM_ENABLE_ENABLE_Disabled << CCM_ENABLE_ENABLE_Pos);
}

NRF_STATIC_INLINE void nrf_ccm_configure(NRF_CCM_Type *p_reg,
                                         nrf_ccm_config_t const *p_config) {
  p_reg->MODE = (((uint32_t)p_config->mode << CCM_MODE_MODE_Pos) |
#if defined(CCM_MODE_DATARATE_Pos)
                 ((uint32_t)p_config->datarate << CCM_MODE_DATARATE_Pos) |
#endif
#if defined(CCM_MODE_LENGTH_Pos)
                 ((uint32_t)p_config->length << CCM_MODE_LENGTH_Pos) |
#endif
                 0);
}

#if defined(CCM_MAXPACKETSIZE_MAXPACKETSIZE_Pos)
NRF_STATIC_INLINE void nrf_ccm_maxpacketsize_set(NRF_CCM_Type *p_reg,
                                                 uint8_t size) {
  NRFX_ASSERT((size >= 0x1B) && (size <= 0xFB));

  p_reg->MAXPACKETSIZE = size;
}
#endif // defined(CCM_MAXPACKETSIZE_MAXPACKETSIZE_Pos)

NRF_STATIC_INLINE bool nrf_ccm_micstatus_get(NRF_CCM_Type const *p_reg) {
  return (bool)(p_reg->MICSTATUS);
}

NRF_STATIC_INLINE void nrf_ccm_cnfptr_set(NRF_CCM_Type *p_reg,
                                          uint32_t const *p_data) {
  p_reg->CNFPTR = (uint32_t)p_data;
}

NRF_STATIC_INLINE uint32_t *nrf_ccm_cnfptr_get(NRF_CCM_Type const *p_reg) {
#if defined(NRF5340_XXAA_NETWORK)
  // Apply workaround for anomaly 10.
  return (uint32_t *)(p_reg->CNFPTR | 0x01000000);
#else
  return (uint32_t *)(p_reg->CNFPTR);
#endif
}

NRF_STATIC_INLINE void nrf_ccm_inptr_set(NRF_CCM_Type *p_reg,
                                         uint32_t const *p_data) {
  p_reg->INPTR = (uint32_t)p_data;
}

NRF_STATIC_INLINE uint32_t *nrf_ccm_inptr_get(NRF_CCM_Type const *p_reg) {
#if defined(NRF5340_XXAA_NETWORK)
  // Apply workaround for anomaly 10.
  return (uint32_t *)(p_reg->INPTR | 0x01000000);
#else
  return (uint32_t *)(p_reg->INPTR);
#endif
}

NRF_STATIC_INLINE void nrf_ccm_outptr_set(NRF_CCM_Type *p_reg,
                                          uint32_t const *p_data) {
  p_reg->OUTPTR = (uint32_t)p_data;
}

NRF_STATIC_INLINE uint32_t *nrf_ccm_outptr_get(NRF_CCM_Type const *p_reg) {
#if defined(NRF5340_XXAA_NETWORK)
  // Apply workaround for anomaly 10.
  return (uint32_t *)(p_reg->OUTPTR | 0x01000000);
#else
  return (uint32_t *)(p_reg->OUTPTR);
#endif
}

NRF_STATIC_INLINE void nrf_ccm_scratchptr_set(NRF_CCM_Type *p_reg,
                                              uint32_t const *p_area) {
  p_reg->SCRATCHPTR = (uint32_t)p_area;
}

NRF_STATIC_INLINE uint32_t *nrf_ccm_stratchptr_get(NRF_CCM_Type const *p_reg) {
#if defined(NRF5340_XXAA_NETWORK)
  // Apply workaround for anomaly 10.
  return (uint32_t *)(p_reg->SCRATCHPTR | 0x01000000);
#else
  return (uint32_t *)(p_reg->SCRATCHPTR);
#endif
}

#if defined(CCM_RATEOVERRIDE_RATEOVERRIDE_Pos)
NRF_STATIC_INLINE void
nrf_ccm_datarate_override_set(NRF_CCM_Type *p_reg,
                              nrf_ccm_datarate_t datarate) {
  p_reg->RATEOVERRIDE =
      ((uint32_t)datarate << CCM_RATEOVERRIDE_RATEOVERRIDE_Pos);
}
#endif

#if defined(DPPI_PRESENT)
NRF_STATIC_INLINE void nrf_ccm_subscribe_set(NRF_CCM_Type *p_reg,
                                             nrf_ccm_task_t task,
                                             uint8_t channel) {
  *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)task + 0x80uL)) =
      ((uint32_t)channel | CCM_SUBSCRIBE_KSGEN_EN_Msk);
}

NRF_STATIC_INLINE void nrf_ccm_subscribe_clear(NRF_CCM_Type *p_reg,
                                               nrf_ccm_task_t task) {
  *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)task + 0x80uL)) = 0;
}

NRF_STATIC_INLINE void nrf_ccm_publish_set(NRF_CCM_Type *p_reg,
                                           nrf_ccm_event_t event,
                                           uint8_t channel) {
  *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)event + 0x80uL)) =
      ((uint32_t)channel | CCM_PUBLISH_ENDKSGEN_EN_Msk);
}

NRF_STATIC_INLINE void nrf_ccm_publish_clear(NRF_CCM_Type *p_reg,
                                             nrf_ccm_event_t event) {
  *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)event + 0x80uL)) = 0;
}
#endif // defined(DPPI_PRESENT)

#endif // NRF_DECLARE_ONLY

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NRF_CCM_H__
