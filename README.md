# json_to_protobuf
Json file to protobuf and protobuf to json file helper class and example. This reads in an example_config.json file, convert to a protobuf object, and print the ShortDebugString() output of the protobuf. This then modifies the protobuf and creates a output.json file

# Visual Studio Code setup help
# Prerequisites: 
The tasks.json is setup for mac os where boost and google::protobufs have been installed
- Google Protobuf version https://github.com/protocolbuffers/protobuf/releases/download/v21.9/protobuf-cpp-3.21.9.tar.gz
- See https://developers.google.com/protocol-buffers/docs/cpptutorial for more details on installing and working with protobufs
- Boost install via Brew formula 'brew install boost' see https://formulae.brew.sh/formula/boost 
# vscode settings.json
Adding the boost include directory to vscode settings.json will clear up any intellisense issues
- "C_Cpp.default.includePath": ["/opt/homebrew/Cellar/boost/1.80.0/include/"]

# Building
Step 1. Run the "Build protobuf code" task. On mac shift+command+p -> run task -> select "Build protobuf code"
Step 2. Run the "Build All" task. On mac shift+command+b select "Build All"

