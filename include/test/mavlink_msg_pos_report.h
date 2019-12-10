#pragma once
// MESSAGE pos_report PACKING

#define MAVLINK_MSG_ID_pos_report 1

MAVPACKED(
typedef struct __mavlink_pos_report_t {
 int64_t est_sec; /*<   time of last estimation of positon */
 int64_t est_nsec; /*<   time of last estimation of positon in nsec */
 float position[3]; /*<   current position, estimated*/
 uint8_t addr[6]; /*<  mac address of drone*/
 uint8_t pos_mode; /*<   positioning mode*/
}) mavlink_pos_report_t;

#define MAVLINK_MSG_ID_pos_report_LEN 35
#define MAVLINK_MSG_ID_pos_report_MIN_LEN 35
#define MAVLINK_MSG_ID_1_LEN 35
#define MAVLINK_MSG_ID_1_MIN_LEN 35

#define MAVLINK_MSG_ID_pos_report_CRC 160
#define MAVLINK_MSG_ID_1_CRC 160

#define MAVLINK_MSG_pos_report_FIELD_POSITION_LEN 3
#define MAVLINK_MSG_pos_report_FIELD_ADDR_LEN 6

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_pos_report { \
    1, \
    "pos_report", \
    5, \
    {  { "addr", NULL, MAVLINK_TYPE_UINT8_T, 6, 28, offsetof(mavlink_pos_report_t, addr) }, \
         { "pos_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 34, offsetof(mavlink_pos_report_t, pos_mode) }, \
         { "est_sec", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_pos_report_t, est_sec) }, \
         { "est_nsec", NULL, MAVLINK_TYPE_INT64_T, 0, 8, offsetof(mavlink_pos_report_t, est_nsec) }, \
         { "position", NULL, MAVLINK_TYPE_FLOAT, 3, 16, offsetof(mavlink_pos_report_t, position) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_pos_report { \
    "pos_report", \
    5, \
    {  { "addr", NULL, MAVLINK_TYPE_UINT8_T, 6, 28, offsetof(mavlink_pos_report_t, addr) }, \
         { "pos_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 34, offsetof(mavlink_pos_report_t, pos_mode) }, \
         { "est_sec", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_pos_report_t, est_sec) }, \
         { "est_nsec", NULL, MAVLINK_TYPE_INT64_T, 0, 8, offsetof(mavlink_pos_report_t, est_nsec) }, \
         { "position", NULL, MAVLINK_TYPE_FLOAT, 3, 16, offsetof(mavlink_pos_report_t, position) }, \
         } \
}
#endif

/**
 * @brief Pack a pos_report message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param addr  mac address of drone
 * @param pos_mode   positioning mode
 * @param est_sec   time of last estimation of positon 
 * @param est_nsec   time of last estimation of positon in nsec 
 * @param position   current position, estimated
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_pos_report_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const uint8_t *addr, uint8_t pos_mode, int64_t est_sec, int64_t est_nsec, const float *position)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_pos_report_LEN];
    _mav_put_int64_t(buf, 0, est_sec);
    _mav_put_int64_t(buf, 8, est_nsec);
    _mav_put_uint8_t(buf, 34, pos_mode);
    _mav_put_float_array(buf, 16, position, 3);
    _mav_put_uint8_t_array(buf, 28, addr, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_pos_report_LEN);
#else
    mavlink_pos_report_t packet;
    packet.est_sec = est_sec;
    packet.est_nsec = est_nsec;
    packet.pos_mode = pos_mode;
    mav_array_memcpy(packet.position, position, sizeof(float)*3);
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_pos_report_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_pos_report;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_pos_report_MIN_LEN, MAVLINK_MSG_ID_pos_report_LEN, MAVLINK_MSG_ID_pos_report_CRC);
}

/**
 * @brief Pack a pos_report message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param addr  mac address of drone
 * @param pos_mode   positioning mode
 * @param est_sec   time of last estimation of positon 
 * @param est_nsec   time of last estimation of positon in nsec 
 * @param position   current position, estimated
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_pos_report_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const uint8_t *addr,uint8_t pos_mode,int64_t est_sec,int64_t est_nsec,const float *position)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_pos_report_LEN];
    _mav_put_int64_t(buf, 0, est_sec);
    _mav_put_int64_t(buf, 8, est_nsec);
    _mav_put_uint8_t(buf, 34, pos_mode);
    _mav_put_float_array(buf, 16, position, 3);
    _mav_put_uint8_t_array(buf, 28, addr, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_pos_report_LEN);
#else
    mavlink_pos_report_t packet;
    packet.est_sec = est_sec;
    packet.est_nsec = est_nsec;
    packet.pos_mode = pos_mode;
    mav_array_memcpy(packet.position, position, sizeof(float)*3);
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_pos_report_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_pos_report;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_pos_report_MIN_LEN, MAVLINK_MSG_ID_pos_report_LEN, MAVLINK_MSG_ID_pos_report_CRC);
}

/**
 * @brief Encode a pos_report struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param pos_report C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_pos_report_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_pos_report_t* pos_report)
{
    return mavlink_msg_pos_report_pack(system_id, component_id, msg, pos_report->addr, pos_report->pos_mode, pos_report->est_sec, pos_report->est_nsec, pos_report->position);
}

/**
 * @brief Encode a pos_report struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param pos_report C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_pos_report_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_pos_report_t* pos_report)
{
    return mavlink_msg_pos_report_pack_chan(system_id, component_id, chan, msg, pos_report->addr, pos_report->pos_mode, pos_report->est_sec, pos_report->est_nsec, pos_report->position);
}

/**
 * @brief Send a pos_report message
 * @param chan MAVLink channel to send the message
 *
 * @param addr  mac address of drone
 * @param pos_mode   positioning mode
 * @param est_sec   time of last estimation of positon 
 * @param est_nsec   time of last estimation of positon in nsec 
 * @param position   current position, estimated
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_pos_report_send(mavlink_channel_t chan, const uint8_t *addr, uint8_t pos_mode, int64_t est_sec, int64_t est_nsec, const float *position)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_pos_report_LEN];
    _mav_put_int64_t(buf, 0, est_sec);
    _mav_put_int64_t(buf, 8, est_nsec);
    _mav_put_uint8_t(buf, 34, pos_mode);
    _mav_put_float_array(buf, 16, position, 3);
    _mav_put_uint8_t_array(buf, 28, addr, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_pos_report, buf, MAVLINK_MSG_ID_pos_report_MIN_LEN, MAVLINK_MSG_ID_pos_report_LEN, MAVLINK_MSG_ID_pos_report_CRC);
#else
    mavlink_pos_report_t packet;
    packet.est_sec = est_sec;
    packet.est_nsec = est_nsec;
    packet.pos_mode = pos_mode;
    mav_array_memcpy(packet.position, position, sizeof(float)*3);
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_pos_report, (const char *)&packet, MAVLINK_MSG_ID_pos_report_MIN_LEN, MAVLINK_MSG_ID_pos_report_LEN, MAVLINK_MSG_ID_pos_report_CRC);
#endif
}

/**
 * @brief Send a pos_report message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_pos_report_send_struct(mavlink_channel_t chan, const mavlink_pos_report_t* pos_report)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_pos_report_send(chan, pos_report->addr, pos_report->pos_mode, pos_report->est_sec, pos_report->est_nsec, pos_report->position);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_pos_report, (const char *)pos_report, MAVLINK_MSG_ID_pos_report_MIN_LEN, MAVLINK_MSG_ID_pos_report_LEN, MAVLINK_MSG_ID_pos_report_CRC);
#endif
}

#if MAVLINK_MSG_ID_pos_report_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_pos_report_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const uint8_t *addr, uint8_t pos_mode, int64_t est_sec, int64_t est_nsec, const float *position)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int64_t(buf, 0, est_sec);
    _mav_put_int64_t(buf, 8, est_nsec);
    _mav_put_uint8_t(buf, 34, pos_mode);
    _mav_put_float_array(buf, 16, position, 3);
    _mav_put_uint8_t_array(buf, 28, addr, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_pos_report, buf, MAVLINK_MSG_ID_pos_report_MIN_LEN, MAVLINK_MSG_ID_pos_report_LEN, MAVLINK_MSG_ID_pos_report_CRC);
#else
    mavlink_pos_report_t *packet = (mavlink_pos_report_t *)msgbuf;
    packet->est_sec = est_sec;
    packet->est_nsec = est_nsec;
    packet->pos_mode = pos_mode;
    mav_array_memcpy(packet->position, position, sizeof(float)*3);
    mav_array_memcpy(packet->addr, addr, sizeof(uint8_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_pos_report, (const char *)packet, MAVLINK_MSG_ID_pos_report_MIN_LEN, MAVLINK_MSG_ID_pos_report_LEN, MAVLINK_MSG_ID_pos_report_CRC);
#endif
}
#endif

#endif

// MESSAGE pos_report UNPACKING


/**
 * @brief Get field addr from pos_report message
 *
 * @return  mac address of drone
 */
static inline uint16_t mavlink_msg_pos_report_get_addr(const mavlink_message_t* msg, uint8_t *addr)
{
    return _MAV_RETURN_uint8_t_array(msg, addr, 6,  28);
}

/**
 * @brief Get field pos_mode from pos_report message
 *
 * @return   positioning mode
 */
static inline uint8_t mavlink_msg_pos_report_get_pos_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  34);
}

/**
 * @brief Get field est_sec from pos_report message
 *
 * @return   time of last estimation of positon 
 */
static inline int64_t mavlink_msg_pos_report_get_est_sec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  0);
}

/**
 * @brief Get field est_nsec from pos_report message
 *
 * @return   time of last estimation of positon in nsec 
 */
static inline int64_t mavlink_msg_pos_report_get_est_nsec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  8);
}

/**
 * @brief Get field position from pos_report message
 *
 * @return   current position, estimated
 */
static inline uint16_t mavlink_msg_pos_report_get_position(const mavlink_message_t* msg, float *position)
{
    return _MAV_RETURN_float_array(msg, position, 3,  16);
}

/**
 * @brief Decode a pos_report message into a struct
 *
 * @param msg The message to decode
 * @param pos_report C-struct to decode the message contents into
 */
static inline void mavlink_msg_pos_report_decode(const mavlink_message_t* msg, mavlink_pos_report_t* pos_report)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    pos_report->est_sec = mavlink_msg_pos_report_get_est_sec(msg);
    pos_report->est_nsec = mavlink_msg_pos_report_get_est_nsec(msg);
    mavlink_msg_pos_report_get_position(msg, pos_report->position);
    mavlink_msg_pos_report_get_addr(msg, pos_report->addr);
    pos_report->pos_mode = mavlink_msg_pos_report_get_pos_mode(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_pos_report_LEN? msg->len : MAVLINK_MSG_ID_pos_report_LEN;
        memset(pos_report, 0, MAVLINK_MSG_ID_pos_report_LEN);
    memcpy(pos_report, _MAV_PAYLOAD(msg), len);
#endif
}
