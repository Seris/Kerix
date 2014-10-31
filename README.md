Kerix
=====

Minimalist kernel for i386 (x86) system

## Prerequisite
- gcc (Compiled with v4.9.1)
- qemu (with i386 system)
- make (Tested with v4.0)

## Build
* Build all
`make all`
* Rebuild all
`make rebuild`
* Rebuild a directory
`make rebuild DIR=$dir`
* Clean .o and executables
`make clean`

## Testing
* Start qemu
`make start-qemu`
* Connect GDB to qemu
```
# In kerix.config
QEMU_ARGS=-s -S

make start-qemu
make gdb-connect-qemu
```
* Kill qemu
`make kill-qemu`