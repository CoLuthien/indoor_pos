#pragma once
// MESSAGE heartbeat PACKING

#define MAVLINK_MSG_ID_heartbeat 0

MAVPACKED(
typedef struct __mavlink_heartbeat_t {
 uint8_t msg_type; /*<  message type*/
 uint8_t addr[6]; /*<  mac address of drone*/
 uint8_t sys_stat; /*<   status of system*/
 uint8_t err_code; /*<   error code, in case of server error*/
}) mavlink_heartbeat_t;

#define MAVLINK_MSG_ID_heartbeat_LEN 9
#define MAVLINK_MSG_ID_heartbeat_MIN_LEN 9
#define MAVLINK_MSG_ID_0_LEN 9
#define MAVLINK_MSG_ID_0_MIN_LEN 9

#define MAVLINK_MSG_ID_heartbeat_CRC 224
#define MAVLINK_MSG_ID_0_CRC 224

#define MAVLINK_MSG_heartbeat_FIELD_ADDR_LEN 6

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_heartbeat { \
    0, \
    "heartbeat", \
    4, \
    {  { "msg_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_heartbeat_t, msg_type) }, \
         { "addr", NULL, MAVLINK_TYPE_UINT8_T, 6, 1, offsetof(mavlink_heartbeat_t, addr) }, \
         { "sys_stat", NULL, MAVLINK_TYPE_UINT8_T, 0, 7, offsetof(mavlink_heartbeat_t, sys_stat) }, \
         { "err_code", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_heartbeat_t, err_code) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_heartbeat { \
    "heartbeat", \
    4, \
    {  { "msg_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_heartbeat_t, msg_type) }, \
         { "addr", NULL, MAVLINK_TYPE_UINT8_T, 6, 1, offsetof(mavlink_heartbeat_t, addr) }, \
         { "sys_stat", NULL, MAVLINK_TYPE_UINT8_T, 0, 7, offsetof(mavlink_heartbeat_t, sys_stat) }, \
         { "err_code", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_heartbeat_t, err_code) }, \
         } \
}
#endif

/**
 * @brief Pack a heartbeat message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param msg_type  message type
 * @param addr  mac address of drone
 * @param sys_stat   status of system
 * @param err_code   error code, in case of server error
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_heartbeat_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t msg_type, const uint8_t *addr, uint8_t sys_stat, uint8_t err_code)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_heartbeat_LEN];
    _mav_put_uint8_t(buf, 0, msg_type);
    _mav_put_uint8_t(buf, 7, sys_stat);
    _mav_put_uint8_t(buf, 8, err_code);
    _mav_put_uint8_t_array(buf, 1, addr, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_heartbeat_LEN);
#else
    mavlink_heartbeat_t packet;
    packet.msg_type = msg_type;
    packet.sys_stat = sys_stat;
    packet.err_code = err_code;
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_heartbeat_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_heartbeat;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_heartbeat_MIN_LEN, MAVLINK_MSG_ID_heartbeat_LEN, MAVLINK_MSG_ID_heartbeat_CRC);
}

/**
 * @brief Pack a heartbeat message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param msg_type  message type
 * @param addr  mac address of drone
 * @param sys_stat   status of system
 * @param err_code   error code, in case of server error
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_heartbeat_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t msg_type,const uint8_t *addr,uint8_t sys_stat,uint8_t err_code)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_heartbeat_LEN];
    _mav_put_uint8_t(buf, 0, msg_type);
    _mav_put_uint8_t(buf, 7, sys_stat);
    _mav_put_uint8_t(buf, 8, err_code);
    _mav_put_uint8_t_array(buf, 1, addr, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_heartbeat_LEN);
#else
    mavlink_heartbeat_t packet;
    packet.msg_type = msg_type;
    packet.sys_stat = sys_stat;
    packet.err_code = err_code;
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_heartbeat_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_heartbeat;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_heartbeat_MIN_LEN, MAVLINK_MSG_ID_heartbeat_LEN, MAVLINK_MSG_ID_heartbeat_CRC);
}

/**
 * @brief Encode a heartbeat struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param heartbeat C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_heartbeat_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_heartbeat_t* heartbeat)
{
    return mavlink_msg_heartbeat_pack(system_id, component_id, msg, heartbeat->msg_type, heartbeat->addr, heartbeat->sys_stat, heartbeat->err_code);
}

/**
 * @brief Encode a heartbeat struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param heartbeat C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_heartbeat_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_heartbeat_t* heartbeat)
{
    return mavlink_msg_heartbeat_pack_chan(system_id, component_id, chan, msg, heartbeat->msg_type, heartbeat->addr, heartbeat->sys_stat, heartbeat->err_code);
}

/**
 * @brief Send a heartbeat message
 * @param chan MAVLink channel to send the message
 *
 * @param msg_type  message type
 * @param addr  mac address of drone
 * @param sys_stat   status of system
 * @param err_code   error code, in case of server error
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_heartbeat_send(mavlink_channel_t chan, uint8_t msg_type, const uint8_t *addr, uint8_t sys_stat, uint8_t err_code)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_heartbeat_LEN];
    _mav_put_uint8_t(buf, 0, msg_type);
    _mav_put_uint8_t(buf, 7, sys_stat);
    _mav_put_uint8_t(buf, 8, err_code);
    _mav_put_uint8_t_array(buf, 1, addr, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_heartbeat, buf, MAVLINK_MSG_ID_heartbeat_MIN_LEN, MAVLINK_MSG_ID_heartbeat_LEN, MAVLINK_MSG_ID_heartbeat_CRC);
#else
    mavlink_heartbeat_t packet;
    packet.msg_type = msg_type;
    packet.sys_stat = sys_stat;
    packet.err_code = err_code;
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_heartbeat, (const char *)&packet, MAVLINK_MSG_ID_heartbeat_MIN_LEN, MAVLINK_MSG_ID_heartbeat_LEN, MAVLINK_MSG_ID_heartbeat_CRC);
#endif
}

/**
 * @brief Send a heartbeat message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_heartbeat_send_struct(mavlink_channel_t chan, const mavlink_heartbeat_t* heartbeat)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_heartbeat_send(chan, heartbeat->msg_type, heartbeat->addr, heartbeat->sys_stat, heartbeat->err_code);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_heartbeat, (const char *)heartbeat, MAVLINK_MSG_ID_heartbeat_MIN_LEN, MAVLINK_MSG_ID_heartbeat_LEN, MAVLINK_MSG_ID_heartbeat_CRC);
#endif
}

#if MAVLINK_MSG_ID_heartbeat_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_heartbeat_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t msg_type, const uint8_t *addr, uint8_t sys_stat, uint8_t err_code)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, msg_type);
    _mav_put_uint8_t(buf, 7, sys_stat);
    _mav_put_uint8_t(buf, 8, err_code);
    _mav_put_uint8_t_array(buf, 1, addr, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_heartbeat, buf, MAVLINK_MSG_ID_heartbeat_MIN_LEN, MAVLINK_MSG_ID_heartbeat_LEN, MAVLINK_MSG_ID_heartbeat_CRC);
#else
    mavlink_heartbeat_t *packet = (mavlink_heartbeat_t *)msgbuf;
    packet->msg_type = msg_type;
    packet->sys_stat = sys_stat;
    packet->err_code = err_code;
    mav_array_memcpy(packet->addr, addr, sizeof(uint8_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_heartbeat, (const char *)packet, MAVLINK_MSG_ID_heartbeat_MIN_LEN, MAVLINK_MSG_ID_heartbeat_LEN, MAVLINK_MSG_ID_heartbeat_CRC);
#endif
}
#endif

#endif

// MESSAGE heartbeat UNPACKING


/**
 * @brief Get field msg_type from heartbeat message
 *
 * @return  message type
 */
static inline uint8_t mavlink_msg_heartbeat_get_msg_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field addr from heartbeat message
 *
 * @return  mac address of drone
 */
static inline uint16_t mavlink_msg_heartbeat_get_addr(const mavlink_message_t* msg, uint8_t *addr)
{
    return _MAV_RETURN_uint8_t_array(msg, addr, 6,  1);
}

/**
 * @brief Get field sys_stat from heartbeat message
 *
 * @return   status of system
 */
static inline uint8_t mavlink_msg_heartbeat_get_sys_stat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  7);
}

/**
 * @brief Get field err_code from heartbeat message
 *
 * @return   error code, in case of server error
 */
static inline uint8_t mavlink_msg_heartbeat_get_err_code(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Decode a heartbeat message into a struct
 *
 * @param msg The message to decode
 * @param heartbeat C-struct to decode the message contents into
 */
static inline void mavlink_msg_heartbeat_decode(const mavlink_message_t* msg, mavlink_heartbeat_t* heartbeat)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    heartbeat->msg_type = mavlink_msg_heartbeat_get_msg_type(msg);
    mavlink_msg_heartbeat_get_addr(msg, heartbeat->addr);
    heartbeat->sys_stat = mavlink_msg_heartbeat_get_sys_stat(msg);
    heartbeat->err_code = mavlink_msg_heartbeat_get_err_code(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_heartbeat_LEN? msg->len : MAVLINK_MSG_ID_heartbeat_LEN;
        memset(heartbeat, 0, MAVLINK_MSG_ID_heartbeat_LEN);
    memcpy(heartbeat, _MAV_PAYLOAD(msg), len);
#endif
}
