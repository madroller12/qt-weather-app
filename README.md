# Qt C++ Weather Forecast Application (Standalone Release)

A portable desktop weather application built using C++ and the Qt Framework that connects to an external Web API to fetch and display real-time weather data.

## Description
This application demonstrates GUI development in Qt, network programming, and API integration. It requests current weather parameters for a selected city, parses the JSON response, and displays a short text description alongside core weather metrics.

The key feature of this repository is its standalone portability. The application has been fully deployed with all required dependencies, meaning it can be executed immediately on any compatible Windows machine without requiring the Qt Framework or Qt Creator to be installed locally.

## Project Specifications & Build Quirks
- **UI Localization:** The user interface and weather descriptions are currently localized in Ukrainian.
- **Executable Name:** Due to the initial project template configuration, the pre-compiled binary is named `Flappy_bird.exe`. This is purely a build artifact and does not affect the core weather functionality.

## Tech Stack
- C++
- Qt Framework (QtWidgets, QtNetwork)
- JSON (for API response parsing)

## How to Run
1. Clone or download this repository to your computer.
2. Open the `release` directory.
3. Run the `Flappy_bird.exe` file to launch the application instantly.
