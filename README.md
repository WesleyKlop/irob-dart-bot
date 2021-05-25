# Dart bot

This is the code repository containing our software written for our Robotics minor.
The robot has the purpose of throwing darts on command by a web interface.

## Setup

We've written this project making use of the platformio development platform, using the CLion IDE.
Since using CLion is not the easiest to set up you can follow this simple guide:

- Configure the CLion toolchain for your platform
  - On Windows, use the MinGW toolchain
  - On macOS, use the default toolchain (required xcode tools)
  - On Linux, I don't know. You probably need CMake.
- Download and install PlatformIO core cli somewhere on your machine
- Download and install the PlatformIO CLion extension
- Create a PlatformIO CLion project somewhere and name it "IROB-dart-bot"
  - target should be arduino nano atmega328
- Clone this repository somewhere on your computer
  - `git clone git@github.com:WesleyKlop/IROB-dart-bot.git /tmp/dartbot`
- Copy the .git folder into your created project
  - `cp -r /tmp/dartbot/.git .git`
- Reset the project to get the correct files
  - `git reset --hard`
- Profit
  - You can also modify the run configurations. Remove the "build" step before it runs upload!