# term-worm

A terminal-based platformer game where you play as a character (#) running and jumping across platforms. Similar to Google's dinosaur game, but with a focus on jumping over gaps between platforms.

## Features

- **Endless runner gameplay**: Platforms generate procedurally as you progress
- **Jumping mechanics**: Use SPACE or UP arrow to jump over gaps
- **Scoring system**: Earn points for distance traveled and platforms successfully jumped
- **Arcade-style difficulty**: React quickly to avoid falling into gaps
- **Terminal graphics**: Runs entirely in your terminal using ncurses

## How to Play

1. Your character (#) automatically runs forward
2. Press **SPACE** or **UP arrow** to jump when you see a gap
3. Land on platforms (=) to continue running
4. Avoid falling into gaps or off the screen
5. Try to achieve the highest score possible!

## Controls

- **SPACE** or **UP arrow**: Jump
- **Q**: Quit the game

## Building and Running

### Prerequisites

You need `ncurses` library installed:

**macOS**: 
```bash
# Usually pre-installed, but if needed:
brew install ncurses
```

**Ubuntu/Debian**:
```bash
sudo apt-get install libncurses5-dev libncursesw5-dev
```

**CentOS/RHEL**:
```bash
sudo yum install ncurses-devel
```

### Compile and Run

```bash
make
./term-worm
```

### Clean Build

```bash
make clean
make
```

## Game Mechanics

- **Physics**: The character is affected by gravity and has realistic jumping physics
- **Platform Generation**: Platforms appear with random widths and gaps
- **Collision Detection**: Precise collision detection for platforms and gaps
- **Auto-scrolling**: The camera automatically moves forward, creating urgency
- **Scoring**: 
  - 1 point per 10 units of distance traveled
  - 10 bonus points per platform successfully jumped

## Technical Details

- Written in C99 standard C
- Uses ncurses for terminal graphics
- Real-time input handling with non-blocking I/O
- Smooth character physics with gravity and velocity
- Dynamic platform management system

Enjoy the game!
