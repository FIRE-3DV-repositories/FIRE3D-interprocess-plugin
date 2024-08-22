# Sample Simulation plugin with AMBF 3.0

## Setup

### Install AMBF 3.0

Clone and compile AMBF 3.0 without ROS support

```
git clone git@github.com:LauraConnolly/ambf.git
cd ambf/core/
mkdir build && cd build
cmake ..
make -j8
```

Test installation
```
cd ambf/core/bin/lin-x86_64/
./ambf_simulator
```

### compile simple plugin

```
cd test-plugin
mkdir build && cd build
cmake ..
make -j8
```

Run ambf with plugin with
```
../ambf/core/bin/lin-x86_64/ambf_simulator --plugins build/libvolumetric_drilling.so
```
