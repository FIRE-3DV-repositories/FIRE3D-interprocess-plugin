# Vulkan Interprocess Plugin with AMBF 3.0

## Setup

### Install AMBF 3.0

Install ambf dependencies (Not sure if they are needed in Ubuntu 22.04)
```
sudo apt install libasound2-dev libgl1-mesa-dev xorg-dev
```
Clone and compile AMBF 3.0 without ROS support

```
git clone git@github.com:LauraConnolly/ambf.git
git checkout ros2-support
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
cd vulkan-interprocess-plugin
mkdir build && cd build
cmake ..
make -j8
```

Run ambf with plugin with
```
../ambf/core/bin/lin-x86_64/ambf_simulator --plugins build/libvulkan_interprocess.so
```
