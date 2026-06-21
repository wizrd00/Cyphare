# Cyphare
![Language](https://img.shields.io/badge/C-C99-blue)
![Platform](https://img.shields.io/badge/Linux-POSIX-green)
![Compiler](https://img.shields.io/badge/PCC%20%7C%20GCC-Tested-orange)

Cyphare is a secure UDP-based file sharing utility designed for fast and reliable file transfers over local networks.

Built on top of the RUFShare protocol, Cyphare combines peer discovery, reliable UDP transmission, and integrity verification into a simple command-line tool.

---

## Features

- Fast file transfer over UDP
- Reliable delivery with retransmission support
- Automatic peer discovery
- Local network scanning
- Data integrity verification
- Lightweight and dependency-free
- Written entirely in C

---

## Installation

```bash
make
```

Generated executable:

```text
cyphare
```

---

## Usage

```bash
./cyphare TASK [OPTIONS]
```

Available tasks:

```text
scan    Discover receivers on the network
pull    Wait for incoming files
push    Send a file to a receiver
```

---

## Discover Receivers

Scan the local network for available receivers:

```bash
./cyphare scan
```

Specify source address:

```bash
./cyphare scan \
    -s 192.168.1.10:1308
```

---

## Receive Files

Start listening for incoming transfers:

```bash
./cyphare pull
```

Custom receiver name:

```bash
./cyphare pull \
    -n alice
```

Custom source address:

```bash
./cyphare pull \
    -s 0.0.0.0:1307
```

---

## Send Files

Transfer a file to a receiver:

```bash
./cyphare push \
    -f archive.tar.gz \
    -d 192.168.1.25:1307
```

Specify sender name:

```bash
./cyphare push \
    -f image.iso \
    -d 192.168.1.25:1307 \
    -n arash
```

Specify chunk size:

```bash
./cyphare push \
    -f backup.bin \
    -d 192.168.1.25:1307 \
    -c 65535
```

---

## Example Workflow

Receiver:

```bash
./cyphare pull -n laptop
```

Sender:

```bash
./cyphare scan
```

Output:

```text
[0] laptop (192.168.1.25:1307)
```

Transfer:

```bash
./cyphare push \
    -f report.pdf \
    -d 192.168.1.25:1307
```

---

## How It Works

Cyphare uses a custom reliable UDP protocol:

1. Receiver announces availability.
2. Sender discovers the receiver.
3. Transfer metadata is exchanged.
4. File is split into chunks.
5. Chunks are acknowledged.
6. Missing data is retransmitted.
7. Integrity checks verify correctness.

This approach provides TCP-like reliability while keeping protocol behavior fully application-controlled.

---

## Project Structure

```text
include/
├── cyphare.h
├── launcher.h
└── utils/

source/
├── cyphare.c
├── launcher.c
└── utils/

library/
├── librufshare.so
└── libunity.so
```

---

## Requirements

- Linux
- POSIX sockets
- pthread
- C99 compatible compiler

Tested with:

- PCC
- GCC

---

## Why Cyphare?

Most file-sharing tools are either:

- Heavyweight
- GUI-focused
- TCP-only

Cyphare was created as a lightweight alternative for developers who want a fast, scriptable, and transparent file transfer tool built around a custom UDP protocol.

---

## License

See the LICENSE file for details.