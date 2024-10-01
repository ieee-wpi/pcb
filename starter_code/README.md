## Starter Code
This folder contains the starter code for the Track 1 board.

### Instructions
In order to program your board, you'll have to first flash a bootloader to your board (this will be done in class for you). Then, you can connect a USB cable to your board, compile, and upload one of the `.ino` files in this folder using the Arduino IDE. You can change and reupload the Arduino code at any time after the bootloader is flashed! 

Before you compile and upload code to your board, you'll have to
1. Install the FastLED library in the Arduino IDE. Go to `Tools -> Manage Libraries`, and search for `FastLED`.
2. Modify any `#define` statements in the code to match any differences in your board. For example, if your board has a different number of LEDs, make sure to update the code to reflect that.
3. In the top left of the IDE, change your board to `Arduino Leonardo` and port to the USB port your board is connected to.
    - On Windows, the port looks like `COMX` where `X` is the port number. You can use Device Manager to find the port the board is connected to.
    - On macOS, the port looks like `/dev/cu.*`. You can run `ls /dev/cu*` in a shell to find the port the board is connected to.
    
You're encouraged to modify and write custom code for your board! You can look at FastLED's examples for inspiration.

### Rainbow
The `rainbow` folder contains a program that will iterate back and forth across the LEDs, changing their hue. This is based on FastLED's "cylon" example code.

### Flashlight
The `flashlight` folder contains a program that will turn all the LEDs on your board to white at their full brightness. Be careful, this is very bright and will use a lot of current!
