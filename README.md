# Music Streaming System

## Description

This project implements a data analysis system for a music streaming application, developed as a practical assignment for the **Computer Science Laboratories III** course. The system processes data related to music tracks, users, artists, albums, and usage history, enabling responses to specific queries about this data.

## Features

- **Streaming data analysis**: Processing of datasets with information about music, users, artists, albums, and history
- **Query system**: 6 different queries for statistical data analysis
- **Data validation**: Syntactic and logical validation of CSV files
- **Multiple execution modes**: Main, interactive, and testing programs
- **Memory management**: Implementation without memory leaks
- **Modularization**: Code structured in modules with clear separation of responsibilities

## Architecture

The system is organized into the following modules:

- **I/O Modules**: Reading and writing CSV data
- **Entity Modules**: Representation of music, users, artists, albums
- **Manager Modules**: Management of different entities
- **Query Module**: Implementation of interrogations
- **Utility Modules**: Auxiliary functions and data structures
- **Validation Module**: Syntactic and logical data validation

## Project Structure

```
trabalho-pratico/
├── include/                 # Interface files (.h)
├── src/                     # Implementation files (.c)
├── resultados/              # Query outputs and error files
├── relatorio-fase1.pdf      # Phase 1 Report
├── relatorio-fase2.pdf      # Phase 2 Report
├── programa-principal       # Main executable (after make)
├── programa-interativo      # Interactive executable (after make)
├── programa-testes          # Testing executable (after make)
└── Makefile                 # Compilation script
```

## Compilation

```bash
# Compile all executables
make

# Compile only the main program
make programa-principal

# Compile only the interactive program
make programa-interativo

# Compile only the testing program
make programa-testes

# Clean compiled files
make clean
```

## Usage

### Main Program
Used by the automatic evaluation platform:
```bash
./programa-principal <dataset_path> <commands_file>
```

**Example:**
```bash
./programa-principal dataset/ input.txt
```

### Interactive Program
Interactive interface for manual query execution:
```bash
./programa-interativo
```

### Testing Program
Validation and performance measurement:
```bash
./programa-testes <dataset_path> <commands_file> <expected_results>
```

**Example:**
```bash
./programa-testes dataset/ input.txt resultados-esperados/
```

## Dataset

The system processes the following CSV files:

- **musics.csv**: Music information (ID, title, artist, album, duration, genre, year, lyrics)
- **users.csv**: User data (username, email, name, age, country, subscription, liked songs)
- **artists.csv**: Artist information (ID, name, description, revenue per stream, constituents, country, type)
- **albums.csv**: Album data (ID, title, artists, year, producers)
- **history.csv**: Playback history (ID, user, music, timestamp, duration, platform)

## Available Queries

1. **Q1**: User or artist summary by ID
2. **Q2**: Top N artists with largest discography (optional country filter)
3. **Q3**: Most popular genres by age range
4. **Q4**: Artist that appeared most times in top 10 (optional date filter)
5. **Q5**: User recommendation with similar tastes
6. **Q6**: Annual summary for a user (optional top N artists)

### Query Format

```
# Standard format (';' separator)
1 U0071877
2 10 Finland

# Alternative format ('=' separator)
1S U0071877
2S 10 Finland
```

## Data Validation

The system implements complete validation of input data:

### Syntactic Validation
- **Dates**: YYYY/MM/DD format
- **Duration**: HH:MM:SS format
- **Email**: username@domain.ext format
- **Subscription Type**: 'normal' or 'premium'
- **Platform**: 'mobile' or 'desktop' (case-insensitive)
- **Artist Type**: 'individual' or 'group' (case-insensitive)
- **Lists**: "[item1,item2,...]" format

### Logical Validation
- Valid references between entities
- Relational data consistency
- Referential integrity validation

## Testing and Performance

The testing program provides:
- Query correctness validation
- Execution time measurement for each query type
- Memory usage analysis
- Detailed error reporting with line numbers

Example output:
```
Q1: 100 of 100 tests ok!
Q2: 90 of 100 tests ok
Discrepancy in query 84: line 10 of "resultados/command84_output.txt"
...
Memory used: 312MB
Execution times:
Q1: 100.0 ms
Q2: 235.6 ms
Total time: 113s
```

## Dependencies

### Required Libraries
- **libc**: Standard C library
- **libglib2.0-dev**: GLib library for data structures (optional)
- **libncurses-dev**: For interactive mode implementation (optional)
- **libreadline-dev**: GNU readline for interactive mode (optional)

## Memory Management

The project emphasizes proper memory management:
- No memory leaks (validated with Valgrind)
- Proper allocation and deallocation of dynamic memory
- Safe handling of data structures

## Code Quality

The codebase follows best practices:
- **Modularization**: Clear separation between interface (.h) and implementation (.c)

