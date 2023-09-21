#ifndef __CLI_ENGINE__
#define __CLI_ENGINE__
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "colors.h"
#include "canvas.h"
#include "characters.h"
#include "utils/util.h"
#include "shapes/shapes.h"

Canvas* InitWindow(int width, int height, const char *title);  // Initialize window and OpenGL context
bool WindowShouldClose(void);                               // Check if KEY_ESCAPE pressed or Close icon pressed
void CloseWindow(void);                                     // Close window and unload OpenGL context
bool IsWindowReady(void);                                   // Check if window has been initialized successfully
bool IsWindowFullscreen(void);                              // Check if window is currently fullscreen
bool IsWindowHidden(void);                                  // Check if window is currently hidden (only PLATFORM_DESKTOP)
bool IsWindowMinimized(void);                               // Check if window is currently minimized (only PLATFORM_DESKTOP)
bool IsWindowMaximized(void);                               // Check if window is currently maximized (only PLATFORM_DESKTOP)
bool IsWindowFocused(void);                                 // Check if window is currently focused (only PLATFORM_DESKTOP)
bool IsWindowResized(void);                                 // Check if window has been resized last frame
bool IsWindowState(unsigned int flag);                      // Check if one specific window flag is enabled
void SetWindowState(unsigned int flags);                    // Set window configuration state using flags (only PLATFORM_DESKTOP)
void ClearWindowState(unsigned int flags);                  // Clear window configuration state flags
void ToggleFullscreen(void);                                // Toggle window state: fullscreen/windowed (only PLATFORM_DESKTOP)
void ToggleBorderlessWindowed(void);                        // Toggle window state: borderless windowed (only PLATFORM_DESKTOP)
void MaximizeWindow(void);                                  // Set window state: maximized, if resizable (only PLATFORM_DESKTOP)
void MinimizeWindow(void);                                  // Set window state: minimized, if resizable (only PLATFORM_DESKTOP)
void RestoreWindow(void);                                   // Set window state: not minimized/maximized (only PLATFORM_DESKTOP)

#endif