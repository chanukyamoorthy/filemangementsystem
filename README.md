# File mangement system

[CC TV] --> Stream Data --> [Storage]

[Storage] - Data structures to store the stream data

       - It will be blocks of data (not complete data)

At one particular time, CC TV will stream data on modification

At initial setup,  CCTV will stream the data about the empty room. Blocks are created and stored in the in-memory.

Since room is static, there will be no streams after the initial streaming

When a person moves inside the room, pixels changes. Data will be streamed to in-memory now.

Example:

Assumptions:
  1.Block of data of 8 bytes
  2.Multiple files will be saved
  3.In-memory management (no file operations)
  4.Print data structure contents for every input
 

SaveData(fileName, "content", timestamp)

SaveData("FileName1", "ABCDEFGHIJKLMONPQRSTUVWX", 5)

file name: FileName1

Content: ABCDEFGHIJKLMONPQRSTUVWX

Timestamp: 5

Data stored:

{0, ABCDEFGH, 5}, {1, IJKLMNOP, 5}, {2, QRSTUVWX, 5},

 

SaveData("FileName1", "ABCDEFGHIJKLMONPQRSTUVWXYZ", 10)

file name: FileName1

Content: ABCDEFGHIJKLMONPQRSTUVWXYZ

Timestamp: 10

Data stored:

{0, ABCDEFGH, 5}, {1, IJKLMNOP, 5}, {2, QRSTUVWX, 5}, {3, YZ, 10}

 

SaveData("FileName1", "ABCDEFGHIJKLMONPQRSTUVWXXXXXYZ", 15)

file name: FileName1

Content: ABCDEFGHIJKLMONPQRSTUVWXXXXXYZ

Timestamp: 15

Data stored:

{0, ABCDEFGH, 5}, {1, IJKLMNOP, 5}, {2, QRSTUVWX, 5}, {3, YZ, 10}, {4, XXXXYZ, 15}

 

SaveData("FileName1", "ABCDEFGHIJKLMO", 20)

file name: FileName1

Content: ABCDEFGHIJKLMO

Timestamp: 20

Data stored:

{0, ABCDEFGH, 5}, {1, IJKLMNOP, 5}, {2, QRSTUVWX, 5}, {3, YZ, 10}, {4, XXXXYZ, 15}, {4, IJKLMO, 20}


PrintData(fileName, timestamp)

PrintData(FileName1, 10)

ABCDEFGHIJKLMONPQRSTUVWXYZ

PrintData(FileName1, 20)

ABCDEFGHIJKLMO
