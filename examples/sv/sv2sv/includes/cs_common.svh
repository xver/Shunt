/**
 * File: cs_common.svh
 *
 * Common macro definitions for client-server communication
 *
 * This file contains common definitions used by both the initiator and target
 * modules in the TCP/IP SystemVerilog SHUNT communication examples.
 */

/**
 * Constant: MY_HOST
 * Default hostname for socket connections (localhost)
 */
`define MY_HOST "localhost"

/**
 * Constant: MY_PORT
 * Default port number for socket connections (3450)
 */
`define MY_PORT  3450

/**
 * Constant: V_SIZE
 * Default vector size for data arrays (5 elements)
 */
`define V_SIZE   5

/**
 * Constant: STRING_MESSAGE
 * Test string for string data type loopback tests
 */
`define STRING_MESSAGE  "server function int string_loopback_test(int socket_id)\0"

/**
 * Constant: STRING_MESSAGE1
 * Alternative test string for string data type loopback tests
 */
`define STRING_MESSAGE1 "0000000000000000000000000000000000000000000000000000000\0"
