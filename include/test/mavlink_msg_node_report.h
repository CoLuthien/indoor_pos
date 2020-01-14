#pragma once
// MESSAGE node_report PACKING

#define MAVLINK_MSG_ID_node_report 6

MAVPACKED(
typedef struct __mavlink_node_report_t {
 uint8_t source_addr[6]; /*<  mac addr of drone*/
 uint8_t report_cnt; /*<   how many node to read?, maximum 16*/
 uint8_t node_status; /*<   status of node */
 uint8_t node_addr[6]; /*<   node addr */
 int8_t rssi; /*<   current rssi of node */
}) mavlink_node_report_t;

#define MAVLINK_MSG_ID_node_report_LEN 15
#define MAVLINK_MSG_ID_node_report_MIN_LEN 15
#define MAVLINK_MSG_ID_6_LEN 15
#define MAVLINK_MSG_ID_6_MIN_LEN 15

#define MAVLINK_MSG_ID_node_report_CRC 43
#define MAVLINK_MSG_ID_6_CRC 43

#define MAVLINK_MSG_node_report_FIELD_SOURCE_ADDR_LEN 6
#define MAVLINK_MSG_node_report_FIELD_NODE_ADDR_LEN 6

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_node_report { \
    6, \
    "node_report", \
    5, \
    {  { "source_addr", NULL, MAVLINK_TYPE_UINT8_T, 6, 0, offsetof(mavlink_node_report_t, source_addr) }, \
         { "report_cnt", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_node_report_t, report_cnt) }, \
         { "node_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 7, offsetof(mavlink_node_report_t, node_status) }, \
         { "node_addr", NULL, MAVLINK_TYPE_UINT8_T, 6, 8, offsetof(mavlink_node_report_t, node_addr) }, \
         { "rssi", NULL, MAVLINK_TYPE_INT8_T, 0, 14, offsetof(mavlink_node_report_t, rssi) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_node_report { \
    "node_report", \
    5, \
    {  { "source_addr", NULL, MAVLINK_TYPE_UINT8_T, 6, 0, offsetof(mavlink_node_report_t, source_addr) }, \
         { "report_cnt", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_node_report_t, report_cnt) }, \
         { "node_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 7, offsetof(mavlink_node_report_t, node_status) }, \
         { "node_addr", NULL, MAVLINK_TYPE_UINT8_T, 6, 8, offsetof(mavlink_node_report_t, node_addr) }, \
         { "rssi", NULL, MAVLINK_TYPE_INT8_T, 0, 14, offsetof(mavlink_node_report_t, rssi) }, \
         } \
}
#endif

/**
 * @brief Pack a node_report message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param source_addr  mac addr of drone
 * @param report_cnt   how many node to read?, maximum 16
 * @param node_status   status of node 
 * @param node_addr   node addr 
 * @param rssi   current rssi of node 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_node_report_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const uint8_t *source_addr, uint8_t report_cnt, uint8_t node_status, const uint8_t *node_addr, int8_t rssi)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_node_report_LEN];
    _mav_put_uint8_t(buf, 6, report_cnt);
    _mav_put_uint8_t(buf, 7, node_status);
    _mav_put_int8_t(buf, 14, rssi);
    _mav_put_uint8_t_array(buf, 0, source_addr, 6);
    _mav_put_uint8_t_array(buf, 8, node_addr, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_node_report_LEN);
#else
    mavlink_node_report_t packet;
    packet.report_cnt = report_cnt;
    packet.node_status = node_status;
    packet.rssi = rssi;
    mav_array_memcpy(packet.source_addr, source_addr, sizeof(uint8_t)*6);
    mav_array_memcpy(packet.node_addr, node_addr, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_node_report_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_node_report;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_node_report_MIN_LEN, MAVLINK_MSG_ID_node_report_LEN, MAVLINK_MSG_ID_node_report_CRC);
}

/**
 * @brief Pack a node_report message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param source_addr  mac addr of drone
 * @param report_cnt   how many node to read?, maximum 16
 * @param node_status   status of node 
 * @param node_addr   node addr 
 * @param rssi   current rssi of node 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_node_report_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const uint8_t *source_addr,uint8_t report_cnt,uint8_t node_status,const uint8_t *node_addr,int8_t rssi)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_node_report_LEN];
    _mav_put_uint8_t(buf, 6, report_cnt);
    _mav_put_uint8_t(buf, 7, node_status);
    _mav_put_int8_t(buf, 14, rssi);
    _mav_put_uint8_t_array(buf, 0, source_addr, 6);
    _mav_put_uint8_t_array(buf, 8, node_addr, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_node_report_LEN);
#else
    mavlink_node_report_t packet;
    packet.report_cnt = report_cnt;
    packet.node_status = node_status;
    packet.rssi = rssi;
    mav_array_memcpy(packet.source_addr, source_addr, sizeof(uint8_t)*6);
    mav_array_memcpy(packet.node_addr, node_addr, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_node_report_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_node_report;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_node_report_MIN_LEN, MAVLINK_MSG_ID_node_report_LEN, MAVLINK_MSG_ID_node_report_CRC);
}

/**
 * @brief Encode a node_report struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param node_report C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_node_report_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_node_report_t* node_report)
{
    return mavlink_msg_node_report_pack(system_id, component_id, msg, node_report->source_addr, node_report->report_cnt, node_report->node_status, node_report->node_addr, node_report->rssi);
}

/**
 * @brief Encode a node_report struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param node_report C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_node_report_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_node_report_t* node_report)
{
    return mavlink_msg_node_report_pack_chan(system_id, component_id, chan, msg, node_report->source_addr, node_report->report_cnt, node_report->node_status, node_report->node_addr, node_report->rssi);
}

/**
 * @brief Send a node_report message
 * @param chan MAVLink channel to send the message
 *
 * @param source_addr  mac addr of drone
 * @param report_cnt   how many node to read?, maximum 16
 * @param node_status   status of node 
 * @param node_addr   node addr 
 * @param rssi   current rssi of node 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_node_report_send(mavlink_channel_t chan, const uint8_t *source_addr, uint8_t report_cnt, uint8_t node_status, const uint8_t *node_addr, int8_t rssi)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_node_report_LEN];
    _mav_put_uint8_t(buf, 6, report_cnt);
    _mav_put_uint8_t(buf, 7, node_status);
    _mav_put_int8_t(buf, 14, rssi);
    _mav_put_uint8_t_array(buf, 0, source_addr, 6);
    _mav_put_uint8_t_array(buf, 8, node_addr, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_node_report, buf, MAVLINK_MSG_ID_node_report_MIN_LEN, MAVLINK_MSG_ID_node_report_LEN, MAVLINK_MSG_ID_node_report_CRC);
#else
    mavlink_node_report_t packet;
    packet.report_cnt = report_cnt;
    packet.node_status = node_status;
    packet.rssi = rssi;
    mav_array_memcpy(packet.source_addr, source_addr, sizeof(uint8_t)*6);
    mav_array_memcpy(packet.node_addr, node_addr, sizeof(uint8_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_node_report, (const char *)&packet, MAVLINK_MSG_ID_node_report_MIN_LEN, MAVLINK_MSG_ID_node_report_LEN, MAVLINK_MSG_ID_node_report_CRC);
#endif
}

/**
 * @brief Send a node_report message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_node_report_send_struct(mavlink_channel_t chan, const mavlink_node_report_t* node_report)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_node_report_send(chan, node_report->source_addr, node_report->report_cnt, node_report->node_status, node_report->node_addr, node_report->rssi);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_node_report, (const char *)node_report, MAVLINK_MSG_ID_node_report_MIN_LEN, MAVLINK_MSG_ID_node_report_LEN, MAVLINK_MSG_ID_node_report_CRC);
#endif
}

#if MAVLINK_MSG_ID_node_report_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_node_report_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const uint8_t *source_addr, uint8_t report_cnt, uint8_t node_status, const uint8_t *node_addr, int8_t rssi)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 6, report_cnt);
    _mav_put_uint8_t(buf, 7, node_status);
    _mav_put_int8_t(buf, 14, rssi);
    _mav_put_uint8_t_array(buf, 0, source_addr, 6);
    _mav_put_uint8_t_array(buf, 8, node_addr, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_node_report, buf, MAVLINK_MSG_ID_node_report_MIN_LEN, MAVLINK_MSG_ID_node_report_LEN, MAVLINK_MSG_ID_node_report_CRC);
#else
    mavlink_node_report_t *packet = (mavlink_node_report_t *)msgbuf;
    packet->report_cnt = report_cnt;
    packet->node_status = node_status;
    packet->rssi = rssi;
    mav_array_memcpy(packet->source_addr, source_addr, sizeof(uint8_t)*6);
    mav_array_memcpy(packet->node_addr, node_addr, sizeof(uint8_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_node_report, (const char *)packet, MAVLINK_MSG_ID_node_report_MIN_LEN, MAVLINK_MSG_ID_node_report_LEN, MAVLINK_MSG_ID_node_report_CRC);
#endif
}
#endif

#endif

// MESSAGE node_report UNPACKING


/**
 * @brief Get field source_addr from node_report message
 *
 * @return  mac addr of drone
 */
static inline uint16_t mavlink_msg_node_report_get_source_addr(const mavlink_message_t* msg, uint8_t *source_addr)
{
    return _MAV_RETURN_uint8_t_array(msg, source_addr, 6,  0);
}

/**
 * @brief Get field report_cnt from node_report message
 *
 * @return   how many node to read?, maximum 16
 */
static inline uint8_t mavlink_msg_node_report_get_report_cnt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  6);
}

/**
 * @brief Get field node_status from node_report message
 *
 * @return   status of node 
 */
static inline uint8_t mavlink_msg_node_report_get_node_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  7);
}

/**
 * @brief Get field node_addr from node_report message
 *
 * @return   node addr 
 */
static inline uint16_t mavlink_msg_node_report_get_node_addr(const mavlink_message_t* msg, uint8_t *node_addr)
{
    return _MAV_RETURN_uint8_t_array(msg, node_addr, 6,  8);
}

/**
 * @brief Get field rssi from node_report message
 *
 * @return   current rssi of node 
 */
static inline int8_t mavlink_msg_node_report_get_rssi(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  14);
}

/**
 * @brief Decode a node_report message into a struct
 *
 * @param msg The message to decode
 * @param node_report C-struct to decode the message contents into
 */
static inline void mavlink_msg_node_report_decode(const mavlink_message_t* msg, mavlink_node_report_t* node_report)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_node_report_get_source_addr(msg, node_report->source_addr);
    node_report->report_cnt = mavlink_msg_node_report_get_report_cnt(msg);
    node_report->node_status = mavlink_msg_node_report_get_node_status(msg);
    mavlink_msg_node_report_get_node_addr(msg, node_report->node_addr);
    node_report->rssi = mavlink_msg_node_report_get_rssi(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_node_report_LEN? msg->len : MAVLINK_MSG_ID_node_report_LEN;
        memset(node_report, 0, MAVLINK_MSG_ID_node_report_LEN);
    memcpy(node_report, _MAV_PAYLOAD(msg), len);
#endif
}
