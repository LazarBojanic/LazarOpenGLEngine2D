A simple DVD vs BluRay 2D game made in OpenGL and C++.

Libraries and DLLs can be found at the following repository: https://github.com/LazarBojanic/LazarOpenGLEngineOOP

The project was made in Microsoft Visual Studio 2022 (x64).

Here I am putting an epilepsy warning just in case.

![animated GIF](LazarOpenGLEngine2D-1.gif)

![animated GIF](LazarOpenGLEngine2D-2.gif)

Libraries in use:
- GLFW -> OpenGL context,
- Glad -> OpenGL functions,
- stbi_image -> texture loading,
- glm -> mathematics library,
- irrKlang -> sound.

Instructions:
- If you're cloning, copy DLLs from the "dlls" folder in the repository to x64/Debug or x64/Release depending on the desired configuration. Download the "libraries" folder from the repository and place it in the project's root folder next to "assets", "src" etc. Build the project in Visual Studio. Then you can either run it from there, or just run the generated .exe file.
- Else, Download the latest release from releases.

The game has several GameStates:
- SCREEN_SAVER,
- TRANSITION_TO_ACTIVE,
- ACTIVE,
- WIN,
- LOSS.

Controls:
- SCREEN_SAVER ->
    B = Start the game,
    R = Reset dvd logo.
- ACTIVE ->
    Left Arrow/A = Move the dvd to the left,
    Right Arrow/D = Move the dvd to the right,
    Space = Shoot lasers.
- LOSS ->
    R = Restart the game.

Game settings:
In Game.cpp, in the initVariables function, game parameters can be set, such as the number of enemies per column and row (numberOfEnemiesPerLine, numberOfEnemyLines), and a bool called "singleLaser" which determines whether to use one or more lasers.