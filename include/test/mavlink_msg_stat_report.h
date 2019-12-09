#pragma once
// MESSAGE stat_report PACKING

#define MAVLINK_MSG_ID_stat_report 1

MAVPACKED(
typedef struct __mavlink_stat_report_t {
 float position[3]; /*<   current position, estimated*/
 uint8_t addr[6]; /*<  mac address of drone*/
 uint8_t sys_stat; /*<   status of system*/
 uint8_t node_cnt; /*<   number of active ble nodes*/
}) mavlink_stat_report_t;

#define MAVLINK_MSG_ID_stat_report_LEN 20
#define MAVLINK_MSG_ID_stat_report_MIN_LEN 20
#define MAVLINK_MSG_ID_1_LEN 20
#define MAVLINK_MSG_ID_1_MIN_LEN 20

#define MAVLINK_MSG_ID_stat_report_CRC 169
#define MAVLINK_MSG_ID_1_CRC 169

#define MAVLINK_MSG_stat_report_FIELD_POSITION_LEN 3
#define MAVLINK_MSG_stat_report_FIELD_ADDR_LEN 6

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_stat_report { \
    1, \
    "stat_report", \
    4, \
    {  { "addr", NULL, MAVLINK_TYPE_UINT8_T, 6, 12, offsetof(mavlink_stat_report_t, addr) }, \
         { "sys_stat", NULL, MAVLINK_TYPE_UINT8_T, 0, 18, offsetof(mavlink_stat_report_t, sys_stat) }, \
         { "node_cnt", NULL, MAVLINK_TYPE_UINT8_T, 0, 19, offsetof(mavlink_stat_report_t, node_cnt) }, \
         { "position", NULL, MAVLINK_TYPE_FLOAT, 3, 0, offsetof(mavlink_stat_report_t, position) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_stat_report { \
    "stat_report", \
    4, \
    {  { "addr", NULL, MAVLINK_TYPE_UINT8_T, 6, 12, offsetof(mavlink_stat_report_t, addr) }, \
         { "sys_stat", NULL, MAVLINK_TYPE_UINT8_T, 0, 18, offsetof(mavlink_stat_report_t, sys_stat) }, \
         { "node_cnt", NULL, MAVLINK_TYPE_UINT8_T, 0, 19, offsetof(mavlink_stat_report_t, node_cnt) }, \
         { "position", NULL, MAVLINK_TYPE_FLOAT, 3, 0, offsetof(mavlink_stat_report_t, position) }, \
         } \
}
#endif

/**
 * @brief Pack a stat_report message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param addr  mac address of drone
 * @param sys_stat   status of system
 * @param node_cnt   number of active ble nodes
 * @param position   current position, estimated
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_stat_report_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const uint8_t *addr, uint8_t sys_stat, uint8_t node_cnt, const float *position)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_stat_report_LEN];
    _mav_put_uint8_t(buf, 18, sys_stat);
    _mav_put_uint8_t(buf, 19, node_cnt);
    _mav_put_float_array(buf, 0, position, 3);
    _mav_put_uint8_t_array(buf, 12, addr, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_stat_report_LEN);
#else
    mavlink_stat_report_t packet;
    packet.sys_stat = sys_stat;
    packet.node_cnt = node_cnt;
    mav_array_memcpy(packet.position, position, sizeof(float)*3);
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_stat_report_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_stat_report;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_stat_report_MIN_LEN, MAVLINK_MSG_ID_stat_report_LEN, MAVLINK_MSG_ID_stat_report_CRC);
}

/**
 * @brief Pack a stat_report message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param addr  mac address of drone
 * @param sys_stat   status of system
 * @param node_cnt   number of active ble nodes
 * @param position   current position, estimated
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_stat_report_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const uint8_t *addr,uint8_t sys_stat,uint8_t node_cnt,const float *position)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_stat_report_LEN];
    _mav_put_uint8_t(buf, 18, sys_stat);
    _mav_put_uint8_t(buf, 19, node_cnt);
    _mav_put_float_array(buf, 0, position, 3);
    _mav_put_uint8_t_array(buf, 12, addr, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_stat_report_LEN);
#else
    mavlink_stat_report_t packet;
    packet.sys_stat = sys_stat;
    packet.node_cnt = node_cnt;
    mav_array_memcpy(packet.position, position, sizeof(float)*3);
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_stat_report_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_stat_report;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_stat_report_MIN_LEN, MAVLINK_MSG_ID_stat_report_LEN, MAVLINK_MSG_ID_stat_report_CRC);
}

/**
 * @brief Encode a stat_report struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param stat_report C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_stat_report_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_stat_report_t* stat_report)
{
    return mavlink_msg_stat_report_pack(system_id, component_id, msg, stat_report->addr, stat_report->sys_stat, stat_report->node_cnt, stat_report->position);
}

/**
 * @brief Encode a stat_report struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param stat_report C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_stat_report_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_stat_report_t* stat_report)
{
    return mavlink_msg_stat_report_pack_chan(system_id, component_id, chan, msg, stat_report->addr, stat_report->sys_stat, stat_report->node_cnt, stat_report->position);
}

/**
 * @brief Send a stat_report message
 * @param chan MAVLink channel to send the message
 *
 * @param addr  mac address of drone
 * @param sys_stat   status of system
 * @param node_cnt   number of active ble nodes
 * @param position   current position, estimated
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_stat_report_send(mavlink_channel_t chan, const uint8_t *addr, uint8_t sys_stat, uint8_t node_cnt, const float *position)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_stat_report_LEN];
    _mav_put_uint8_t(buf, 18, sys_stat);
    _mav_put_uint8_t(buf, 19, node_cnt);
    _mav_put_float_array(buf, 0, position, 3);
    _mav_put_uint8_t_array(buf, 12, addr, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_stat_report, buf, MAVLINK_MSG_ID_stat_report_MIN_LEN, MAVLINK_MSG_ID_stat_report_LEN, MAVLINK_MSG_ID_stat_report_CRC);
#else
    mavlink_stat_report_t packet;
    packet.sys_stat = sys_stat;
    packet.node_cnt = node_cnt;
    mav_array_memcpy(packet.position, position, sizeof(float)*3);
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_stat_report, (const char *)&packet, MAVLINK_MSG_ID_stat_report_MIN_LEN, MAVLINK_MSG_ID_stat_report_LEN, MAVLINK_MSG_ID_stat_report_CRC);
#endif
}

/**
 * @brief Send a stat_report message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_stat_report_send_struct(mavlink_channel_t chan, const mavlink_stat_report_t* stat_report)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_stat_report_send(chan, stat_report->addr, stat_report->sys_stat, stat_report->node_cnt, stat_report->position);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_stat_report, (const char *)stat_report, MAVLINK_MSG_ID_stat_report_MIN_LEN, MAVLINK_MSG_ID_stat_report_LEN, MAVLINK_MSG_ID_stat_report_CRC);
#endif
}

#if MAVLINK_MSG_ID_stat_report_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_stat_report_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const uint8_t *addr, uint8_t sys_stat, uint8_t node_cnt, const float *position)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 18, sys_stat);
    _mav_put_uint8_t(buf, 19, node_cnt);
    _mav_put_float_array(buf, 0, position, 3);
    _mav_put_uint8_t_array(buf, 12, addr, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_stat_report, buf, MAVLINK_MSG_ID_stat_report_MIN_LEN, MAVLINK_MSG_ID_stat_report_LEN, MAVLINK_MSG_ID_stat_report_CRC);
#else
    mavlink_stat_report_t *packet = (mavlink_stat_report_t *)msgbuf;
    packet->sys_stat = sys_stat;
    packet->node_cnt = node_cnt;
    mav_array_memcpy(packet->position, position, sizeof(float)*3);
    mav_array_memcpy(packet->addr, addr, sizeof(uint8_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_stat_report, (const char *)packet, MAVLINK_MSG_ID_stat_report_MIN_LEN, MAVLINK_MSG_ID_stat_report_LEN, MAVLINK_MSG_ID_stat_report_CRC);
#endif
}
#endif

#endif

// MESSAGE stat_report UNPACKING


/**
 * @brief Get field addr from stat_report message
 *
 * @return  mac address of drone
 */
static inline uint16_t mavlink_msg_stat_report_get_addr(const mavlink_message_t* msg, uint8_t *addr)
{
    return _MAV_RETURN_uint8_t_array(msg, addr, 6,  12);
}

/**
 * @brief Get field sys_stat from stat_report message
 *
 * @return   status of system
 */
static inline uint8_t mavlink_msg_stat_report_get_sys_stat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  18);
}

/**
 * @brief Get field node_cnt from stat_report message
 *
 * @return   number of active ble nodes
 */
static inline uint8_t mavlink_msg_stat_report_get_node_cnt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  19);
}

/**
 * @brief Get field position from stat_report message
 *
 * @return   current position, estimated
 */
static inline uint16_t mavlink_msg_stat_report_get_position(const mavlink_message_t* msg, float *position)
{
    return _MAV_RETURN_float_array(msg, position, 3,  0);
}

/**
 * @brief Decode a stat_report message into a struct
 *
 * @param msg The message to decode
 * @param stat_report C-struct to decode the message contents into
 */
static inline void mavlink_msg_stat_report_decode(const mavlink_message_t* msg, mavlink_stat_report_t* stat_report)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_stat_report_get_position(msg, stat_report->position);
    mavlink_msg_stat_report_get_addr(msg, stat_report->addr);
    stat_report->sys_stat = mavlink_msg_stat_report_get_sys_stat(msg);
    stat_report->node_cnt = mavlink_msg_stat_report_get_node_cnt(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_stat_report_LEN? msg->len : MAVLINK_MSG_ID_stat_report_LEN;
        memset(stat_report, 0, MAVLINK_MSG_ID_stat_report_LEN);
    memcpy(stat_report, _MAV_PAYLOAD(msg), len);
#endif
}
