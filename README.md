# rovPlayer - Remote OSC Video Player 

build with openframeworks verison `0.11`  
only tested on linux  
support for basic mapping and shader  

## keyboard controls
press `e` to enter and leave edit mode  
press `a` to add a new player (works only in edit mode)  
press `R` to remove the last added player  (works only in edit mode)  
press `f` to enter and leave fullscreen  


## OSC controls
|address   |   arguments 
| --------------|:-------------
| toggle fullscren
| `/settings/fullscreen` 
| start video playback
| `/play`           | `int(player)` 
| stop video playback
| `/stop`           | `int(PLAYER)` 
| pause video playback |  the second bool is for displaying the current frame or not and is optional 
| `/pause`          | `int(PLAYER) bool(STATE) bool(BLACK)`
| toggle pause state
| `/togglePause`    | `int(PLAYER)`
| load video file or stream
|`/load`            |  `int(PLAYER) string(PATH)` 
| set loop mode     |  0=no loop, 1=normal loop, 2=palindrome
|`/loop`            | `int(PLAYER) int(MODE)`
| set surface position
| `/setPosition`    | `int(PLAYER) int(X_POS) int(Y_POS)`
| set surface corner position | corner numbers are orderd counte clockwise starting with 0 for the top left corner
| `/setCorner`       | `int(PLAYER) int(CORNER) int(X_POS) int(Y_POS)`
| load first shader 
| `/loadShaderA`    | `int(PLAYER) string(PATH)`
| enable or disable first shader
| `/enableShaderA`  | `int(PLAYER) bool(STATE)`
| pass values to first shader | can be up to 4 values 
| `setShaderA`      | `float(VAL_A) float(VAL_D) float(VAL_C) float(VAL_D)`
| load second shader 
| `/loadShaderB`    | `int(PLAYER) string(PATH)`
| enable or disable second shader
| `/enableShaderB`  | `int(PLAYER) bool(STATE)`
| pass values to second shader | can be up to 4 values 
| `/setShaderB`      | `float(VAL_A) float(VAL_D) float(VAL_C) float(VAL_D)`

