/*
 * Arm SCP/MCP Software
 * Copyright (c) 2015-2020, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MOD_SENSOR_H
#define MOD_SENSOR_H

#include <fwk_id.h>
#include <fwk_module_idx.h>

#include <stdbool.h>
#include <stdint.h>

/*!
 * \addtogroup GroupModules Modules
 * \{
 */

/*!
 * \defgroup GroupModuleSensor Sensor
 *
 * \brief Module for reading hardware sensors.
 *
 * \details Module for interfacing with and reading various hardware sensors.
 *
 * \{
 */

/*!
 * \brief Sensor types as defined by SCMI.
 */
enum mod_sensor_type {
    MOD_SENSOR_TYPE_NONE = 0,
    MOD_SENSOR_TYPE_UNSPECIFIED,
    MOD_SENSOR_TYPE_DEGREES_C,
    MOD_SENSOR_TYPE_DEGREES_F,
    MOD_SENSOR_TYPE_DEGREES_K,
    MOD_SENSOR_TYPE_VOLTS,
    MOD_SENSOR_TYPE_AMPS,
    MOD_SENSOR_TYPE_WATTS,
    MOD_SENSOR_TYPE_JOULES,
    MOD_SENSOR_TYPE_COULOMBS,
    MOD_SENSOR_TYPE_VA,
    MOD_SENSOR_TYPE_NITS,
    MOD_SENSOR_TYPE_LUMENS,
    MOD_SENSOR_TYPE_LUX,
    MOD_SENSOR_TYPE_CANDELAS,
    MOD_SENSOR_TYPE_KPA,
    MOD_SENSOR_TYPE_PSI,
    MOD_SENSOR_TYPE_NEWTONS,
    MOD_SENSOR_TYPE_CFM,
    MOD_SENSOR_TYPE_RPM,
    MOD_SENSOR_TYPE_HERTZ,
    MOD_SENSOR_TYPE_SECONDS,
    MOD_SENSOR_TYPE_MINUTES,
    MOD_SENSOR_TYPE_HOURS,
    MOD_SENSOR_TYPE_DAYS,
    MOD_SENSOR_TYPE_WEEKS,
    MOD_SENSOR_TYPE_MILS,
    MOD_SENSOR_TYPE_INCHES,
    MOD_SENSOR_TYPE_FEET,
    MOD_SENSOR_TYPE_CUBIC_INCHES,
    MOD_SENSOR_TYPE_CUBIC_FEET,
    MOD_SENSOR_TYPE_METERS,
    MOD_SENSOR_TYPE_CUBIC_CENTIMETERS,
    MOD_SENSOR_TYPE_CUBIC_METERS,
    MOD_SENSOR_TYPE_LITRES,
    MOD_SENSOR_TYPE_FLUID_OUNCES,
    MOD_SENSOR_TYPE_RADIANS,
    MOD_SENSOR_TYPE_STERADIANS,
    MOD_SENSOR_TYPE_REVOLUTIONS,
    MOD_SENSOR_TYPE_CYCLES,
    MOD_SENSOR_TYPE_GRAVITIES,
    MOD_SENSOR_TYPE_OUNCES,
    MOD_SENSOR_TYPE_POUNDS,
    MOD_SENSOR_TYPE_FOOT_POUNDS,
    MOD_SENSOR_TYPE_OUNCE_INCHES,
    MOD_SENSOR_TYPE_GAUSS,
    MOD_SENSOR_TYPE_GILBERTS,
    MOD_SENSOR_TYPE_HENRIES,
    MOD_SENSOR_TYPE_FARADS,
    MOD_SENSOR_TYPE_OHMS,
    MOD_SENSOR_TYPE_SIEMENS,
    MOD_SENSOR_TYPE_MOLES,
    MOD_SENSOR_TYPE_BECQUERELS,
    MOD_SENSOR_TYPE_PPM,
    MOD_SENSOR_TYPE_DECIBELS,
    MOD_SENSOR_TYPE_DBA,
    MOD_SENSOR_TYPE_DBC,
    MOD_SENSOR_TYPE_GRAYS,
    MOD_SENSOR_TYPE_SIEVERTS,
    MOD_SENSOR_TYPE_COLOR_TEMP_DEGREES_K,
    MOD_SENSOR_TYPE_BITS,
    MOD_SENSOR_TYPE_BYTES,
    MOD_SENSOR_TYPE_WORDS,
    MOD_SENSOR_TYPE_DWORDS,
    MOD_SENSOR_TYPE_QWORDS,
    MOD_SENSOR_TYPE_PERCENTAGE,
    MOD_SENSOR_TYPE_PASCALS,
    MOD_SENSOR_TYPE_COUNTS,
    MOD_SENSOR_TYPE_GRAMS,
    MOD_SENSOR_TYPE_NEWTON_METERS,
    MOD_SENSOR_TYPE_HITS,
    MOD_SENSOR_TYPE_MISSES,
    MOD_SENSOR_TYPE_RETRIES,
    MOD_SENSOR_TYPE_OVERRUNS,
    MOD_SENSOR_TYPE_UNDERRUNS,
    MOD_SENSOR_TYPE_COLLISIONS,
    MOD_SENSOR_TYPE_PACKETS,
    MOD_SENSOR_TYPE_MESSAGES,
    MOD_SENSOR_TYPE_CHARACTERS,
    MOD_SENSOR_TYPE_ERRORS,
    MOD_SENSOR_TYPE_CORRECTED_ERRORS,
    MOD_SENSOR_TYPE_UNCORRECTABLE_ERRORS,
    MOD_SENSOR_TYPE_SQUARE_MILS,
    MOD_SENSOR_TYPE_SQUARE_INCHES,
    MOD_SENSOR_TYPE_SQUARE_FEET,
    MOD_SENSOR_TYPE_SQUARE_CENTIMETERS,
    MOD_SENSOR_TYPE_SQUARE_METERS,
    MOD_SENSOR_TYPE_OEM_UNIT = 0xFF,
    MOD_SENSOR_TYPE_COUNT
};

/*!
 * \brief Structure containing all sensor trip point information.
 */
struct mod_sensor_trip_point_info {
    /*! Sensor trip point count */
    uint32_t count;
};

/*!
 * \brief Structure containing all sensor driver information.
 *
 * \details Sensor information structure used to configure the sensor HAL.
 */
struct mod_sensor_info {
    /*! SCMI sensor type */
    enum mod_sensor_type type;

    /*!
     * \brief Time (in seconds) between sensor updates.
     *
     * \details Set this field to 0 to indicate that the sensor does not have a
     *      minimum update interval. This field is used with
     *      ::mod_sensor_info::update_interval_multiplier to calculate the
     *      actual update interval.
     */
    unsigned int update_interval;

    /*!
     * \brief Power-of-10 multiplier for ::mod_sensor_info::update_interval.
     *
     * \details This is used to calculate the actual interval time:
     *
     *      ```none
     *      actual = update_interval * 10^(update_interval_multiplier)
     *      ```
     */
    int update_interval_multiplier;

    /*!
     * \brief Power-of-10 multiplier applied to the unit specified by
     *      ::mod_sensor_info::type.
     *
     * \details Used per:
     *
     *      ```none
     *      unit * 10^(unit_multiplier)
     *      ```
     */
    int unit_multiplier;
};

/*!
 * \brief Structure containing all sensor information for SCMI requests.
 *
 * \details Sensor information structure used serve SCMI requests.
 */
struct mod_sensor_scmi_info {
    /*! Sensor HAL information */
    struct mod_sensor_info hal_info;

    /*! Sensor trip information */
    struct mod_sensor_trip_point_info trip_point;
};

/*!
 * \brief Sensor trip point detection mode
 */
enum mod_sensor_trip_point_mode {
    MOD_SENSOR_TRIP_POINT_MODE_DISABLED = 0,
    MOD_SENSOR_TRIP_POINT_MODE_POSITIVE,
    MOD_SENSOR_TRIP_POINT_MODE_NEGATIVE,
    MOD_SENSOR_TRIP_POINT_MODE_TRANSITION
};

/*!
 * \brief Structure containing trip point parameters.
 *
 * \details Sensor trip point information structure used to configure
 *     a trip point value.
 */
struct mod_sensor_trip_point_params {
    /*! Sensor trip point low valuer */
    uint32_t low_value;

    /*! Sensor trip point high value */
    uint32_t high_value;

    /*! Sensor trip point mode */
    enum mod_sensor_trip_point_mode mode;
};

/*!
 * \brief Sensor device configuration.
 *
 * \details Configuration structure for individual sensors.
 */
struct mod_sensor_dev_config {
    /*! Module or element identifier of the driver */
    fwk_id_t driver_id;

    /*! API identifier of the driver */
    fwk_id_t driver_api_id;

    /*!  Notifications identifier */
    fwk_id_t notification_id;

    /*! Trip point API identifier */
    fwk_id_t trip_point_api_id;

    /*! Sensor trip information */
    struct mod_sensor_trip_point_info trip_point;
};

/*!
 * \brief Sensor module configuration.
 *
 * \details Configuration structure sensor module.
 */
struct mod_sensor_config {
    /*!  Notifications identifier */
    fwk_id_t notification_id;

    /*! Trip point API identifier */
    fwk_id_t trip_point_api_id;
};

/*!
 * \brief Sensor driver API.
 *
 * \details Api used by this module to interface with the driver.
 */
struct mod_sensor_driver_api {
    /*!
     * \brief Get sensor value.
     *
     * \param id Specific sensor device id.
     * \param[out] value Sensor value.
     *
     * \retval ::FWK_PENDING The request is pending. The driver will provide the
     *      requested value later through the driver response API.
     * \retval ::FWK_SUCCESS Value was read successfully.
     * \return One of the standard framework error codes.
     */
    int (*get_value)(fwk_id_t id, uint64_t *value);

    /*!
     * \brief Get sensor information.
     *
     * \param id Specific sensor device id.
     * \param[out] info The sensor information.
     *
     * \retval ::FWK_SUCCESS The information was read successfully.
     * \return One of the standard framework error codes.
     */
    int (*get_info)(fwk_id_t id, struct mod_sensor_info *info);
};

/*!
 * \brief Sensor API.
 */
struct mod_sensor_api {
    /*!
     * \brief Read sensor value.
     *
     * \details Read current sensor value.
     *
     * \param id Specific sensor device id.
     * \param[out] value The sensor value.
     *
     * \retval ::FWK_SUCCESS Operation succeeded.
     * \retval ::FWK_E_DEVICE Driver error.
     * \retval ::FWK_E_BUSY At least one reading of the sensor value is already
     *      on-going.
     * \retval ::FWK_PENDING The request is pending. The requested value will be
     *      provided via a response event.
     * \return One of the standard framework error codes.
     */
    int (*get_value)(fwk_id_t id, uint64_t *value);

    /*!
     * \brief Get sensor information.
     *
     * \details Get a pointer to the sensor_info structure of a specific sensor.
     *
     * \param id Specific sensor device id.
     * \param[out] info The information structure.
     *
     * \retval ::FWK_SUCCESS Operation succeeded.
     * \retval ::FWK_E_DEVICE Driver error.
     * \return One of the standard framework error codes.
     */
    int (*get_info)(fwk_id_t id, struct mod_sensor_scmi_info *info);

    /*!
     * \brief Set trip point.
     *
     * \details Set trip point sensor configuration.
     *
     * \param id Specific sensor device id.
     * \param trip_point_idx Specific trip point index.
     * \param params Pointer to trip points parameters structure.
     *
     * \retval FWK_SUCCESS Operation succeeded.
     * \return One of the standard framework error codes.
     */
    int (*set_trip_point)(
        fwk_id_t id,
        uint32_t trip_point_idx,
        struct mod_sensor_trip_point_params *params);

    /*!
     * \brief Get trip point.
     *
     * \details Get trip point sensor configuration.
     *
     * \param id Specific sensor device id.
     * \param trip_point_idx Specific trip point index.
     * \param[out] params Pointer to trip points parameters structure.
     *
     * \retval FWK_SUCCESS Operation succeeded.
     * \return One of the standard framework error codes.
     */
    int (*get_trip_point)(
        fwk_id_t id,
        uint32_t trip_point_idx,
        struct mod_sensor_trip_point_params *params);
};

/*!
 * \brief Driver response parameters.
 */
struct mod_sensor_driver_resp_params {
    /*! Status of the requested operation */
    int status;

    /*! Value requested */
    uint64_t value;
};

/*!
 * \brief Driver response API.
 *
 * \details API used by the driver to notify the HAL when a pending request
 *      has completed.
 */
struct mod_sensor_driver_response_api {
    /*!
     * \brief Inform the completion of a sensor reading.
     *
     * \param id Specific sensor device identifier.
     * \param[out] response The response data structure.
     */
    void (*reading_complete)(fwk_id_t id,
                             struct mod_sensor_driver_resp_params *response);
};

/*!
 * \brief API indices.
 */
enum mod_sensor_api_idx {
    /*!
     * \brief Driver API index.
     *
     * \note This API implements the ::mod_sensor_api interface.
     */
    MOD_SENSOR_API_IDX_SENSOR,

    /*!
     * \brief Driver response API.
     */
    MOD_SENSOR_API_IDX_DRIVER_RESPONSE,

    /*!
     * \brief Number of defined APIs.
     */
    MOD_SENSOR_API_IDX_COUNT,
};

/*!
 * \brief Module API identifier.
 */
static const fwk_id_t mod_sensor_api_id_sensor =
    FWK_ID_API_INIT(FWK_MODULE_IDX_SENSOR, MOD_SENSOR_API_IDX_SENSOR);

/*!
 * \brief Driver input API identifier.
 */
static const fwk_id_t mod_sensor_api_id_driver_response =
    FWK_ID_API_INIT(FWK_MODULE_IDX_SENSOR, MOD_SENSOR_API_IDX_DRIVER_RESPONSE);

/*!
 * \brief Shared event parameters.
 */
struct mod_sensor_event_params {
    /*! Sensor value */
    uint64_t value;

    /*! Status of the response event */
    int status;
};

/*!
 * Sensor module read request event index
 */
#define MOD_SENSOR_EVENT_IDX_READ_REQUEST    0

/*!
 * \brief Read request event identifier.
 *
 * \details Clients which expect to receive a response event from this module
 *      should use this identifier to properly identify the response.
 */
static const fwk_id_t mod_sensor_event_id_read_request =
    FWK_ID_EVENT_INIT(FWK_MODULE_IDX_SENSOR, MOD_SENSOR_EVENT_IDX_READ_REQUEST);

/*!
 * \}
 */

/*!
 * \}
 */

#endif /* MOD_SENSOR_H */
