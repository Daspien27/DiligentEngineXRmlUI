# DiligentEngineXRmlUI
This Repo investigates generating a Diligent Engine backend for RmlUi

Build system: Visual Studio 2019

Platform: Just windows for now...sorry!

Build dependencies:

- clone DiligentEngine (https://github.com/DiligentGraphics/DiligentEngine) and install it through cmake to some directory. Then add an environment variable DILIGENT_ENGINE_INSTALL_DIR pointing to that folder.
- install vcpkg and the following dependencies for the win64 triplet
   - glfw
   - RmlUi
   
A lot of my design decisions have been porting the RmlUi_Backend_GLFW_GL3.cpp/RmlUi_Platform_GLFW.cpp/RmlUi_Renderer_GL3.cpp from https://github.com/mikke89/RmlUi/tree/master/Backends.

The samples I used to make the code come from the Tutorials/Samples in the DiligentEngine repo, but also from my sandbox solution https://github.com/Daspien27/LearnDiligentEngine.
   
