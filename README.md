# Halloween Console Raycaster

A Windows console 3D-ish (ray casting) mini game built on a modified OneLoneCoder (Javidx9) console game engine. You explore a maze, shoot ghosts, avoid being touched, and win when every ghost is gone.

## Project Layout
- Solution: [Halloween_Game.sln](Halloween_Game.sln)
- Game source: [Halloween_Game/Halloween_Game.cpp](Halloween_Game/Halloween_Game.cpp)
- Engine header: [Halloween_Game/olcConsoleGameEngine.h](Halloween_Game/olcConsoleGameEngine.h)
- Sprites:  
  - Wall: [Halloween_Game/wall2.spr](Halloween_Game/wall2.spr)  
  - Ghost: [Halloween_Game/ghost.spr](Halloween_Game/ghost.spr)  
  - Bullet: [Halloween_Game/bullet.spr](Halloween_Game/bullet.spr)  
  - Pumpkin (collectible / decorative): [Halloween_Game/pumpkin.spr](Halloween_Game/pumpkin.spr)

## Core Classes & Key Engine Routines
Game derives from [`olcConsoleGameEngine`](Halloween_Game/olcConsoleGameEngine.h) and overrides `OnUserCreate()` & `OnUserUpdate()` inside [`Halloween_Game`](Halloween_Game/Halloween_Game.cpp).

Frequently used engine APIs:
- Console setup: [`olcConsoleGameEngine::ConstructConsole`](Halloween_Game/olcConsoleGameEngine.h)
- Main loop start: [`olcConsoleGameEngine::Start`](Halloween_Game/olcConsoleGameEngine.h)
- Primitive rendering: [`olcConsoleGameEngine::Draw`](Halloween_Game/olcConsoleGameEngine.h), [`olcConsoleGameEngine::DrawLine`](Halloween_Game/olcConsoleGameEngine.h), [`olcConsoleGameEngine::FillTriangle`](Halloween_Game/olcConsoleGameEngine.h)
- Sprites: [`olcConsoleGameEngine::DrawSprite`](Halloween_Game/olcConsoleGameEngine.h), [`olcConsoleGameEngine::DrawPartialSprite`](Halloween_Game/olcConsoleGameEngine.h)
- Input: [`olcConsoleGameEngine::GetKey`](Halloween_Game/olcConsoleGameEngine.h)
- Timing: fElapsedTime passed into `OnUserUpdate`
- Depth buffer & ray casting implemented in the game loop in [Halloween_Game/Halloween_Game.cpp](Halloween_Game/Halloween_Game.cpp)

## Gameplay
Objective: Eliminate all ghosts (they disappear when hit). If a ghost reaches you (very close distance check) you lose.

Win condition: All entities using the ghost sprite removed → message "You Won!".  
Lose condition: Ghost proximity → message "You Died!".

Entities (Thing struct) hold position, velocity, sprite, and visibility.

## Controls (defaults inferred)
- W / S: Move forward / backward
- A / D: Strafe left / right
- Left / Right (likely): Rotate view (standard pattern with this engine)
- Space: Fire bullet (creation logic uses a key press check for a single-shot insert)
- M (likely toggle): Show 2D overhead map (controlled by boolean `bMap`)
(If a key appears unresponsive, verify mapping in [Halloween_Game/Halloween_Game.cpp](Halloween_Game/Halloween_Game.cpp) and adjust.)

## Ray Casting Overview
For each screen column:
1. Compute ray angle relative to player angle (`fPlayerA`) and field of view (`fFOV`).
2. Step forward incrementally until wall cell (`#`) or max depth (`fDepth`).
3. Determine wall slice height from distance, store in `fDepthBuffer`.
4. Sample wall sprite horizontally (`fSampleX`) based on which face was hit.
5. Draw ceiling (blank), wall (sampled glyph & colour), and floor (solid colour).

Sprites (ghosts, bullets, pumpkins) are projected afterward:
- Translate into camera space
- Angle test: within `fFOV / 2`
- Scaled by distance, clipped against `fDepthBuffer` to ensure proper occlusion.

## Build & Run
### Visual Studio
1. Open [Halloween_Game.sln](Halloween_Game.sln)
2. Ensure Character Set = Use Unicode (engine requires it)
3. Build (Debug x64 or Win32)
4. Run (console opens at 360x240 characters, font 4x4 set in `main`)

### Command Line (Developer Command Prompt)
```
cl /EHsc /std:c++17 Halloween_Game\Halloween_Game.cpp /Fe:Halloween_Game.exe /DUNICODE /D_UNICODE winmm.lib
```

## Changing Resolution
Edit the call in `main` inside [Halloween_Game/Halloween_Game.cpp](Halloween_Game/Halloween_Game.cpp):
```
game.ConstructConsole(360, 240, 4, 4);
```
Arguments: width, height (chars), font width, font height (pixels). Larger font sizes reduce effective pixel resolution but increase legibility. Keep within limits enforced by [`olcConsoleGameEngine::ConstructConsole`](Halloween_Game/olcConsoleGameEngine.h).

## Assets
`.spr` files are custom serialized sprite sheets loaded via the `olcSprite` loader. Sampling for textured walls uses:
- [`olcSprite::SampleGlyph`](Halloween_Game/olcConsoleGameEngine.h)
- [`olcSprite::SampleColour`](Halloween_Game/olcConsoleGameEngine.h)

## Extending
Ideas:
- Add sound via `EnableSound()` then load/play with [`olcConsoleGameEngine::LoadAudioSample`](Halloween_Game/olcConsoleGameEngine.h) and [`olcConsoleGameEngine::PlaySample`](Halloween_Game/olcConsoleGameEngine.h)
- Add doors: modify map string (`map` in `OnUserCreate`) and add interaction key
- Animated sprites: vary sample offsets with time
- Mini-map enhancements: additional symbols, player facing arrow

## Known Constraints
- Windows-only (WinAPI + `winmm.lib`)
- Unicode console required
- Fixed timestep not enforced (frame time used directly)

## Troubleshooting
- Console size error: lower resolution or increase font size (engine checks maximum via WinAPI).
- Garbled sprites: confirm `.spr` relative paths used in `OnUserCreate()`.
- Input lag: run in Release build.

## License & Attribution
The engine code in [Halloween_Game/olcConsoleGameEngine.h](Halloween_Game/olcConsoleGameEngine.h) follows the OneLoneCoder / Javidx9 license terms (attribution required). Retain original header notices. Game-specific logic in [Halloween_Game/Halloween_Game.cpp](Halloween_Game/Halloween_Game.cpp) may be adapted freely; ensure continued attribution of the engine.

Attribution example (retain in distributions):
"Built with the OneLoneCoder Console Game Engine by Javidx9."

## Quick Start Snippet
```
int main() {
    HalloweenGame game;
    game.ConstructConsole(360,240,4,4);
    game.Start();
    return 0;
}
```

## Contact / Source Reference
Original engine author: Javidx9 (YouTube / GitHub links in engine header). This project adapts that single-header engine with a themed ray casting game loop.

Enjoy hacking it.