# GBEmu
This is a basic Gameboy emulator. Sound is not implemented at all and not all games work perfectly.

## Demo Videos
Tetris - https://www.youtube.com/watch?v=tNwYMBqwgAs

Metroid II: Return of Samus - https://www.youtube.com/watch?v=5bL7oTIxEGY

Final Fantasy Adventure - https://www.youtube.com/watch?v=fKTiKOippgE

Pokemon Yellow - https://www.youtube.com/watch?v=dSGP_QIFN8c

Super Mario Land 2: 6 Golden Coins - https://www.youtube.com/watch?v=Ycxi_ZaPbx4

Wario Land II - https://www.youtube.com/watch?v=phLfPmjXBYM


Full playlist for ease of access - https://www.youtube.com/playlist?list=PLinm6frsc3SR5eT5ezNUtylG4ntSj3-oa

## Instructions for use
If you want to test it with your own games, simply download the package for your specific OS (only Win32 is available right now until I get a new hard drive and reinstall Linux, I'm afraid). Extract it to some folder. Put your roms in the roms folder, ensure they all have the file extension .gb (if it comes with extension .gbc just rename, if it comes with any other extension it probably isn't a Game Boy game but feel free to try your luck). To run, open up a terminal in the folder and type "./emulator.exe <gamename>" (or "./emulator <gamename> on Linux), replacing <gamename> with the name of the rom without the filename. For example, running the command "./emulator.exe tetris" will use the file ./roms/tetris.gb (unless you change the roms folder in the settings file).
  
## Settings
FAST_FORWARD - Set to true or false, if set to true it doesn't wait between frame draws and will run significantly faster.

WINDOW_HEIGHT - Set to height of window in pixels.

WINDOW_WIDTH - Set to width of window in pixels, preferably equal to 10/9 * WINDOW_HEIGHT.

COLOR_MODE - Set to green or grey/gray, determines palette that will be used for rendering the pixel array.

SAVE_DIRECTORY - Set to name of save directory with trailing forward slash.

GAME_DIRECTORY - Set to name of game directory with trailing forward slash.

LOAD_SAVE - Set to true or false, if set to false it won't load saves from save directory even if they exist.

A_KEY - Set to SDL-compliant name of key corresponding to A

B_KEY - Set to SDL-compliant name of key corresponding to B

START_KEY - Set to SDL-compliant name of key corresponding to Start

SELECT_KEY - Set to SDL-compliant name of key corresponding to Select

UP_KEY - Set to SDL-compliant name of key corresponding to Up

DOWN_KEY - Set to SDL-compliant name of key corresponding to Down

LEFT_KEY - Set to SDL-compliant name of key corresponding to Left

RIGHT_KEY - Set to SDL-compliant name of key corresponding to Right
