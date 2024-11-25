build:
    - mkdir -p ./build && rm -rf ./build/* && cd build; cmake .. -GNinja; ninja; cd ..
format:
    - find . -type f -name "*.cpp" -o -name "*.h" | xargs clang-format -i
build-prod:
    - mkdir -p ./build && rm -rf ./build/* && cd build && cmake .. -GNinja -DCMAKE_BUILD_TYPE=Release && ninja && cd ..    
tidy:
    - run-clang-tidy -p="./build" -header-filter="^(?!.*third_party).*"