#pragma once
// MESSAGE command PACKING

#define MAVLINK_MSG_ID_command 5

MAVPACKED(
typedef struct __mavlink_command_t {
 uint8_t addr[6]; /*<  mac address of drone*/
 uint8_t sys_stat; /*<   status of system*/
 uint8_t command; /*<   command from server*/
}) mavlink_command_t;

#define MAVLINK_MSG_ID_command_LEN 8
#define MAVLINK_MSG_ID_command_MIN_LEN 8
#define MAVLINK_MSG_ID_5_LEN 8
#define MAVLINK_MSG_ID_5_MIN_LEN 8

#define MAVLINK_MSG_ID_command_CRC 192
#define MAVLINK_MSG_ID_5_CRC 192

#define MAVLINK_MSG_command_FIELD_ADDR_LEN 6

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_command { \
    5, \
    "command", \
    3, \
    {  { "addr", NULL, MAVLINK_TYPE_UINT8_T, 6, 0, offsetof(mavlink_command_t, addr) }, \
         { "sys_stat", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_command_t, sys_stat) }, \
         { "command", NULL, MAVLINK_TYPE_UINT8_T, 0, 7, offsetof(mavlink_command_t, command) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_command { \
    "command", \
    3, \
    {  { "addr", NULL, MAVLINK_TYPE_UINT8_T, 6, 0, offsetof(mavlink_command_t, addr) }, \
         { "sys_stat", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_command_t, sys_stat) }, \
         { "command", NULL, MAVLINK_TYPE_UINT8_T, 0, 7, offsetof(mavlink_command_t, command) }, \
         } \
}
#endif

/**
 * @brief Pack a command message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param addr  mac address of drone
 * @param sys_stat   status of system
 * @param command   command from server
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_command_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const uint8_t *addr, uint8_t sys_stat, uint8_t command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_command_LEN];
    _mav_put_uint8_t(buf, 6, sys_stat);
    _mav_put_uint8_t(buf, 7, command);
    _mav_put_uint8_t_array(buf, 0, addr, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_command_LEN);
#else
    mavlink_command_t packet;
    packet.sys_stat = sys_stat;
    packet.command = command;
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_command_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_command;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_command_MIN_LEN, MAVLINK_MSG_ID_command_LEN, MAVLINK_MSG_ID_command_CRC);
}

/**
 * @brief Pack a command message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param addr  mac address of drone
 * @param sys_stat   status of system
 * @param command   command from server
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_command_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const uint8_t *addr,uint8_t sys_stat,uint8_t command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_command_LEN];
    _mav_put_uint8_t(buf, 6, sys_stat);
    _mav_put_uint8_t(buf, 7, command);
    _mav_put_uint8_t_array(buf, 0, addr, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_command_LEN);
#else
    mavlink_command_t packet;
    packet.sys_stat = sys_stat;
    packet.command = command;
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_command_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_command;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_command_MIN_LEN, MAVLINK_MSG_ID_command_LEN, MAVLINK_MSG_ID_command_CRC);
}

/**
 * @brief Encode a command struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param command C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_command_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_command_t* command)
{
    return mavlink_msg_command_pack(system_id, component_id, msg, command->addr, command->sys_stat, command->command);
}

/**
 * @brief Encode a command struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param command C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_command_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_command_t* command)
{
    return mavlink_msg_command_pack_chan(system_id, component_id, chan, msg, command->addr, command->sys_stat, command->command);
}

/**
 * @brief Send a command message
 * @param chan MAVLink channel to send the message
 *
 * @param addr  mac address of drone
 * @param sys_stat   status of system
 * @param command   command from server
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_command_send(mavlink_channel_t chan, const uint8_t *addr, uint8_t sys_stat, uint8_t command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_command_LEN];
    _mav_put_uint8_t(buf, 6, sys_stat);
    _mav_put_uint8_t(buf, 7, command);
    _mav_put_uint8_t_array(buf, 0, addr, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_command, buf, MAVLINK_MSG_ID_command_MIN_LEN, MAVLINK_MSG_ID_command_LEN, MAVLINK_MSG_ID_command_CRC);
#else
    mavlink_command_t packet;
    packet.sys_stat = sys_stat;
    packet.command = command;
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_command, (const char *)&packet, MAVLINK_MSG_ID_command_MIN_LEN, MAVLINK_MSG_ID_command_LEN, MAVLINK_MSG_ID_command_CRC);
#endif
}

/**
 * @brief Send a command message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_command_send_struct(mavlink_channel_t chan, const mavlink_command_t* command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_command_send(chan, command->addr, command->sys_stat, command->command);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_command, (const char *)command, MAVLINK_MSG_ID_command_MIN_LEN, MAVLINK_MSG_ID_command_LEN, MAVLINK_MSG_ID_command_CRC);
#endif
}

#if MAVLINK_MSG_ID_command_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_command_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const uint8_t *addr, uint8_t sys_stat, uint8_t command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 6, sys_stat);
    _mav_put_uint8_t(buf, 7, command);
    _mav_put_uint8_t_array(buf, 0, addr, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_command, buf, MAVLINK_MSG_ID_command_MIN_LEN, MAVLINK_MSG_ID_command_LEN, MAVLINK_MSG_ID_command_CRC);
#else
    mavlink_command_t *packet = (mavlink_command_t *)msgbuf;
    packet->sys_stat = sys_stat;
    packet->command = command;
    mav_array_memcpy(packet->addr, addr, sizeof(uint8_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_command, (const char *)packet, MAVLINK_MSG_ID_command_MIN_LEN, MAVLINK_MSG_ID_command_LEN, MAVLINK_MSG_ID_command_CRC);
#endif
}
#endif

#endif

// MESSAGE command UNPACKING


/**
 * @brief Get field addr from command message
 *
 * @return  mac address of drone
 */
static inline uint16_t mavlink_msg_command_get_addr(const mavlink_message_t* msg, uint8_t *addr)
{
    return _MAV_RETURN_uint8_t_array(msg, addr, 6,  0);
}

/**
 * @brief Get field sys_stat from command message
 *
 * @return   status of system
 */
static inline uint8_t mavlink_msg_command_get_sys_stat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  6);
}

/**
 * @brief Get field command from command message
 *
 * @return   command from server
 */
static inline uint8_t mavlink_msg_command_get_command(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  7);
}

/**
 * @brief Decode a command message into a struct
 *
 * @param msg The message to decode
 * @param command C-struct to decode the message contents into
 */
static inline void mavlink_msg_command_decode(const mavlink_message_t* msg, mavlink_command_t* command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_command_get_addr(msg, command->addr);
    command->sys_stat = mavlink_msg_command_get_sys_stat(msg);
    command->command = mavlink_msg_command_get_command(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_command_LEN? msg->len : MAVLINK_MSG_ID_command_LEN;
        memset(command, 0, MAVLINK_MSG_ID_command_LEN);
    memcpy(command, _MAV_PAYLOAD(msg), len);
#endif
}
