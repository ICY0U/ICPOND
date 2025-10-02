# ICPONDs (UE 5.6, C++) — CosyPond prototype basics

This is a tiny starter project for your game jam idea.
It includes:
- **BoatPawn**: simple physics-y thrust/turn movement, drag and speed cap.
- **PondGameModeBase**: defaults to the boat pawn.
- **CurrentVolume**: a box volume that gently pushes overlapping actors to simulate pond currents.
- **Input**: WASD / Left stick, and `E`/LMB to "Fish" (logs for now).

## Getting started
1. Extract the ZIP.
2. Open `ICPONDs.uproject` with Unreal 5.6. If prompted, allow it to build the C++ project.
3. Create a new empty level (or open one), then **Play**. The boat auto-possesses Player 0.
4. Optional: place **CurrentVolume** actors in the world to add gentle currents (set direction/strength on the instance).

## Notes
- The boat uses the engine's built-in Cylinder mesh so no assets are required.
- Movement is intentionally cosy: moderate thrust, high damping, and quadratic water drag.
- Fishing input is wired; you can add logic later (line/bobber/mini-game).
- You can tune values in the BoatPawn instance or class defaults.


## Test Pond Level (runtime spawner)
You asked for a test level with water. Since map `.umap` files are binary and can't be authored here, this project includes **`PondTestSpawner`** which builds a playable test pond **at runtime**:

1. In the Editor, create a new empty level (Default).
2. In the Place Actors panel, search for **PondTestSpawner** and drop it at the world origin (0,0,0).
3. Press **Play**.
   - A large **SimpleWaterPlane** is spawned at `Z=0` (tries Water plugin material; falls back to a plain plane).
   - **9 islands** are arranged in a ring.
   - A ring of **CurrentVolume** actors creates a gentle clockwise current.
   - Your **BoatPawn** auto-possesses and you can row around and press **E** to fish.

You can also tweak the spawner's exposed properties (pond radius, island count, current strength).
