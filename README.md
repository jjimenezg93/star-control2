# Star Control 2

Remake of the classic game **Star Control 2**, developed putting together:

- [U-gine](https://github.com/jjimenezg93/U-gine "U-gine"). Extended with Audio manager (OpenAL)
- [Input Manager](https://github.com/jjimenezg93/InputManager "Input"). Extended with GUI manager
- ECS and Machine State for scenes taken from [Dodger](https://github.com/jjimenezg93/Dodger "Dodger").

___

###Project description
The main goal of this project is to develop a game mixing different systems previously developed.
___

###IMPORTANT NOTES

To configure input keys for each player, [ASCII](http://www.asciitable.com/ "ASCII table") dec codes must be set in `controls.json` file

Configurable keys allowed are all ASCII codes between 32 and 127 (defined in `event.h` -> `EKeyboardEventID`). Note that keys which need Shift are not currently
supported.

Special characters, such as Enter and arrow keys, must be added to `m_specialKeys` vector in `CKeyboardController::Init()`, using *`GLFW_KEY_<key_name>`*,
search for GLFW_KEY_SPECIAL.
___

###Version
Project is currently at **v1.0**
