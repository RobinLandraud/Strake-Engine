set windows-shell := ["powershell.exe", "-Command"]
set shell := ["sh", "-c"]
vcpkg := "C:/Users/robin/Documents/Prog/Strake-Engine/vcpkg"

build:
    - mkdir -p ./build && rm -rf ./build/* && cd build; cmake .. -GNinja; ninja; cd ..
build-windows:
    - powershell.exe -Command "if (-Not (Test-Path ./build)) { New-Item -ItemType Directory -Path ./build }; Remove-Item -Recurse -Force ./build/*; cd build; cmake .. -GNinja -DVCPKG_ROOT='{{ vcpkg }}'; ninja; cd .."
format:
    - find . -type f -name "*.cpp" -o -name "*.h" | xargs clang-format -i
build-prod:
    - mkdir -p ./build && rm -rf ./build/* && cd build && cmake .. -GNinja -DCMAKE_BUILD_TYPE=Release && ninja && cd ..    
tidy:
    - run-clang-tidy -p="./build" -header-filter="^(?!.*third_party).*"