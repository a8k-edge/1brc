# 1BRC
Output - original solution prints map of formated records.
So expected output is formated records of `Station<delimiter><min>/<mean>/<max>` with idiomatic Map wrapper.

## Environment
### Hardware
- 12th Gen Intel(R) Core(TM) i5-12400   2.50 GHz
- 16 GB RAM
- Storage Samsung Portable SSD T5, NTFS

### Software
- C++ 11.3 version (WSL)
- Java 21 version (WSL)
- Python 3.11
- Golang 1.20

## Results

### Execution Time
#### Create measurement(1 billion records)
- Java (Original 1BRC code):  5:15
- CPP: 1:56 (1:46 user, 0:10 sys spaces)
- Py: 17:06
- Golang: 5:54

#### Aggeregation (m:s)
- Java (Original 1BRC code): 8:54
- CPP: 7:13 (3:14 user, 0:13 sys space)
- Py: 10:28
- Golang: 1:59
