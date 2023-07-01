# Cloth Simulator
A simple 2D cloth simulator, written in C++ SFML. Program provides realistic *tearing* and *moving*/*dragging* of the cloth.

The simulation works based on the principles of [Verlet Integration](https://en.wikipedia.org/wiki/Verlet_integration). The cloth consists of *particles* and *constraints* (sticks connecting the particles). The force is applied to the small particles and sticks adjust accordingly.

<p align="center">
   <img src="demo/example-gif.gif" alt="animated" />
</p>


## Prerequisites
The program was developed in [C++14](https://en.cppreference.com/w/cpp/14). Additionally, the [SFML](https://www.sfml-dev.org/) library was used for graphics.


## Getting Started
To run the program, download and unzip [Cloth-Simulator.zip](Cloth-Simulator.zip). You should expect the directory below:

```
+-- Cloth Simulator
|   +-- Cloth - Shortcut.lnk
|   +-- App
|   |   +-- assets
|   |   +-- Cloth.cbp
|   |   +-- Cloth.exe
|   |   +-- sfml-audio-2.dll
|   |   +-- sfml-graphics-2.dll
|   |   +-- ...
```

Running the **Cloth** shortcut should be enough to access the program.


## Used Modules
- *main.ccp* - main function launching the app
- *gui/cloth_app.hpp*, *gui/cloth_app.ccp* - cloth simulator app window
- *engine/cloth.hpp*, *engine/cloth.ccp* - cloth object (verlet entity), initializing and managing interactions
- *engine/verlet/\*.hpp*, *engine/verlet/\*.ccp* - implementation of verlet classes (point, constraint, entity), contain base of the simulation physics


## Future Improvements/Sophistications
- **Dynamic Tearing by Distance** - weight of the cloth itself could result in tears
- **Texture and other Graphics** - current implementation is kept simple for demonstration, but better graphics could be added


## Details
- Author - Arastun Mammadli
- License - [MIT](LICENSE)
