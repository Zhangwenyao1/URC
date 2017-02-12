# R3-URC!

This is the _main_ URC repo, with real URC code, not shared developer testing. For that use a personal repo. (We may have another repo specifically for that purpose, check back later)

## Other repos and links of interest

None yet

## Usage and layout

### Layout
The layout of this repo is like this:
| Path | What it is |
| --- | --: |
`rosws/` | The main ros workspace
`rosws/src` | All the catkin packages, NOT all the nodes
`rosws/.gitignore` | A simple gitignore to keep per-system directories out of the repo
`microcontroller/` | All of the microcontroller (arduino) related things, grouped by device.
`scripts/` | Various useful scripts to use this repo for maximum productivity!
`devstuff/` | General other stuff that you want to put on git. The original git repo is copied here as well.

### First clone
When you first clone this, you will want to run `scripts/setup_firsttime.sh` from the root directory. It will then setup everything.

### Arduino things
If you want to update one arduino, go into its directory, and use the command `$ pio run --target upload`. On the TX1, however, we know where all the arduinos are plugged in and a script (coming soon) will auto-update all of them.

### Build everything
Use the script `scripts/build.sh`. If a build fails, it will ask you if you want to continue.

## More documentation?
If we need more, or you just want to say something, you can use slack, or put it in the wiki for this repo. I might put a page about what to put in a package soon.

## P.S
Don't be a litterbug, keep general development... stuff in the `devstuff/` folder, and keep the structured code in a differnet
