# R3-URC!

This is the _main_ URC repo!

## Network IP Addresses

**Device**|**IP**|**Username**|**Password**
:-----:|:-----:|:-----:|:-----:
Rocket M2 UBNT-ROBOT|192.168.137.2|ubnt|robotrobot
Rocket M2 UBNT-BASESTATION|192.168.137.3|ubnt|robotrobot
Jetson TX1 (old)|192.168.137.212|ubuntu|ubuntu
Jetson TX1 (old) VPN|192.168.255.10 |ubuntu|ubuntu
Jetson TX1 (new)|192.168.137.213|ubuntu|ubuntu
Jeston TX1 (new) VPN|192.168.255.18|ubuntu|ubuntu
TP-link 1|192.168.0.254|admin|admin
TP-link 2|192.168.0.253|admin|admin
Daniel's Laptop|192.167.137.10| | 
Gab's laptop|192.167.137.22| | 

## Usage and layout

### Layout
The layout of this repo is like this:

| Path | What it is |
| --- | --: |
| `rosws/` | The main ros workspace |
| `rosws/src` | All the catkin packages, NOT all the nodes |
| `rosws/.gitignore` | A simple gitignore to keep per-system directories out of the repo |
| `microcontroller/` | All of the microcontroller (arduino) related things, grouped by device. |
| `scripts/` | Various useful scripts to use this repo for maximum productivity! |
| `devstuff/` | General other stuff that you want to put on git. The original git repo is copied here as well. |

### First clone
When you first clone this, you will want to run `scripts/setup_firsttime.sh` from the root directory. It will then setup everything.

### Arduino things
If you want to update one arduino, go into its directory, and use the command `$ pio run --target upload`. On the TX1, however, we know where all the arduinos are plugged in and a script (coming soon) will auto-update all of them.

### Build everything
Use the script `scripts/build.sh`. If a build fails, it will ask you if you want to continue.

## More documentation?
If we need more, or you just want to say something, you can use slack, or put it in the wiki for this repo. I might put a page about what to put in a package soon.

## P.S
Don't be a litterbug, keep general development... stuff in the `devstuff/` folder, and keep the structured code in the right directory!
