# Cub3D - Raycasting Game Engine

A simple raycasting engine inspired by Wolfenstein 3D, developed as part of the 42 school curriculum. This project creates a 3D graphical representation of a maze using raycasting principles.

## Features

### Mandatory
- First-person perspective maze navigation
- Textured walls with different textures for each direction (N/S/E/W)
- Smooth player movement and rotation
- Configurable map and textures through `.cub` files

### Bonus
- Minimap display
- Mouse rotation control
- Collision detection
- Animated doors and sprites

## Technical Requirements

- gcc compiler
- Make
- MinilibX library
- X11 include files
- XShm extension

## Installation

```bash
# Clone the repository
git clone https://github.com/yacoub-harkati/42_cub3D.git

# Navigate to project directory
cd 42_cub3D

# For mandatory part
cd mandatory && make 

# For bonus part
cd bonus && make

# Run with a map file
./cub3D maps/map.cub
```

## Map Configuration

Maps use `.cub` extension and follow this format:
```
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0    # Floor color (RGB)
C 225,30,0     # Ceiling color (RGB)

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

Map elements:
- `0`: Empty space
- `1`: Wall
- `N/S/E/W`: Player starting position and orientation
- Space: Void (invalid path)

## Controls

### Mandatory
- `W/A/S/D`: Move forward/left/backward/right
- `←/→`: Rotate camera left/right
- `ESC/X close button`: Exit game

### Bonus
- Mouse movement: Camera rotation
- `E`: Interact with doorsq

## Project Structure

```
cub3D/
├── mandatory/
│   ├── Libft/              # Custom C library
│   ├── assets/
│   │   ├── maps/          # Map files
│   │   └── textures/      # Wall textures
│   ├── includes/          # Header files
│   ├── minilibx-linux/    # Graphics library
│   └── src/
│       ├── raycasting/    # Raycasting implementation
│       ├── utils/         # Utility functions
│       └── *.c           # Core functionality files
└── bonus/                # Same structure with bonus features
```

## Implementation Details

### Core Components
1. **Parsing**
   - Map file validation
   - Texture loading
   - Color parsing
   - Map validation

2. **Raycasting**
   - DDA (Digital Differential Analysis) algorithm
   - Wall collision detection
   - Texture mapping
   - Distance calculation

3. **Game Engine**
   - Player movement
   - Collision detection
   - Event handling
   - Memory management

## License

This project is part of 42 school curriculum. Check with 42 for license details.

## Authors

- rzarhoun (@rzarhoun)
- yaharkat (@yaharkat)

---
Made at 42