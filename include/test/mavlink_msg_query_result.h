#pragma once
// MESSAGE query_result PACKING

#define MAVLINK_MSG_ID_query_result 3

MAVPACKED(
typedef struct __mavlink_query_result_t {
 float x; /*<   x position */
 float y; /*<   y position */
 float z; /*<   z position */
 uint8_t addr[6]; /*<  mac address of drone*/
 uint8_t match_addr[6]; /*<   matched node's addr*/
 uint8_t is_usable; /*<   is this node_usable? */
}) mavlink_query_result_t;

#define MAVLINK_MSG_ID_query_result_LEN 25
#define MAVLINK_MSG_ID_query_result_MIN_LEN 25
#define MAVLINK_MSG_ID_3_LEN 25
#define MAVLINK_MSG_ID_3_MIN_LEN 25

#define MAVLINK_MSG_ID_query_result_CRC 59
#define MAVLINK_MSG_ID_3_CRC 59

#define MAVLINK_MSG_query_result_FIELD_ADDR_LEN 6
#define MAVLINK_MSG_query_result_FIELD_MATCH_ADDR_LEN 6

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_query_result { \
    3, \
    "query_result", \
    6, \
    {  { "addr", NULL, MAVLINK_TYPE_UINT8_T, 6, 12, offsetof(mavlink_query_result_t, addr) }, \
         { "match_addr", NULL, MAVLINK_TYPE_UINT8_T, 6, 18, offsetof(mavlink_query_result_t, match_addr) }, \
         { "is_usable", NULL, MAVLINK_TYPE_UINT8_T, 0, 24, offsetof(mavlink_query_result_t, is_usable) }, \
         { "x", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_query_result_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_query_result_t, y) }, \
         { "z", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_query_result_t, z) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_query_result { \
    "query_result", \
    6, \
    {  { "addr", NULL, MAVLINK_TYPE_UINT8_T, 6, 12, offsetof(mavlink_query_result_t, addr) }, \
         { "match_addr", NULL, MAVLINK_TYPE_UINT8_T, 6, 18, offsetof(mavlink_query_result_t, match_addr) }, \
         { "is_usable", NULL, MAVLINK_TYPE_UINT8_T, 0, 24, offsetof(mavlink_query_result_t, is_usable) }, \
         { "x", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_query_result_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_query_result_t, y) }, \
         { "z", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_query_result_t, z) }, \
         } \
}
#endif

/**
 * @brief Pack a query_result message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param addr  mac address of drone
 * @param match_addr   matched node's addr
 * @param is_usable   is this node_usable? 
 * @param x   x position 
 * @param y   y position 
 * @param z   z position 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_query_result_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const uint8_t *addr, const uint8_t *match_addr, uint8_t is_usable, float x, float y, float z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_query_result_LEN];
    _mav_put_float(buf, 0, x);
    _mav_put_float(buf, 4, y);
    _mav_put_float(buf, 8, z);
    _mav_put_uint8_t(buf, 24, is_usable);
    _mav_put_uint8_t_array(buf, 12, addr, 6);
    _mav_put_uint8_t_array(buf, 18, match_addr, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_query_result_LEN);
#else
    mavlink_query_result_t packet;
    packet.x = x;
    packet.y = y;
    packet.z = z;
    packet.is_usable = is_usable;
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
    mav_array_memcpy(packet.match_addr, match_addr, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_query_result_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_query_result;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_query_result_MIN_LEN, MAVLINK_MSG_ID_query_result_LEN, MAVLINK_MSG_ID_query_result_CRC);
}

/**
 * @brief Pack a query_result message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param addr  mac address of drone
 * @param match_addr   matched node's addr
 * @param is_usable   is this node_usable? 
 * @param x   x position 
 * @param y   y position 
 * @param z   z position 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_query_result_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const uint8_t *addr,const uint8_t *match_addr,uint8_t is_usable,float x,float y,float z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_query_result_LEN];
    _mav_put_float(buf, 0, x);
    _mav_put_float(buf, 4, y);
    _mav_put_float(buf, 8, z);
    _mav_put_uint8_t(buf, 24, is_usable);
    _mav_put_uint8_t_array(buf, 12, addr, 6);
    _mav_put_uint8_t_array(buf, 18, match_addr, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_query_result_LEN);
#else
    mavlink_query_result_t packet;
    packet.x = x;
    packet.y = y;
    packet.z = z;
    packet.is_usable = is_usable;
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
    mav_array_memcpy(packet.match_addr, match_addr, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_query_result_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_query_result;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_query_result_MIN_LEN, MAVLINK_MSG_ID_query_result_LEN, MAVLINK_MSG_ID_query_result_CRC);
}

/**
 * @brief Encode a query_result struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param query_result C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_query_result_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_query_result_t* query_result)
{
    return mavlink_msg_query_result_pack(system_id, component_id, msg, query_result->addr, query_result->match_addr, query_result->is_usable, query_result->x, query_result->y, query_result->z);
}

/**
 * @brief Encode a query_result struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param query_result C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_query_result_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_query_result_t* query_result)
{
    return mavlink_msg_query_result_pack_chan(system_id, component_id, chan, msg, query_result->addr, query_result->match_addr, query_result->is_usable, query_result->x, query_result->y, query_result->z);
}

/**
 * @brief Send a query_result message
 * @param chan MAVLink channel to send the message
 *
 * @param addr  mac address of drone
 * @param match_addr   matched node's addr
 * @param is_usable   is this node_usable? 
 * @param x   x position 
 * @param y   y position 
 * @param z   z position 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_query_result_send(mavlink_channel_t chan, const uint8_t *addr, const uint8_t *match_addr, uint8_t is_usable, float x, float y, float z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_query_result_LEN];
    _mav_put_float(buf, 0, x);
    _mav_put_float(buf, 4, y);
    _mav_put_float(buf, 8, z);
    _mav_put_uint8_t(buf, 24, is_usable);
    _mav_put_uint8_t_array(buf, 12, addr, 6);
    _mav_put_uint8_t_array(buf, 18, match_addr, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_query_result, buf, MAVLINK_MSG_ID_query_result_MIN_LEN, MAVLINK_MSG_ID_query_result_LEN, MAVLINK_MSG_ID_query_result_CRC);
#else
    mavlink_query_result_t packet;
    packet.x = x;
    packet.y = y;
    packet.z = z;
    packet.is_usable = is_usable;
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
    mav_array_memcpy(packet.match_addr, match_addr, sizeof(uint8_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_query_result, (const char *)&packet, MAVLINK_MSG_ID_query_result_MIN_LEN, MAVLINK_MSG_ID_query_result_LEN, MAVLINK_MSG_ID_query_result_CRC);
#endif
}

/**
 * @brief Send a query_result message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_query_result_send_struct(mavlink_channel_t chan, const mavlink_query_result_t* query_result)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_query_result_send(chan, query_result->addr, query_result->match_addr, query_result->is_usable, query_result->x, query_result->y, query_result->z);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_query_result, (const char *)query_result, MAVLINK_MSG_ID_query_result_MIN_LEN, MAVLINK_MSG_ID_query_result_LEN, MAVLINK_MSG_ID_query_result_CRC);
#endif
}

#if MAVLINK_MSG_ID_query_result_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_query_result_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const uint8_t *addr, const uint8_t *match_addr, uint8_t is_usable, float x, float y, float z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, x);
    _mav_put_float(buf, 4, y);
    _mav_put_float(buf, 8, z);
    _mav_put_uint8_t(buf, 24, is_usable);
    _mav_put_uint8_t_array(buf, 12, addr, 6);
    _mav_put_uint8_t_array(buf, 18, match_addr, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_query_result, buf, MAVLINK_MSG_ID_query_result_MIN_LEN, MAVLINK_MSG_ID_query_result_LEN, MAVLINK_MSG_ID_query_result_CRC);
#else
    mavlink_query_result_t *packet = (mavlink_query_result_t *)msgbuf;
    packet->x = x;
    packet->y = y;
    packet->z = z;
    packet->is_usable = is_usable;
    mav_array_memcpy(packet->addr, addr, sizeof(uint8_t)*6);
    mav_array_memcpy(packet->match_addr, match_addr, sizeof(uint8_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_query_result, (const char *)packet, MAVLINK_MSG_ID_query_result_MIN_LEN, MAVLINK_MSG_ID_query_result_LEN, MAVLINK_MSG_ID_query_result_CRC);
#endif
}
#endif

#endif

// MESSAGE query_result UNPACKING


/**
 * @brief Get field addr from query_result message
 *
 * @return  mac address of drone
 */
static inline uint16_t mavlink_msg_query_result_get_addr(const mavlink_message_t* msg, uint8_t *addr)
{
    return _MAV_RETURN_uint8_t_array(msg, addr, 6,  12);
}

/**
 * @brief Get field match_addr from query_result message
 *
 * @return   matched node's addr
 */
static inline uint16_t mavlink_msg_query_result_get_match_addr(const mavlink_message_t* msg, uint8_t *match_addr)
{
    return _MAV_RETURN_uint8_t_array(msg, match_addr, 6,  18);
}

/**
 * @brief Get field is_usable from query_result message
 *
 * @return   is this node_usable? 
 */
static inline uint8_t mavlink_msg_query_result_get_is_usable(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  24);
}

/**
 * @brief Get field x from query_result message
 *
 * @return   x position 
 */
static inline float mavlink_msg_query_result_get_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field y from query_result message
 *
 * @return   y position 
 */
static inline float mavlink_msg_query_result_get_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field z from query_result message
 *
 * @return   z position 
 */
static inline float mavlink_msg_query_result_get_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Decode a query_result message into a struct
 *
 * @param msg The message to decode
 * @param query_result C-struct to decode the message contents into
 */
static inline void mavlink_msg_query_result_decode(const mavlink_message_t* msg, mavlink_query_result_t* query_result)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    query_result->x = mavlink_msg_query_result_get_x(msg);
    query_result->y = mavlink_msg_query_result_get_y(msg);
    query_result->z = mavlink_msg_query_result_get_z(msg);
    mavlink_msg_query_result_get_addr(msg, query_result->addr);
    mavlink_msg_query_result_get_match_addr(msg, query_result->match_addr);
    query_result->is_usable = mavlink_msg_query_result_get_is_usable(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_query_result_LEN? msg->len : MAVLINK_MSG_ID_query_result_LEN;
        memset(query_result, 0, MAVLINK_MSG_ID_query_result_LEN);
    memcpy(query_result, _MAV_PAYLOAD(msg), len);
#endif
}
