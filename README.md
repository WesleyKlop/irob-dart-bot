# Dart bot

This is the code repository containing our software written for our Robotics
minor. The robot has the purpose of throwing darts on command by a web
interface.

## Setup

### Arduino robot

We've written this part making use of the platformio development platform, using
the CLion IDE. Since using CLion is not the easiest to set up you can follow
this simple guide:

- Configure the CLion toolchain for your platform
  - On Windows, use the MinGW toolchain
  - On macOS, use the default toolchain (requires xcode tools)
  - On Linux, I don't know. You probably need CMake.
- Download and install PlatformIO core cli somewhere on your machine
  - [https://docs.platformio.org/en/latest/core/installation.html#installation-methods]()
  - On Windows, make sure to add the path to the cli to your system
    environment variables.
- Download and install the PlatformIO CLion extension
  - You can find this on the plugin marketplace inside CLion
- Create a PlatformIO CLion project somewhere and name it "robot"
  - target should be arduino nano atmega328
- Clone this repository somewhere on your computer
  - `git clone git@github.com:WesleyKlop/IROB-dart-bot.git dart-bot`
- Copy the relevant files/folders into your cloned project.
  - `mv path/to/robot/project/{.pio,CMakeListsPrivate.txt,.idea,cmake-build-*} dart-bot/robot`
  - `rm -rf path/to/robot/project`
- Profit
  - You can also modify the run configurations. Remove the "build" step before
    it runs upload!

### Server

Our Server is made with Python 3.9. We utilize Flask, Q-learning and develop in
PyCharm.

#### Development

- Open the folder with PyCharm.
- Configure your interpreter. (Python 3.9, please use venv or something)
- Install requirements `pip install -r requirements.txt`
  - When installing new packages you can dump packages
    using `pip freeze > requirements.txt`
- Should just work.

#### Deployment

This part should be deployed to a Raspberry Pi. We use an RPI 4 8gb. On our
server we configured Nginx + Gunicorn for serving the application and wrote some
systemd services for keeping it alive.

## Q-Learning

We utilize Q-Learning for reinforcement learning. We configure some parameters
for our state, select the spot where we want to shoot and then give feedback to
our agent on how it went.

These are the different parts of our Q-learning network:

- Agent: The dart robot itself, which calibrates the servos using the
  Q-network.
- Action: The timings for the two servos
- Environment: The dart board where the dart lands
- Reward: Integer based on if the dart actually hit.
- State: Robot height, elastic band age.

So by supplying the Q-network with the parameters for robot height and elastic
age we can get timings for the robot. After we have calibrated this we can use
our aiming formula to compensate for the different distances/heights for various
spots on the board.
