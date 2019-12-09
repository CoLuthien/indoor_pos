/** @file
 *    @brief MAVLink comm protocol testsuite generated from test.xml
 *    @see http://qgroundcontrol.org/mavlink/
 */
#pragma once
#ifndef TEST_TESTSUITE_H
#define TEST_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL

static void mavlink_test_test(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{

    mavlink_test_test(system_id, component_id, last_msg);
}
#endif




static void mavlink_test_heartbeat(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_heartbeat >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_heartbeat_t packet_in = {
        { 5, 6, 7, 8, 9, 10 },151,218
    };
    mavlink_heartbeat_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.sys_stat = packet_in.sys_stat;
        packet1.err_code = packet_in.err_code;
        
        mav_array_memcpy(packet1.addr, packet_in.addr, sizeof(uint8_t)*6);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_heartbeat_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_heartbeat_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_heartbeat_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_heartbeat_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_heartbeat_pack(system_id, component_id, &msg , packet1.addr , packet1.sys_stat , packet1.err_code );
    mavlink_msg_heartbeat_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_heartbeat_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.addr , packet1.sys_stat , packet1.err_code );
    mavlink_msg_heartbeat_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_heartbeat_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_heartbeat_send(MAVLINK_COMM_1 , packet1.addr , packet1.sys_stat , packet1.err_code );
    mavlink_msg_heartbeat_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_stat_report(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_stat_report >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_stat_report_t packet_in = {
        { 17.0, 18.0, 19.0 },{ 41, 42, 43, 44, 45, 46 },187,254
    };
    mavlink_stat_report_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.sys_stat = packet_in.sys_stat;
        packet1.node_cnt = packet_in.node_cnt;
        
        mav_array_memcpy(packet1.position, packet_in.position, sizeof(float)*3);
        mav_array_memcpy(packet1.addr, packet_in.addr, sizeof(uint8_t)*6);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_stat_report_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_stat_report_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_stat_report_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_stat_report_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_stat_report_pack(system_id, component_id, &msg , packet1.addr , packet1.sys_stat , packet1.node_cnt , packet1.position );
    mavlink_msg_stat_report_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_stat_report_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.addr , packet1.sys_stat , packet1.node_cnt , packet1.position );
    mavlink_msg_stat_report_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_stat_report_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_stat_report_send(MAVLINK_COMM_1 , packet1.addr , packet1.sys_stat , packet1.node_cnt , packet1.position );
    mavlink_msg_stat_report_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_query(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_query >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_query_t packet_in = {
        { 5, 6, 7, 8, 9, 10 },151,{ 218, 219, 220, 221, 222, 223 }
    };
    mavlink_query_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.node_cnt = packet_in.node_cnt;
        
        mav_array_memcpy(packet1.addr, packet_in.addr, sizeof(uint8_t)*6);
        mav_array_memcpy(packet1.found_addrs, packet_in.found_addrs, sizeof(uint8_t)*6);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_query_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_query_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_query_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_query_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_query_pack(system_id, component_id, &msg , packet1.addr , packet1.node_cnt , packet1.found_addrs );
    mavlink_msg_query_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_query_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.addr , packet1.node_cnt , packet1.found_addrs );
    mavlink_msg_query_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_query_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_query_send(MAVLINK_COMM_1 , packet1.addr , packet1.node_cnt , packet1.found_addrs );
    mavlink_msg_query_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_query_result(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_query_result >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_query_result_t packet_in = {
        17.0,45.0,73.0,{ 41, 42, 43, 44, 45, 46 },{ 187, 188, 189, 190, 191, 192 },77
    };
    mavlink_query_result_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.x = packet_in.x;
        packet1.y = packet_in.y;
        packet1.z = packet_in.z;
        packet1.is_usable = packet_in.is_usable;
        
        mav_array_memcpy(packet1.addr, packet_in.addr, sizeof(uint8_t)*6);
        mav_array_memcpy(packet1.match_addr, packet_in.match_addr, sizeof(uint8_t)*6);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_query_result_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_query_result_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_query_result_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_query_result_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_query_result_pack(system_id, component_id, &msg , packet1.addr , packet1.match_addr , packet1.is_usable , packet1.x , packet1.y , packet1.z );
    mavlink_msg_query_result_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_query_result_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.addr , packet1.match_addr , packet1.is_usable , packet1.x , packet1.y , packet1.z );
    mavlink_msg_query_result_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_query_result_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_query_result_send(MAVLINK_COMM_1 , packet1.addr , packet1.match_addr , packet1.is_usable , packet1.x , packet1.y , packet1.z );
    mavlink_msg_query_result_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_command(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_command >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_command_t packet_in = {
        { 5, 6, 7, 8, 9, 10 },151,218
    };
    mavlink_command_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.sys_stat = packet_in.sys_stat;
        packet1.command = packet_in.command;
        
        mav_array_memcpy(packet1.addr, packet_in.addr, sizeof(uint8_t)*6);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_command_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_command_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_command_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_command_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_command_pack(system_id, component_id, &msg , packet1.addr , packet1.sys_stat , packet1.command );
    mavlink_msg_command_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_command_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.addr , packet1.sys_stat , packet1.command );
    mavlink_msg_command_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_command_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_command_send(MAVLINK_COMM_1 , packet1.addr , packet1.sys_stat , packet1.command );
    mavlink_msg_command_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_node_report(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_node_report >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_node_report_t packet_in = {
        { 5, 6, 7, 8, 9, 10 },151,218,{ 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124 },{ 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76 }
    };
    mavlink_node_report_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.report_cnt = packet_in.report_cnt;
        packet1.node_status = packet_in.node_status;
        
        mav_array_memcpy(packet1.source_addr, packet_in.source_addr, sizeof(uint8_t)*6);
        mav_array_memcpy(packet1.node_addr, packet_in.node_addr, sizeof(uint8_t)*96);
        mav_array_memcpy(packet1.rssi, packet_in.rssi, sizeof(int8_t)*16);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_node_report_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_node_report_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_node_report_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_node_report_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_node_report_pack(system_id, component_id, &msg , packet1.source_addr , packet1.report_cnt , packet1.node_status , packet1.node_addr , packet1.rssi );
    mavlink_msg_node_report_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_node_report_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.source_addr , packet1.report_cnt , packet1.node_status , packet1.node_addr , packet1.rssi );
    mavlink_msg_node_report_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_node_report_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_node_report_send(MAVLINK_COMM_1 , packet1.source_addr , packet1.report_cnt , packet1.node_status , packet1.node_addr , packet1.rssi );
    mavlink_msg_node_report_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_test(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_heartbeat(system_id, component_id, last_msg);
    mavlink_test_stat_report(system_id, component_id, last_msg);
    mavlink_test_query(system_id, component_id, last_msg);
    mavlink_test_query_result(system_id, component_id, last_msg);
    mavlink_test_command(system_id, component_id, last_msg);
    mavlink_test_node_report(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // TEST_TESTSUITE_H
