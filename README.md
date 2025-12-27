# Clinic

A small C project for managing clinic records (patients and appointments).

## Summary

This repository contains a C program that works with patient and appointment data. Source files implement core data structures and functions to read and process records from a data file.

## Files

- `clinic.c` - main program and user-facing logic
- `clinic.h` - public declarations and data structures
- `core.c` - core helper functions and file I/O
- `core.h` - core function declarations

## Prerequisites

- A C compiler (GCC/Clang) or MSVC on Windows
- Make (optional)

## Build

Using GCC (MinGW/MSYS or WSL):

```bash
gcc -o clinic clinic.c core.c -Wall -Wextra
```

Using Microsoft Visual C++ (Developer Command Prompt):

```powershell
cl /Fe:clinic.exe clinic.c core.c
```

## Run

Run the built executable and provide the data file path (if the program expects one). Example (PowerShell):

```powershell
# On Windows, if you built clinic.exe:
.\clinic.exe path\to\datafile.txt

# On Unix-like shells:
./clinic path/to/datafile.txt
```

If the program reads from a default file or stdin, check `clinic.h` and `clinic.c` for the expected inputs.

## Usage notes

- The project currently provides functions to read patient and appointment records into arrays; ensure any buffers passed in match the expected `max` sizes to avoid overruns.
- Check `clinic.h` for function prototypes and data structure definitions.

## Contributing

Small fixes, clearer build instructions, or sample data files are welcome. Open an issue or submit a pull request.

