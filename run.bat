cmake -B build -DCMAKE_BUILD_TYPE=Release -DVCPKG_TARGET_TRIPLET="x64-windows" -DCMAKE_TOOLCHAIN_FILE="C:/vcpkg/scripts/buildsystems/vcpkg.cmake"
cmake --build build