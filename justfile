build:
    - rm -f Ghost && mkdir -p ./build && rm -rf ./build/* && cd build; cmake .. -GNinja; ninja; cd ..
format:
    - find . -type f -name "*.cpp" -o -name "*.h" | xargs clang-format -i
build-prod:
    - rm -f Ghost && mkdir -p ./build && rm -rf ./build/* && cd build && cmake .. -GNinja -DCMAKE_BUILD_TYPE=Release && ninja && cd ..    
tidy:
    - clang-tidy -p="./build" main.cpp -header-filter=.*