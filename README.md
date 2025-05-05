# Jacs Air Quality app
This is app for checking air quality in cities in Poland. Data is provided by [Główny Inspektora Ochrony Środowiska (GIOŚ)](https://powietrze.gios.gov.pl/pjp/home) and fetched from their [API](https://api.gios.gov.pl/pjp-api/swagger-ui/) (Inconsistency in file naming comes from writing app in QtCreator which does not do any capitalization in filename and the coming to Clion which handles filenames as you would expect)
## Features
- Fetching available stations details
- Fetching details of sensors for given station
- Fetching current sensor data
- Fetching historical sensor data
- Displaying sensor data on chart with information about: maximum value, minimum value, average value and trend
- Displaying location of stations on map for the selected city
- Finding nearest station to the users current location
## Documentation
For documentation head [here](hwtjac0.github.io/JAQ/) 
## Building
### Requirements
Project was developed and built on linux distro. There is a chance that 
it may build on windows without any issues.

Required packages are:
- Qt6 ^6.9
  - Core
  - Gui
  - Quick
  - Charts
  - Widgets
  - Location
  - Positioning
  - Test
- cmake
### Step-by-step
Follow these commands:
```
git clone https://github.com/HWTjac0/JAQ.git
cd JAQ
mkdir build
cd build
cmake .. -DBUILD_TESTING=ON
cmake --build .
```
## Tests
Tests are written using QtTest and are run with Ctest. You can find them 
in `Tests/` subdirectory.Basically after building the project and while still in `build/` 
subdirectory, simply run `ctest` or `ctest -V`. If you want to only build
tests instead of `cmake --build .` run `cmake --build . --target jaq_test`
