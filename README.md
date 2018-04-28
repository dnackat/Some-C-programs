# Questions

## What's `stdint.h`?

A: stdint.h is a header file in the C standard library that provide a set of typedefs to set up exact width integer types along with an upper and a lower limit.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

A: They specify the exact size of memory for a given variable, irrespective of the platform on which the program is run.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

A: 1 byte, 4 bytes, 4 bytes, and 2 bytes respectively.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

A: The first two bytes of a BMP file are 0x42 and 0x4D in hexadecimal (BM in ASCII).

## What's the difference between `bfSize` and `biSize`?

A: bfSize is the total size in bytes of the BMP file, whereas biSize is the size in bytes of the 'BITMAPINFOHEADER' struct.

## What does it mean if `biHeight` is negative?

A: If biHeight is negative, the BMP is top-down with origin at the top left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

A: The variable biBitCount.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

A: There are several reasons why this can happen:
   . The file doesn't exist
   . You do not have permission to access the file
   . The file exists in a different directory than the one the program is searching in
   . The file is opened in a mode that doesn't allow the current operation

## Why is the third argument to `fread` always `1` in our code?

A: It is because we intend to read the image file one pixel (triple) at a time, so the **qty** argument is set to 1.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

A: The padding value would be 3 bytes.

## What does `fseek` do?

A: **fseek** is used to move the file pointer associated with a file to a desired position.

## What is `SEEK_CUR`?

A: **SEEK_CUR** denotes the pointer's current position.
