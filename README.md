# quick-format-string
A header-only library to 
- quickly create formatted strings via builder pattern to produce a ```std::string```
- act as a character or byte buffer with extra functionality for use in various areas

### How to use
QFString is a templated class containing two parameters: 
1. ```N``` - the maximum number of ```char_t``` to store
2. ```char_t``` - the character type to store

Every QFString is guaranteed to be null terminated, meaning the maximum capacity is given by:
```N - 1```

```cpp
// 32 byte maximum buffer to format string into
std::string str = QFString<32>::create("Today is %s", "Friday");
```
Is equivalent to the following code
```cpp
// More explicit way to format string, works in builder pattern (xvalues)
std::string str = QFString<64>().format("Today is %s", "Friday").string();
// and lvalues that are reused throughout an application
QFString buffer;
buffer.format("[%s] %s.csv", "*", "File32");
/*...Program logic...*/
buffer.format("[%s] %s.txt", "+", "File64");
// ...
auto str1 = buffer.string();
auto str2 = std::string(buffer.c_str());
```

QFString also can works as a character buffer of a fixed size N. Which may be useful in applications like user interfaces like ImGui...
```
/*Buffer to use to store the text input*/
QFString<64> buffer{};
if (ImGui::InputText("Text Input"
  , buffer.max_size()
  , buffer.capacity())) {
    std::cout 
      << "User Entered: " 
      << std::quoted(buffer.c_str()) 
      << std::endl;
}
```
... or in receiving and sending Serial messages between devices of known or limited size.
```cpp
int socket; /*... Socket boilerplate ...*/
QFString<64> message{};
ssize_t valread = read(socket, message.c_str(), message.max_size());
std::cout 
  << QFString::create("Received %i bytes: %s"
    , message.size()
    , message.c_str()
  ).string() 
  << std::endl;
```

### Building
Use the following set of commands to clone the repo then build and test the source code.
```bash
git clone <quick-format-string>
cd quick-format-string
git submodule update --init --recursive
mkdir build
cd build
cmake ..
make
ctest
```