UART PARSER SYSTEM:
                +-------------------+
                |   Input Source    |
                |-------------------|
                | file / stdin      |
                | serial / stream   |
                +---------+---------+
                          |
                          v
                +-------------------+
                |   Read 1 Byte      |
                |-------------------|
                | byte = get_next() |
                +---------+---------+
                          |
                          v
                +-------------------+
                | process_byte()    |
                |-------------------|
                | push byte vào CB  |
                +---------+---------+
                          |
                          v
                +-------------------+
                | Circular Buffer   |
                |-------------------|
                | lưu byte tạm thời |
                | theo FIFO         |
                +---------+---------+
                          |
                          v
                +-------------------------+
                | try_parse_frame()       |
                |-------------------------|
                | 1. tìm HEADER           |
                | 2. đọc LEN              |
                | 3. check đủ byte chưa   |
                | 4. check CRC            |
                | 5. valid -> tạo Frame   |
                | 6. invalid -> resync    |
                +-----+-----------+-------+
                      |           |
          invalid / partial       | valid frame
                      |           v
                      |   +-------------------+
                      |   |   Frame Object    |
                      |   |-------------------|
                      |   | header            |
                      |   | len               |
                      |   | data[]            |
                      |   | crc               |
                      |   +---------+---------+
                      |             |
                      |             v
                      |   +-------------------+
                      |   |  handle_frame()   |
                      |   |-------------------|
                      |   | decode command    |
                      |   | update stats      |
                      |   | build response    |
                      |   +---------+---------+
                      |             |
                      |             v
                      |   +-------------------+
                      |   | output / log      |
                      |   |-------------------|
                      |   | print / save / tx |
                      |   +-------------------+
                      |
                      v
             +----------------------+
             | resync / wait more   |
             |----------------------|
             | bỏ byte rác          |
             | hoặc chờ thêm data   |
             +----------------------+
			 