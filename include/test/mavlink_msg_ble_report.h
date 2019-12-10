#pragma once
// MESSAGE ble_report PACKING

#define MAVLINK_MSG_ID_ble_report 2

MAVPACKED(
typedef struct __mavlink_ble_report_t {
 uint8_t addr[6]; /*<  mac address of drone*/
 uint8_t pos_mode; /*<   positioning mode*/
 uint8_t conn_size; /*<   # of connected nodes */
 uint8_t ready_size; /*<   # of in range nodes */
}) mavlink_ble_report_t;

#define MAVLINK_MSG_ID_ble_report_LEN 9
#define MAVLINK_MSG_ID_ble_report_MIN_LEN 9
#define MAVLINK_MSG_ID_2_LEN 9
#define MAVLINK_MSG_ID_2_MIN_LEN 9

#define MAVLINK_MSG_ID_ble_report_CRC 37
#define MAVLINK_MSG_ID_2_CRC 37

#define MAVLINK_MSG_ble_report_FIELD_ADDR_LEN 6

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ble_report { \
    2, \
    "ble_report", \
    4, \
    {  { "addr", NULL, MAVLINK_TYPE_UINT8_T, 6, 0, offsetof(mavlink_ble_report_t, addr) }, \
         { "pos_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_ble_report_t, pos_mode) }, \
         { "conn_size", NULL, MAVLINK_TYPE_UINT8_T, 0, 7, offsetof(mavlink_ble_report_t, conn_size) }, \
         { "ready_size", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_ble_report_t, ready_size) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ble_report { \
    "ble_report", \
    4, \
    {  { "addr", NULL, MAVLINK_TYPE_UINT8_T, 6, 0, offsetof(mavlink_ble_report_t, addr) }, \
         { "pos_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_ble_report_t, pos_mode) }, \
         { "conn_size", NULL, MAVLINK_TYPE_UINT8_T, 0, 7, offsetof(mavlink_ble_report_t, conn_size) }, \
         { "ready_size", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_ble_report_t, ready_size) }, \
         } \
}
#endif

/**
 * @brief Pack a ble_report message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param addr  mac address of drone
 * @param pos_mode   positioning mode
 * @param conn_size   # of connected nodes 
 * @param ready_size   # of in range nodes 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_ble_report_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const uint8_t *addr, uint8_t pos_mode, uint8_t conn_size, uint8_t ready_size)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ble_report_LEN];
    _mav_put_uint8_t(buf, 6, pos_mode);
    _mav_put_uint8_t(buf, 7, conn_size);
    _mav_put_uint8_t(buf, 8, ready_size);
    _mav_put_uint8_t_array(buf, 0, addr, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ble_report_LEN);
#else
    mavlink_ble_report_t packet;
    packet.pos_mode = pos_mode;
    packet.conn_size = conn_size;
    packet.ready_size = ready_size;
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ble_report_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ble_report;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ble_report_MIN_LEN, MAVLINK_MSG_ID_ble_report_LEN, MAVLINK_MSG_ID_ble_report_CRC);
}

/**
 * @brief Pack a ble_report message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param addr  mac address of drone
 * @param pos_mode   positioning mode
 * @param conn_size   # of connected nodes 
 * @param ready_size   # of in range nodes 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_ble_report_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const uint8_t *addr,uint8_t pos_mode,uint8_t conn_size,uint8_t ready_size)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ble_report_LEN];
    _mav_put_uint8_t(buf, 6, pos_mode);
    _mav_put_uint8_t(buf, 7, conn_size);
    _mav_put_uint8_t(buf, 8, ready_size);
    _mav_put_uint8_t_array(buf, 0, addr, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ble_report_LEN);
#else
    mavlink_ble_report_t packet;
    packet.pos_mode = pos_mode;
    packet.conn_size = conn_size;
    packet.ready_size = ready_size;
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ble_report_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ble_report;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ble_report_MIN_LEN, MAVLINK_MSG_ID_ble_report_LEN, MAVLINK_MSG_ID_ble_report_CRC);
}

/**
 * @brief Encode a ble_report struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param ble_report C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_ble_report_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_ble_report_t* ble_report)
{
    return mavlink_msg_ble_report_pack(system_id, component_id, msg, ble_report->addr, ble_report->pos_mode, ble_report->conn_size, ble_report->ready_size);
}

/**
 * @brief Encode a ble_report struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param ble_report C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_ble_report_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_ble_report_t* ble_report)
{
    return mavlink_msg_ble_report_pack_chan(system_id, component_id, chan, msg, ble_report->addr, ble_report->pos_mode, ble_report->conn_size, ble_report->ready_size);
}

/**
 * @brief Send a ble_report message
 * @param chan MAVLink channel to send the message
 *
 * @param addr  mac address of drone
 * @param pos_mode   positioning mode
 * @param conn_size   # of connected nodes 
 * @param ready_size   # of in range nodes 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_ble_report_send(mavlink_channel_t chan, const uint8_t *addr, uint8_t pos_mode, uint8_t conn_size, uint8_t ready_size)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ble_report_LEN];
    _mav_put_uint8_t(buf, 6, pos_mode);
    _mav_put_uint8_t(buf, 7, conn_size);
    _mav_put_uint8_t(buf, 8, ready_size);
    _mav_put_uint8_t_array(buf, 0, addr, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ble_report, buf, MAVLINK_MSG_ID_ble_report_MIN_LEN, MAVLINK_MSG_ID_ble_report_LEN, MAVLINK_MSG_ID_ble_report_CRC);
#else
    mavlink_ble_report_t packet;
    packet.pos_mode = pos_mode;
    packet.conn_size = conn_size;
    packet.ready_size = ready_size;
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ble_report, (const char *)&packet, MAVLINK_MSG_ID_ble_report_MIN_LEN, MAVLINK_MSG_ID_ble_report_LEN, MAVLINK_MSG_ID_ble_report_CRC);
#endif
}

/**
 * @brief Send a ble_report message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_ble_report_send_struct(mavlink_channel_t chan, const mavlink_ble_report_t* ble_report)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_ble_report_send(chan, ble_report->addr, ble_report->pos_mode, ble_report->conn_size, ble_report->ready_size);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ble_report, (const char *)ble_report, MAVLINK_MSG_ID_ble_report_MIN_LEN, MAVLINK_MSG_ID_ble_report_LEN, MAVLINK_MSG_ID_ble_report_CRC);
#endif
}

#if MAVLINK_MSG_ID_ble_report_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_ble_report_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const uint8_t *addr, uint8_t pos_mode, uint8_t conn_size, uint8_t ready_size)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 6, pos_mode);
    _mav_put_uint8_t(buf, 7, conn_size);
    _mav_put_uint8_t(buf, 8, ready_size);
    _mav_put_uint8_t_array(buf, 0, addr, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ble_report, buf, MAVLINK_MSG_ID_ble_report_MIN_LEN, MAVLINK_MSG_ID_ble_report_LEN, MAVLINK_MSG_ID_ble_report_CRC);
#else
    mavlink_ble_report_t *packet = (mavlink_ble_report_t *)msgbuf;
    packet->pos_mode = pos_mode;
    packet->conn_size = conn_size;
    packet->ready_size = ready_size;
    mav_array_memcpy(packet->addr, addr, sizeof(uint8_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ble_report, (const char *)packet, MAVLINK_MSG_ID_ble_report_MIN_LEN, MAVLINK_MSG_ID_ble_report_LEN, MAVLINK_MSG_ID_ble_report_CRC);
#endif
}
#endif

#endif

// MESSAGE ble_report UNPACKING


/**
 * @brief Get field addr from ble_report message
 *
 * @return  mac address of drone
 */
static inline uint16_t mavlink_msg_ble_report_get_addr(const mavlink_message_t* msg, uint8_t *addr)
{
    return _MAV_RETURN_uint8_t_array(msg, addr, 6,  0);
}

/**
 * @brief Get field pos_mode from ble_report message
 *
 * @return   positioning mode
 */
static inline uint8_t mavlink_msg_ble_report_get_pos_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  6);
}

/**
 * @brief Get field conn_size from ble_report message
 *
 * @return   # of connected nodes 
 */
static inline uint8_t mavlink_msg_ble_report_get_conn_size(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  7);
}

/**
 * @brief Get field ready_size from ble_report message
 *
 * @return   # of in range nodes 
 */
static inline uint8_t mavlink_msg_ble_report_get_ready_size(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Decode a ble_report message into a struct
 *
 * @param msg The message to decode
 * @param ble_report C-struct to decode the message contents into
 */
static inline void mavlink_msg_ble_report_decode(const mavlink_message_t* msg, mavlink_ble_report_t* ble_report)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_ble_report_get_addr(msg, ble_report->addr);
    ble_report->pos_mode = mavlink_msg_ble_report_get_pos_mode(msg);
    ble_report->conn_size = mavlink_msg_ble_report_get_conn_size(msg);
    ble_report->ready_size = mavlink_msg_ble_report_get_ready_size(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ble_report_LEN? msg->len : MAVLINK_MSG_ID_ble_report_LEN;
        memset(ble_report, 0, MAVLINK_MSG_ID_ble_report_LEN);
    memcpy(ble_report, _MAV_PAYLOAD(msg), len);
#endif
}
