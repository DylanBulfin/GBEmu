# GBEmu
This is a basic Gameboy emulator. Sound is not implemented at all, and some MBCs are not finished.

Requires SDL2 and PortAudio to compile, probably only works on Windows (with MinGW) and Linux.

Put roms in the directory listed in the settings.txt file (relative to the emulator executable, default "roms/").

Saves will be stored in the directory set in the settings file (default "saves/") relative to the emulator executable, make sure the empty directoy is created before you open up a game that can save.

Use the provided makefile to compile, to run either directly run the emulator.out file or the run.py file (requires python 3) with the name of the rom (without directory or extension) as the only argument. E.g. the command "./emulator.out Game" will open and run the game in "roms/Game.gb" and, if the game has a battery backup, store the save in "saves/Game.sram" (unless you've set different directories in settings.txt).
