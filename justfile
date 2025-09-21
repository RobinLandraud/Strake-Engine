set windows-shell := ["powershell.exe", "-Command"]
set shell := ["sh", "-c"]

set dotenv-load := true
vcpkg := env_var_or_default("VCPKG_PATH", "C:/dev/vcpkg")

###########################
# Linux specific commands #
###########################

# allow to run clang-format on all files
[unix]
format:
    - find . -type f -name "*.cpp" -o -name "*.h" | xargs clang-format -i

# run clang-tidy on all files
[unix] 
tidy:
    - run-clang-tidy -p="./build" -header-filter="^(?!.*third_party).*"

# build the project as release
[unix]
build:
    - mkdir -p ./build && rm -rf ./build/* && cd build && cmake .. -GNinja -DCMAKE_BUILD_TYPE=Release && ninja && cd ..

# build the project as debug
[unix]
build-debug:
    - mkdir -p ./build && rm -rf ./build/* && cd build && cmake .. -GNinja -DCMAKE_BUILD_TYPE=Debug && ninja && cd ..

#############################
# Windows specific commands #
#############################

# install dependencies with vcpkg
[windows]
install:
    - powershell.exe -Command "{{ vcpkg }}/vcpkg.exe install glfw3 glm glew assimp"


# build the project as release
[windows]
build:
    - powershell.exe -Command "if (-Not (Test-Path ./build)) { New-Item -ItemType Directory -Path ./build }; Remove-Item -Recurse -Force ./build/*; cd build; cmake .. -A x64 -DCMAKE_TOOLCHAIN_FILE='{{ vcpkg }}'; cmake --build . --config Release; cd .."


# build the project as debug
[windows]
build-debug:
    - powershell.exe -Command "if (-Not (Test-Path ./build)) { New-Item -ItemType Directory -Path ./build }; Remove-Item -Recurse -Force ./build/*; cd build; cmake .. -A x64 -DCMAKE_TOOLCHAIN_FILE='{{ vcpkg }}'; cmake --build . --config Debug; cd .."