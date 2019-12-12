#pragma once
// MESSAGE request PACKING

#define MAVLINK_MSG_ID_request 7

MAVPACKED(
typedef struct __mavlink_request_t {
 int64_t req_sec; /*<   time of request */
 int64_t req_nsec; /*<   time of request nsec */
 uint8_t addr[6]; /*<   mac addr of drone */
 uint8_t requset; /*<   request number */
}) mavlink_request_t;

#define MAVLINK_MSG_ID_request_LEN 23
#define MAVLINK_MSG_ID_request_MIN_LEN 23
#define MAVLINK_MSG_ID_7_LEN 23
#define MAVLINK_MSG_ID_7_MIN_LEN 23

#define MAVLINK_MSG_ID_request_CRC 146
#define MAVLINK_MSG_ID_7_CRC 146

#define MAVLINK_MSG_request_FIELD_ADDR_LEN 6

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_request { \
    7, \
    "request", \
    4, \
    {  { "addr", NULL, MAVLINK_TYPE_UINT8_T, 6, 16, offsetof(mavlink_request_t, addr) }, \
         { "requset", NULL, MAVLINK_TYPE_UINT8_T, 0, 22, offsetof(mavlink_request_t, requset) }, \
         { "req_sec", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_request_t, req_sec) }, \
         { "req_nsec", NULL, MAVLINK_TYPE_INT64_T, 0, 8, offsetof(mavlink_request_t, req_nsec) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_request { \
    "request", \
    4, \
    {  { "addr", NULL, MAVLINK_TYPE_UINT8_T, 6, 16, offsetof(mavlink_request_t, addr) }, \
         { "requset", NULL, MAVLINK_TYPE_UINT8_T, 0, 22, offsetof(mavlink_request_t, requset) }, \
         { "req_sec", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_request_t, req_sec) }, \
         { "req_nsec", NULL, MAVLINK_TYPE_INT64_T, 0, 8, offsetof(mavlink_request_t, req_nsec) }, \
         } \
}
#endif

/**
 * @brief Pack a request message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param addr   mac addr of drone 
 * @param requset   request number 
 * @param req_sec   time of request 
 * @param req_nsec   time of request nsec 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_request_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const uint8_t *addr, uint8_t requset, int64_t req_sec, int64_t req_nsec)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_request_LEN];
    _mav_put_int64_t(buf, 0, req_sec);
    _mav_put_int64_t(buf, 8, req_nsec);
    _mav_put_uint8_t(buf, 22, requset);
    _mav_put_uint8_t_array(buf, 16, addr, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_request_LEN);
#else
    mavlink_request_t packet;
    packet.req_sec = req_sec;
    packet.req_nsec = req_nsec;
    packet.requset = requset;
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_request_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_request;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_request_MIN_LEN, MAVLINK_MSG_ID_request_LEN, MAVLINK_MSG_ID_request_CRC);
}

/**
 * @brief Pack a request message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param addr   mac addr of drone 
 * @param requset   request number 
 * @param req_sec   time of request 
 * @param req_nsec   time of request nsec 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_request_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const uint8_t *addr,uint8_t requset,int64_t req_sec,int64_t req_nsec)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_request_LEN];
    _mav_put_int64_t(buf, 0, req_sec);
    _mav_put_int64_t(buf, 8, req_nsec);
    _mav_put_uint8_t(buf, 22, requset);
    _mav_put_uint8_t_array(buf, 16, addr, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_request_LEN);
#else
    mavlink_request_t packet;
    packet.req_sec = req_sec;
    packet.req_nsec = req_nsec;
    packet.requset = requset;
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_request_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_request;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_request_MIN_LEN, MAVLINK_MSG_ID_request_LEN, MAVLINK_MSG_ID_request_CRC);
}

/**
 * @brief Encode a request struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param request C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_request_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_request_t* request)
{
    return mavlink_msg_request_pack(system_id, component_id, msg, request->addr, request->requset, request->req_sec, request->req_nsec);
}

/**
 * @brief Encode a request struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param request C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_request_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_request_t* request)
{
    return mavlink_msg_request_pack_chan(system_id, component_id, chan, msg, request->addr, request->requset, request->req_sec, request->req_nsec);
}

/**
 * @brief Send a request message
 * @param chan MAVLink channel to send the message
 *
 * @param addr   mac addr of drone 
 * @param requset   request number 
 * @param req_sec   time of request 
 * @param req_nsec   time of request nsec 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_request_send(mavlink_channel_t chan, const uint8_t *addr, uint8_t requset, int64_t req_sec, int64_t req_nsec)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_request_LEN];
    _mav_put_int64_t(buf, 0, req_sec);
    _mav_put_int64_t(buf, 8, req_nsec);
    _mav_put_uint8_t(buf, 22, requset);
    _mav_put_uint8_t_array(buf, 16, addr, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_request, buf, MAVLINK_MSG_ID_request_MIN_LEN, MAVLINK_MSG_ID_request_LEN, MAVLINK_MSG_ID_request_CRC);
#else
    mavlink_request_t packet;
    packet.req_sec = req_sec;
    packet.req_nsec = req_nsec;
    packet.requset = requset;
    mav_array_memcpy(packet.addr, addr, sizeof(uint8_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_request, (const char *)&packet, MAVLINK_MSG_ID_request_MIN_LEN, MAVLINK_MSG_ID_request_LEN, MAVLINK_MSG_ID_request_CRC);
#endif
}

/**
 * @brief Send a request message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_request_send_struct(mavlink_channel_t chan, const mavlink_request_t* request)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_request_send(chan, request->addr, request->requset, request->req_sec, request->req_nsec);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_request, (const char *)request, MAVLINK_MSG_ID_request_MIN_LEN, MAVLINK_MSG_ID_request_LEN, MAVLINK_MSG_ID_request_CRC);
#endif
}

#if MAVLINK_MSG_ID_request_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_request_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const uint8_t *addr, uint8_t requset, int64_t req_sec, int64_t req_nsec)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int64_t(buf, 0, req_sec);
    _mav_put_int64_t(buf, 8, req_nsec);
    _mav_put_uint8_t(buf, 22, requset);
    _mav_put_uint8_t_array(buf, 16, addr, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_request, buf, MAVLINK_MSG_ID_request_MIN_LEN, MAVLINK_MSG_ID_request_LEN, MAVLINK_MSG_ID_request_CRC);
#else
    mavlink_request_t *packet = (mavlink_request_t *)msgbuf;
    packet->req_sec = req_sec;
    packet->req_nsec = req_nsec;
    packet->requset = requset;
    mav_array_memcpy(packet->addr, addr, sizeof(uint8_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_request, (const char *)packet, MAVLINK_MSG_ID_request_MIN_LEN, MAVLINK_MSG_ID_request_LEN, MAVLINK_MSG_ID_request_CRC);
#endif
}
#endif

#endif

// MESSAGE request UNPACKING


/**
 * @brief Get field addr from request message
 *
 * @return   mac addr of drone 
 */
static inline uint16_t mavlink_msg_request_get_addr(const mavlink_message_t* msg, uint8_t *addr)
{
    return _MAV_RETURN_uint8_t_array(msg, addr, 6,  16);
}

/**
 * @brief Get field requset from request message
 *
 * @return   request number 
 */
static inline uint8_t mavlink_msg_request_get_requset(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  22);
}

/**
 * @brief Get field req_sec from request message
 *
 * @return   time of request 
 */
static inline int64_t mavlink_msg_request_get_req_sec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  0);
}

/**
 * @brief Get field req_nsec from request message
 *
 * @return   time of request nsec 
 */
static inline int64_t mavlink_msg_request_get_req_nsec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  8);
}

/**
 * @brief Decode a request message into a struct
 *
 * @param msg The message to decode
 * @param request C-struct to decode the message contents into
 */
static inline void mavlink_msg_request_decode(const mavlink_message_t* msg, mavlink_request_t* request)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    request->req_sec = mavlink_msg_request_get_req_sec(msg);
    request->req_nsec = mavlink_msg_request_get_req_nsec(msg);
    mavlink_msg_request_get_addr(msg, request->addr);
    request->requset = mavlink_msg_request_get_requset(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_request_LEN? msg->len : MAVLINK_MSG_ID_request_LEN;
        memset(request, 0, MAVLINK_MSG_ID_request_LEN);
    memcpy(request, _MAV_PAYLOAD(msg), len);
#endif
}
