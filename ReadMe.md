# GarageSaveLoadBugLevel

This level provides a simple test environment for reproducing the garage save/load bug.

The level consists of a single garage, with a single unit loaded in the garage. The level also contains some diagnostic information relating to the bug which is output to the in-game message log. The information includes the unit array base address, along with the alignment of that address modulo 120 (the size of a `Unit` record). The bug happens when the alignment is 0 modulo 120. When this happens, the log message is accompanied by the garage selection sound. When the alignment is not suitable to reproduce the bug, the log message is accompanied by the building placement error sound. This lets the user know very quickly if the current environment is suitable for reproducing the bug.

## Bug Occurrence Rate

Conditions to reproduce the bug naturally happen about 1/15 times the level is started. Further, simply restarting the level with hotkeys `G`-`N`-`N` often leaves the unit array base address stuck on the same value after about the 3rd try. In that case, it may help to return to the main menu, or try loading a level first before continuing to get new unit array base address values.

As waiting for the correct conditions to naturally occur can be quite tedious, the [GarageSaveLoadBugModule](https://github.com/OutpostUniverse/GarageSaveLoadBugModule) project can be used in conjunction with this level to make bug reproduction reliable.

## More Information

For more information about the cause of the bug, the [op2ext](https://github.com/OutpostUniverse/op2ext) project contains an [Issue for the GarageSaveLoadBug](https://github.com/OutpostUniverse/op2ext/issues/204).
