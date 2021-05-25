# Dart bot

This is the code repository containing our software written for our Robotics minor.
The robot has the purpose of throwing darts on command by a web interface.

## Setup

We've written this project making use of the platformio development platform, using the CLion IDE.
Since using CLion is not the easiest to set up you can follow this simple guide:

- Configure the CLion toolchain for your platform
  - On Windows, use the MinGW toolchain
  - On macOS, use the default toolchain (requires xcode tools)
  - On Linux, I don't know. You probably need CMake.
- Download and install PlatformIO core cli somewhere on your machine
  - [https://docs.platformio.org/en/latest/core/installation.html#installation-methods]()
- Download and install the PlatformIO CLion extension
  - You can find this on the plugin marketplace inside CLion
- Create a PlatformIO CLion project somewhere and name it "IROB-dart-bot"
  - target should be arduino nano atmega328
- Clone this repository somewhere on your computer
  - `git clone git@github.com:WesleyKlop/IROB-dart-bot.git tmp-dartbot`
- Copy the .git folder into your created project, and reset project
  - `mv tmp-dartbot/.git .git`
  - `rm -rf tmp-dartbot`
  - `git reset --hard`
- Profit
  - You can also modify the run configurations. Remove the "build" step before it runs upload!
