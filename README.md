# Markdown to HTML

## Description

This is a simple library for parsing markdown files and converting them to HTML in Dosato

## Usage

```dosato
import "markdown" // Import the library

do write("test.html", markdown_to_html(read("test.md"))) // read your file (string) and convert it to HTML, then write it to a file
```

## Compiling

Make sure you have make installed on your system, alongside a C compiler (gcc, clang, etc.)<br>

```bash
make
```

## Dependencies

This library uses `md4c` for parsing markdown files. You can find that library [here](https://github.com/mity/md4c/)<br>
Credits to them for this amazing library :)