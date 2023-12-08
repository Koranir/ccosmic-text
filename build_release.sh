cargo build --release
cp target/release/libccosmic_text.so target/lib/libccosmic_text.so
cbindgen -c cbindgen.toml --cpp-compat --crate ccosmic-text -l c -o target/lib/ccosmic_text.h --profile release
