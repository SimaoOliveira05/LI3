# LI3
This project implements a data analysis system for a music streaming application, developed as a practical assignment for the **Computer Science Laboratories III** course. The system processes data related to music tracks, users, artists, albums, and usage history, enabling responses to specific queries about this data.


## Grade

**Final Grade:** 18 / 20 ⭐

## Authors

- *Gabriel Dantas* -> [@gabil88](https://github.com/gabil88)
- *José Fernandes* -> [@JoseLourencoFernandes](https://github.com/JoseLourencoFernandes)
- *Simão Oliveira* -> [@SimaoOliveira05](https://github.com/SimaoOliveira05)
- *Diogo Martins* -> [@Diog0martins](https://github.com/Diog0martins)

## Requirements
- **libc**: Standard C library
- **libglib2.0-dev**: GLib library for data structures (optional)
- **libncurses-dev**: For interactive mode implementation (optional)
- **libreadline-dev**: GNU readline for interactive mode (optional)


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
