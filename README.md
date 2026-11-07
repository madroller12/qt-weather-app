# Weather Desktop Pro (Qt C++)

A modern, responsive desktop weather application built with C++17 and Qt Framework. Features real-time weather monitoring, 5-day forecasts, IP-based geolocation, multi-language support, and a clean iOS-inspired dark UI.

## Key Features

- **Multi-Language Support (i18n):** Instant UI localization supporting 4 languages (Ukrainian, English, Italian, Russian).
- **Current Weather & Metrics:** Real-time temperature, "feels like" status, humidity, wind speed, and atmospheric pressure.
- **5-Day Weather Forecast:** Vertical scrollable daily forecast list powered by OpenWeatherMap API.
- **IP Geolocation:** Quick auto-detection of user location at the click of a button.
- **Modern Responsive UI:** Glassmorphism-style dark layout with dynamic window resizing and responsive controls.

## Tech Stack

- **Language:** C++17
- **Framework:** Qt 6 (QtWidgets, QtNetwork)
- **API:** OpenWeatherMap REST API (JSON parsing)
- **Build System:** qmake / CMake

## Project Structure

```text
├── main.cpp                # Application entry point
├── mainwindow.cpp          # UI layout logic, API handlers & i18n
├── mainwindow.h            # Main window class interface
├── mainwindow.ui           # Base Qt Designer layout definition
├── qt-weather-app.pro      # Qt qmake project configuration
├── .gitignore              # Git build artifact exclusions
└── README.md               # Project documentation
```

## How to Build & Run

### Prerequisites
- Qt SDK (version 6.x or 5.15+) with MinGW / MSVC compiler toolchain.

### Build Steps
1. Clone the repository:
```bash
git clone https://github.com/madroller12/qt-weather-app.git
```
2. Open `qt-weather-app.pro` in **Qt Creator**.
3. Select your Desktop Kit configuration.
4. Build and run the project (`Ctrl + R`).

## Standalone Executable Download

To run the application without installing Qt SDK, download the pre-packaged standalone binary from the **[Releases](../../releases)** page.