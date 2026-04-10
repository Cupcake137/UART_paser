# UART Parser System

A small C project for learning how to parse UART-like byte streams using a circular buffer, frame detection, CRC validation, and stream resynchronization.

## Features

- Circular buffer implementation
- Frame parsing from byte stream
- Protocol format: `[HEADER][LEN][DATA...][CRC]`
- CRC validation
- Error handling with parser status codes
- Resynchronization when invalid bytes are found
- Stream input from text file
- Console output and log file output

## Frame Format

Each frame follows this format:
[HEADER][LEN][DATA...][CRC]

## Example

AA 03 10 20 30 00
AA : frame header
03 : payload length
10 20 30 : payload bytes
00 : CRC = XOR of payload bytes

## Project Structure

UART_paser/
├── inc/
│   ├── buffer.h
│   ├── byte_processing.h
│   ├── file_handle.h
│   └── logger.h
├── src/
│   ├── buffer.c
│   ├── byte_processing.c
│   ├── file_handle.c
│   ├── logger.c
│   └── main.c
├── test/
│   ├── stream_test.txt
│   └── parser.log
├── Makefile
└── README.md

## Project process

Build
make
Run
./uart_parser
Input Test File

The parser reads test stream data from:

./test/stream_test.txt

## Example test stream may include:

valid frames
noise bytes before header
CRC error case
invalid length case
multiple frames in one stream
Output
Terminal output

The terminal prints parser activity, for example:

Frame OK: H = AA LEN = 3 10 20 30 CRC = 00
[RESYNC] Dropped invalid byte
[ERROR] CRC mismatch
[ERROR] Invalid length
Log file output

Detailed logs are also written to:

./test/parser.log
Parser Status Design

The parser returns different status values to separate normal waiting from actual parsing errors:

PARSER_OK
PARSER_WAIT
PARSER_RESYNC
PARSER_CRC_ERROR
PARSER_LEN_ERROR
PARSER_BUFFER_ERROR
PARSER_ARG_ERROR

This makes debugging easier and avoids treating all failures as the same error.

## What I learned

This project helped me practice:

pointer-based buffer handling
circular buffer design
frame detection in continuous stream
CRC checking
resynchronization strategy
separating parser core from logging/output
building a small embedded-style C project structure
Future Improvements
read input from real UART device on Raspberry Pi
add frame statistics
support command handler layer
generate response frames
improve recovery strategy for malformed frames