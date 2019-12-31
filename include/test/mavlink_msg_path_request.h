#pragma once
// MESSAGE path_request PACKING

#define MAVLINK_MSG_ID_path_request 8

MAVPACKED(
typedef struct __mavlink_path_request_t {
 uint16_t interval; /*<   interval in ms*/
 uint8_t addr[6]; /*<   drone addr*/
 uint8_t back_to; /*<   back to second*/
}) mavlink_path_request_t;

#define MAVLINK_MSG_ID_path_request_LEN 9
#define MAVLINK_MSG_ID_path_request_MIN_LEN 9
#define MAVLINK_MSG_ID_8_LEN 9
#define MAVLINK_MSG_ID_8_MIN_LEN 9

#define MAVLINK_MSG_ID_path_request_CRC 163
#define MAVLINK_MSG_ID_8_CRC 163

#define MAVLINK_MSG_path_request_FIELD_ADDR_LEN 6

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_path_request { \
    8, \
    "path_request", \
    3, \
    {  { "addr", NULL, MAVLINK_TYPE_UINT8_T, 6, 2, offsetof(mavlink_path_request_t, addr) }, \
         { "back_to", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_path_request_t, back_to) }, \
         { "interval", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_path_request_t, interval) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_path_request { \
    "path_request", \
    3, \
    {  { "addr", NULL, MAVLINK_TYPE_UINT8_T, 6, 2, offsetof(mavlink_path_request_t, addr) }, \
         { "back_to", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_path_request_t, back_to) }, \
         { "interval", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_path_request_t, interval) }, \
         } \
}
#endif

/**
 * @brief Pack a path_request message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param addr   drone addr
 * @param back_to   back to second
 * @param interval   interval in ms
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_path_request_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const uint8_t *addr, uint8_t back_to, uint16_t interval)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_path_request_LEN];
    _mav_put_uint16_t(buf, 0, interval);
    _mav_put_uint8_t(buf, 8, back_to);
    _mav_put_uint8_t_array(buf, 2, addr, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_path_request_LEN);
#else
    mavlink_path_request_t packet;
    packet.interval = interval;
    packet.back_to = back_to;
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_path_request_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_path_request;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_path_request_MIN_LEN, MAVLINK_MSG_ID_path_request_LEN, MAVLINK_MSG_ID_path_request_CRC);
}

/**
 * @brief Pack a path_request message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param addr   drone addr
 * @param back_to   back to second
 * @param interval   interval in ms
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_path_request_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const uint8_t *addr,uint8_t back_to,uint16_t interval)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_path_request_LEN];
    _mav_put_uint16_t(buf, 0, interval);
    _mav_put_uint8_t(buf, 8, back_to);
    _mav_put_uint8_t_array(buf, 2, addr, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_path_request_LEN);
#else
    mavlink_path_request_t packet;
    packet.interval = interval;
    packet.back_to = back_to;
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_path_request_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_path_request;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_path_request_MIN_LEN, MAVLINK_MSG_ID_path_request_LEN, MAVLINK_MSG_ID_path_request_CRC);
}

/**
 * @brief Encode a path_request struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param path_request C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_path_request_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_path_request_t* path_request)
{
    return mavlink_msg_path_request_pack(system_id, component_id, msg, path_request->addr, path_request->back_to, path_request->interval);
}

/**
 * @brief Encode a path_request struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param path_request C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_path_request_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_path_request_t* path_request)
{
    return mavlink_msg_path_request_pack_chan(system_id, component_id, chan, msg, path_request->addr, path_request->back_to, path_request->interval);
}

/**
 * @brief Send a path_request message
 * @param chan MAVLink channel to send the message
 *
 * @param addr   drone addr
 * @param back_to   back to second
 * @param interval   interval in ms
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_path_request_send(mavlink_channel_t chan, const uint8_t *addr, uint8_t back_to, uint16_t interval)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_path_request_LEN];
    _mav_put_uint16_t(buf, 0, interval);
    _mav_put_uint8_t(buf, 8, back_to);
    _mav_put_uint8_t_array(buf, 2, addr, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_path_request, buf, MAVLINK_MSG_ID_path_request_MIN_LEN, MAVLINK_MSG_ID_path_request_LEN, MAVLINK_MSG_ID_path_request_CRC);
#else
    mavlink_path_request_t packet;
    packet.interval = interval;
    packet.back_to = back_to;
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_path_request, (const char *)&packet, MAVLINK_MSG_ID_path_request_MIN_LEN, MAVLINK_MSG_ID_path_request_LEN, MAVLINK_MSG_ID_path_request_CRC);
#endif
}

/**
 * @brief Send a path_request message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_path_request_send_struct(mavlink_channel_t chan, const mavlink_path_request_t* path_request)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_path_request_send(chan, path_request->addr, path_request->back_to, path_request->interval);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_path_request, (const char *)path_request, MAVLINK_MSG_ID_path_request_MIN_LEN, MAVLINK_MSG_ID_path_request_LEN, MAVLINK_MSG_ID_path_request_CRC);
#endif
}

#if MAVLINK_MSG_ID_path_request_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_path_request_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const uint8_t *addr, uint8_t back_to, uint16_t interval)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint16_t(buf, 0, interval);
    _mav_put_uint8_t(buf, 8, back_to);
    _mav_put_uint8_t_array(buf, 2, addr, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_path_request, buf, MAVLINK_MSG_ID_path_request_MIN_LEN, MAVLINK_MSG_ID_path_request_LEN, MAVLINK_MSG_ID_path_request_CRC);
#else
    mavlink_path_request_t *packet = (mavlink_path_request_t *)msgbuf;
    packet->interval = interval;
    packet->back_to = back_to;
    mav_array_memcpy(packet->addr, addr, sizeof(uint8_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_path_request, (const char *)packet, MAVLINK_MSG_ID_path_request_MIN_LEN, MAVLINK_MSG_ID_path_request_LEN, MAVLINK_MSG_ID_path_request_CRC);
#endif
}
#endif

#endif

// MESSAGE path_request UNPACKING


/**
 * @brief Get field addr from path_request message
 *
 * @return   drone addr
 */
static inline uint16_t mavlink_msg_path_request_get_addr(const mavlink_message_t* msg, uint8_t *addr)
{
    return _MAV_RETURN_uint8_t_array(msg, addr, 6,  2);
}

/**
 * @brief Get field back_to from path_request message
 *
 * @return   back to second
 */
static inline uint8_t mavlink_msg_path_request_get_back_to(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Get field interval from path_request message
 *
 * @return   interval in ms
 */
static inline uint16_t mavlink_msg_path_request_get_interval(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Decode a path_request message into a struct
 *
 * @param msg The message to decode
 * @param path_request C-struct to decode the message contents into
 */
static inline void mavlink_msg_path_request_decode(const mavlink_message_t* msg, mavlink_path_request_t* path_request)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    path_request->interval = mavlink_msg_path_request_get_interval(msg);
    mavlink_msg_path_request_get_addr(msg, path_request->addr);
    path_request->back_to = mavlink_msg_path_request_get_back_to(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_path_request_LEN? msg->len : MAVLINK_MSG_ID_path_request_LEN;
        memset(path_request, 0, MAVLINK_MSG_ID_path_request_LEN);
    memcpy(path_request, _MAV_PAYLOAD(msg), len);
#endif
}
