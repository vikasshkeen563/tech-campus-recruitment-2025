Solutions Considered:

Tried using a simple regex-based approach to parse logs by date. This was effective but needed improvements for speed and memory usage.
Explored multi-threading to speed up processing, but that added complexity without much gain for the current file size.

Final Solution Summary:

Went with a single-threaded approach that reads and parses logs line-by-line. Each log is stored in memory only once, and the results are written to a file as needed. This keeps things simple and effecient.

Steps to Run:

Compile the C++ code
Run the program with a date argument: ./log_parser 2025-01-31.
The logs for the specified date will be saved in output/output_YYYY-MM-DD.txt.
