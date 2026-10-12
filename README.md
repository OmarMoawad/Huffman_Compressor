# Huffman Compressor

A lossless text-file compressor and decompressor in C++, built on Huffman coding.

The program counts how often each character appears and builds a Huffman tree with a
min-heap (`std::priority_queue`). It then gives each character a prefix-free bit code and
packs the encoded bit stream into bytes. The compressed file starts with the code table and
the number of padding bits, so decompression needs nothing except that file.

`#C++` `#Huffman_Coding` `#Greedy_Algorithms` `#Priority_Queue`

## Project structure

```
Huffman_Compressor/
├── src/
│   ├── main.cpp        # command-line entry point: parses arguments, runs compress/decompress
│   ├── Huffman.h/.cpp  # tree construction, encoding, decoding, bit/byte helpers
│   └── CodeTable.h/.cpp# one (symbol, code) entry of the Huffman code table
├── data/
│   └── input.txt       # sample input file
├── archive/            # original prebuilt binary and sample outputs from the 2020 submission
├── Makefile
└── README.md
```

## Requirements

- A C++17 compiler (`g++` or `clang++`)
- `make`

There are no external libraries.

## Build

```bash
make
```

This produces the executable `build/huffman`.

## Usage

```bash
./build/huffman <input-file> <output-file> <flag>
```

| Argument        | Meaning                                         |
|-----------------|-------------------------------------------------|
| `<input-file>`  | file to read                                    |
| `<output-file>` | file to write                                   |
| `<flag>`        | `c` to compress, `d` to decompress              |

### Example

```bash
# compress the sample file
./build/huffman data/input.txt build/input.huf c

# decompress it again
./build/huffman build/input.huf build/input.decoded.txt d

# the decoded file is identical to the original
cmp data/input.txt build/input.decoded.txt
```

To run all three steps at once:

```bash
make demo
```

The program prints its working (character frequencies, the code table and the bit stream)
to the terminal as it runs.

## Author

Omar Kamel Hamed
