# Bare Metal Training 07: SPI Flash

## Assignment
1. Need to open and rewrite “Time Capsule” based on 16 Mbit SPI Serial Flash memory (SPI Clock Frequency is 500kBit/s).
2. Read time capsule content and save it to the text file. If it is empty – inform your mentor about it.
3. Send email message to person who create it (with content attached). Put current mentor and previous person mentor as CC. “We found your time capsule…”.
4. Erase time capsule (all memory).
5. Write your own time capsule. Send a message with the contest to your current mentor.
Read it back from the memory to check that everything is fine (after the power cycle off/on).
6. Time capsule message
“From: @USERNAME, @EMAIL”
“Mentor: @USERNAME, @EMAIL”
“Date: @DATE”
“TIME CAPSULE”
Poetry / Lyrics here, favorite song, etc. (8 – 16 lines). See sample below.
7. Each line should be written to the start of new 4kB block of memory.
Each line should end with CR (\n = #13) symbol.
So 20 lines – 20 memory blocks used (from the beginning of memory).
   
## [Solution](Core/)

## Additional Materials
Capture of the signal trace of the program in execution and video of it's work can be found here:
[Google Drive Folder With Additional Materials](https://drive.google.com/drive/folders/1bfuC0hg8dh-z5F1fcq6eww9zFhJMqi1H?usp=share_link)
