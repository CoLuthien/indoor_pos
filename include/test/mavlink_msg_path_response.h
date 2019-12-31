#pragma once
// MESSAGE path_response PACKING

#define MAVLINK_MSG_ID_path_response 9

MAVPACKED(
typedef struct __mavlink_path_response_t {
 float x; /*<   x position */
 float y; /*<   y position */
 float z; /*<   z position */
 uint8_t addr[6]; /*<   drone addr*/
 uint8_t index; /*<   order of replay */
}) mavlink_path_response_t;

#define MAVLINK_MSG_ID_path_response_LEN 19
#define MAVLINK_MSG_ID_path_response_MIN_LEN 19
#define MAVLINK_MSG_ID_9_LEN 19
#define MAVLINK_MSG_ID_9_MIN_LEN 19

#define MAVLINK_MSG_ID_path_response_CRC 95
#define MAVLINK_MSG_ID_9_CRC 95

#define MAVLINK_MSG_path_response_FIELD_ADDR_LEN 6

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_path_response { \
    9, \
    "path_response", \
    5, \
    {  { "addr", NULL, MAVLINK_TYPE_UINT8_T, 6, 12, offsetof(mavlink_path_response_t, addr) }, \
         { "index", NULL, MAVLINK_TYPE_UINT8_T, 0, 18, offsetof(mavlink_path_response_t, index) }, \
         { "x", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_path_response_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_path_response_t, y) }, \
         { "z", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_path_response_t, z) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_path_response { \
    "path_response", \
    5, \
    {  { "addr", NULL, MAVLINK_TYPE_UINT8_T, 6, 12, offsetof(mavlink_path_response_t, addr) }, \
         { "index", NULL, MAVLINK_TYPE_UINT8_T, 0, 18, offsetof(mavlink_path_response_t, index) }, \
         { "x", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_path_response_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_path_response_t, y) }, \
         { "z", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_path_response_t, z) }, \
         } \
}
#endif

/**
 * @brief Pack a path_response message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param addr   drone addr
 * @param index   order of replay 
 * @param x   x position 
 * @param y   y position 
 * @param z   z position 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_path_response_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const uint8_t *addr, uint8_t index, float x, float y, float z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_path_response_LEN];
    _mav_put_float(buf, 0, x);
    _mav_put_float(buf, 4, y);
    _mav_put_float(buf, 8, z);
    _mav_put_uint8_t(buf, 18, index);
    _mav_put_uint8_t_array(buf, 12, addr, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_path_response_LEN);
#else
    mavlink_path_response_t packet;
    packet.x = x;
    packet.y = y;
    packet.z = z;
    packet.index = index;
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_path_response_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_path_response;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_path_response_MIN_LEN, MAVLINK_MSG_ID_path_response_LEN, MAVLINK_MSG_ID_path_response_CRC);
}

/**
 * @brief Pack a path_response message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param addr   drone addr
 * @param index   order of replay 
 * @param x   x position 
 * @param y   y position 
 * @param z   z position 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_path_response_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const uint8_t *addr,uint8_t index,float x,float y,float z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_path_response_LEN];
    _mav_put_float(buf, 0, x);
    _mav_put_float(buf, 4, y);
    _mav_put_float(buf, 8, z);
    _mav_put_uint8_t(buf, 18, index);
    _mav_put_uint8_t_array(buf, 12, addr, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_path_response_LEN);
#else
    mavlink_path_response_t packet;
    packet.x = x;
    packet.y = y;
    packet.z = z;
    packet.index = index;
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_path_response_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_path_response;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_path_response_MIN_LEN, MAVLINK_MSG_ID_path_response_LEN, MAVLINK_MSG_ID_path_response_CRC);
}

/**
 * @brief Encode a path_response struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param path_response C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_path_response_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_path_response_t* path_response)
{
    return mavlink_msg_path_response_pack(system_id, component_id, msg, path_response->addr, path_response->index, path_response->x, path_response->y, path_response->z);
}

/**
 * @brief Encode a path_response struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param path_response C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_path_response_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_path_response_t* path_response)
{
    return mavlink_msg_path_response_pack_chan(system_id, component_id, chan, msg, path_response->addr, path_response->index, path_response->x, path_response->y, path_response->z);
}

/**
 * @brief Send a path_response message
 * @param chan MAVLink channel to send the message
 *
 * @param addr   drone addr
 * @param index   order of replay 
 * @param x   x position 
 * @param y   y position 
 * @param z   z position 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_path_response_send(mavlink_channel_t chan, const uint8_t *addr, uint8_t index, float x, float y, float z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_path_response_LEN];
    _mav_put_float(buf, 0, x);
    _mav_put_float(buf, 4, y);
    _mav_put_float(buf, 8, z);
    _mav_put_uint8_t(buf, 18, index);
    _mav_put_uint8_t_array(buf, 12, addr, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_path_response, buf, MAVLINK_MSG_ID_path_response_MIN_LEN, MAVLINK_MSG_ID_path_response_LEN, MAVLINK_MSG_ID_path_response_CRC);
#else
    mavlink_path_response_t packet;
    packet.x = x;
    packet.y = y;
    packet.z = z;
    packet.index = index;
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_path_response, (const char *)&packet, MAVLINK_MSG_ID_path_response_MIN_LEN, MAVLINK_MSG_ID_path_response_LEN, MAVLINK_MSG_ID_path_response_CRC);
#endif
}

/**
 * @brief Send a path_response message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_path_response_send_struct(mavlink_channel_t chan, const mavlink_path_response_t* path_response)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_path_response_send(chan, path_response->addr, path_response->index, path_response->x, path_response->y, path_response->z);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_path_response, (const char *)path_response, MAVLINK_MSG_ID_path_response_MIN_LEN, MAVLINK_MSG_ID_path_response_LEN, MAVLINK_MSG_ID_path_response_CRC);
#endif
}

#if MAVLINK_MSG_ID_path_response_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_path_response_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const uint8_t *addr, uint8_t index, float x, float y, float z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, x);
    _mav_put_float(buf, 4, y);
    _mav_put_float(buf, 8, z);
    _mav_put_uint8_t(buf, 18, index);
    _mav_put_uint8_t_array(buf, 12, addr, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_path_response, buf, MAVLINK_MSG_ID_path_response_MIN_LEN, MAVLINK_MSG_ID_path_response_LEN, MAVLINK_MSG_ID_path_response_CRC);
#else
    mavlink_path_response_t *packet = (mavlink_path_response_t *)msgbuf;
    packet->x = x;
    packet->y = y;
    packet->z = z;
    packet->index = index;
    mav_array_memcpy(packet->addr, addr, sizeof(uint8_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_path_response, (const char *)packet, MAVLINK_MSG_ID_path_response_MIN_LEN, MAVLINK_MSG_ID_path_response_LEN, MAVLINK_MSG_ID_path_response_CRC);
#endif
}
#endif

#endif

// MESSAGE path_response UNPACKING


/**
 * @brief Get field addr from path_response message
 *
 * @return   drone addr
 */
static inline uint16_t mavlink_msg_path_response_get_addr(const mavlink_message_t* msg, uint8_t *addr)
{
    return _MAV_RETURN_uint8_t_array(msg, addr, 6,  12);
}

/**
 * @brief Get field index from path_response message
 *
 * @return   order of replay 
 */
static inline uint8_t mavlink_msg_path_response_get_index(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  18);
}

/**
 * @brief Get field x from path_response message
 *
 * @return   x position 
 */
static inline float mavlink_msg_path_response_get_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field y from path_response message
 *
 * @return   y position 
 */
static inline float mavlink_msg_path_response_get_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field z from path_response message
 *
 * @return   z position 
 */
static inline float mavlink_msg_path_response_get_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Decode a path_response message into a struct
 *
 * @param msg The message to decode
 * @param path_response C-struct to decode the message contents into
 */
static inline void mavlink_msg_path_response_decode(const mavlink_message_t* msg, mavlink_path_response_t* path_response)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    path_response->x = mavlink_msg_path_response_get_x(msg);
    path_response->y = mavlink_msg_path_response_get_y(msg);
    path_response->z = mavlink_msg_path_response_get_z(msg);
    mavlink_msg_path_response_get_addr(msg, path_response->addr);
    path_response->index = mavlink_msg_path_response_get_index(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_path_response_LEN? msg->len : MAVLINK_MSG_ID_path_response_LEN;
        memset(path_response, 0, MAVLINK_MSG_ID_path_response_LEN);
    memcpy(path_response, _MAV_PAYLOAD(msg), len);
#endif
}
