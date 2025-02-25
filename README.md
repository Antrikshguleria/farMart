**Overview**

The project consists of two C++ programs:

1) build_index.cpp: Builds an index file (log_index.idx) that maps dates to byte offsets in the log file.

2) extract_logs.cpp: Uses the index file to efficiently extract logs for a specific date and saves them to an output file.

Build and Run Instructions

**Step 1**: Build the Index
1) Compile build_index.cpp:
**g++ build_index.cpp -o build_index**

2) Run build_index to create the index file:
**./build_index**
This will generate the log_index.idx file.

**Step 2**: Extract Logs
1)  extract_logs.cpp:
**g++ extract_logs.cpp -o extract_logs**

2) Run extract_logs with a date as an argument:
**./extract_logs YYYY-MM-DD**
**Example: ./extract_logs 2024-12-01**

Check the output:
The logs for the specified date will be saved in output/output_YYYY-MM-DD.txt.

**How It Works**
1) **Index Building:**
- The build_index program reads the log file line by line.
- It extracts the date from each log entry and records the byte offset of the first log entry for that date.
- The index is saved to a file (log_index.idx).

2) **Log Extraction:**
- The extract_logs program loads the index into memory.
- It uses the index to jump directly to the byte offset of the first log entry for the specified date.
- It reads and writes logs until it encounters a log entry for a different date.
