#pragma once
// MESSAGE query PACKING

#define MAVLINK_MSG_ID_query 2

MAVPACKED(
typedef struct __mavlink_query_t {
 uint8_t addr[6]; /*<  mac address of drone*/
 uint8_t node_cnt; /*<   number of querying nodes*/
 uint8_t found_addrs[6]; /*<   addr of found nodes*/
}) mavlink_query_t;

#define MAVLINK_MSG_ID_query_LEN 13
#define MAVLINK_MSG_ID_query_MIN_LEN 13
#define MAVLINK_MSG_ID_2_LEN 13
#define MAVLINK_MSG_ID_2_MIN_LEN 13

#define MAVLINK_MSG_ID_query_CRC 223
#define MAVLINK_MSG_ID_2_CRC 223

#define MAVLINK_MSG_query_FIELD_ADDR_LEN 6
#define MAVLINK_MSG_query_FIELD_FOUND_ADDRS_LEN 6

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_query { \
    2, \
    "query", \
    3, \
    {  { "addr", NULL, MAVLINK_TYPE_UINT8_T, 6, 0, offsetof(mavlink_query_t, addr) }, \
         { "node_cnt", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_query_t, node_cnt) }, \
         { "found_addrs", NULL, MAVLINK_TYPE_UINT8_T, 6, 7, offsetof(mavlink_query_t, found_addrs) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_query { \
    "query", \
    3, \
    {  { "addr", NULL, MAVLINK_TYPE_UINT8_T, 6, 0, offsetof(mavlink_query_t, addr) }, \
         { "node_cnt", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_query_t, node_cnt) }, \
         { "found_addrs", NULL, MAVLINK_TYPE_UINT8_T, 6, 7, offsetof(mavlink_query_t, found_addrs) }, \
         } \
}
#endif

/**
 * @brief Pack a query message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param addr  mac address of drone
 * @param node_cnt   number of querying nodes
 * @param found_addrs   addr of found nodes
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_query_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const uint8_t *addr, uint8_t node_cnt, const uint8_t *found_addrs)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_query_LEN];
    _mav_put_uint8_t(buf, 6, node_cnt);
    _mav_put_uint8_t_array(buf, 0, addr, 6);
    _mav_put_uint8_t_array(buf, 7, found_addrs, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_query_LEN);
#else
    mavlink_query_t packet;
    packet.node_cnt = node_cnt;
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
    mav_array_memcpy(packet.found_addrs, found_addrs, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_query_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_query;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_query_MIN_LEN, MAVLINK_MSG_ID_query_LEN, MAVLINK_MSG_ID_query_CRC);
}

/**
 * @brief Pack a query message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param addr  mac address of drone
 * @param node_cnt   number of querying nodes
 * @param found_addrs   addr of found nodes
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_query_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const uint8_t *addr,uint8_t node_cnt,const uint8_t *found_addrs)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_query_LEN];
    _mav_put_uint8_t(buf, 6, node_cnt);
    _mav_put_uint8_t_array(buf, 0, addr, 6);
    _mav_put_uint8_t_array(buf, 7, found_addrs, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_query_LEN);
#else
    mavlink_query_t packet;
    packet.node_cnt = node_cnt;
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
    mav_array_memcpy(packet.found_addrs, found_addrs, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_query_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_query;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_query_MIN_LEN, MAVLINK_MSG_ID_query_LEN, MAVLINK_MSG_ID_query_CRC);
}

/**
 * @brief Encode a query struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param query C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_query_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_query_t* query)
{
    return mavlink_msg_query_pack(system_id, component_id, msg, query->addr, query->node_cnt, query->found_addrs);
}

/**
 * @brief Encode a query struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param query C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_query_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_query_t* query)
{
    return mavlink_msg_query_pack_chan(system_id, component_id, chan, msg, query->addr, query->node_cnt, query->found_addrs);
}

/**
 * @brief Send a query message
 * @param chan MAVLink channel to send the message
 *
 * @param addr  mac address of drone
 * @param node_cnt   number of querying nodes
 * @param found_addrs   addr of found nodes
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_query_send(mavlink_channel_t chan, const uint8_t *addr, uint8_t node_cnt, const uint8_t *found_addrs)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_query_LEN];
    _mav_put_uint8_t(buf, 6, node_cnt);
    _mav_put_uint8_t_array(buf, 0, addr, 6);
    _mav_put_uint8_t_array(buf, 7, found_addrs, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_query, buf, MAVLINK_MSG_ID_query_MIN_LEN, MAVLINK_MSG_ID_query_LEN, MAVLINK_MSG_ID_query_CRC);
#else
    mavlink_query_t packet;
    packet.node_cnt = node_cnt;
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
    mav_array_memcpy(packet.found_addrs, found_addrs, sizeof(uint8_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_query, (const char *)&packet, MAVLINK_MSG_ID_query_MIN_LEN, MAVLINK_MSG_ID_query_LEN, MAVLINK_MSG_ID_query_CRC);
#endif
}

/**
 * @brief Send a query message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_query_send_struct(mavlink_channel_t chan, const mavlink_query_t* query)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_query_send(chan, query->addr, query->node_cnt, query->found_addrs);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_query, (const char *)query, MAVLINK_MSG_ID_query_MIN_LEN, MAVLINK_MSG_ID_query_LEN, MAVLINK_MSG_ID_query_CRC);
#endif
}

#if MAVLINK_MSG_ID_query_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_query_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const uint8_t *addr, uint8_t node_cnt, const uint8_t *found_addrs)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 6, node_cnt);
    _mav_put_uint8_t_array(buf, 0, addr, 6);
    _mav_put_uint8_t_array(buf, 7, found_addrs, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_query, buf, MAVLINK_MSG_ID_query_MIN_LEN, MAVLINK_MSG_ID_query_LEN, MAVLINK_MSG_ID_query_CRC);
#else
    mavlink_query_t *packet = (mavlink_query_t *)msgbuf;
    packet->node_cnt = node_cnt;
    mav_array_memcpy(packet->addr, addr, sizeof(uint8_t)*6);
    mav_array_memcpy(packet->found_addrs, found_addrs, sizeof(uint8_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_query, (const char *)packet, MAVLINK_MSG_ID_query_MIN_LEN, MAVLINK_MSG_ID_query_LEN, MAVLINK_MSG_ID_query_CRC);
#endif
}
#endif

#endif

// MESSAGE query UNPACKING


/**
 * @brief Get field addr from query message
 *
 * @return  mac address of drone
 */
static inline uint16_t mavlink_msg_query_get_addr(const mavlink_message_t* msg, uint8_t *addr)
{
    return _MAV_RETURN_uint8_t_array(msg, addr, 6,  0);
}

/**
 * @brief Get field node_cnt from query message
 *
 * @return   number of querying nodes
 */
static inline uint8_t mavlink_msg_query_get_node_cnt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  6);
}

/**
 * @brief Get field found_addrs from query message
 *
 * @return   addr of found nodes
 */
static inline uint16_t mavlink_msg_query_get_found_addrs(const mavlink_message_t* msg, uint8_t *found_addrs)
{
    return _MAV_RETURN_uint8_t_array(msg, found_addrs, 6,  7);
}

/**
 * @brief Decode a query message into a struct
 *
 * @param msg The message to decode
 * @param query C-struct to decode the message contents into
 */
static inline void mavlink_msg_query_decode(const mavlink_message_t* msg, mavlink_query_t* query)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_query_get_addr(msg, query->addr);
    query->node_cnt = mavlink_msg_query_get_node_cnt(msg);
    mavlink_msg_query_get_found_addrs(msg, query->found_addrs);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_query_LEN? msg->len : MAVLINK_MSG_ID_query_LEN;
        memset(query, 0, MAVLINK_MSG_ID_query_LEN);
    memcpy(query, _MAV_PAYLOAD(msg), len);
#endif
}
