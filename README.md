# SatOS-HAL

This repository contains the SatOS(TM) hardware abstraction layer (HAL), which has been developed by [Antaris, Inc](https://antaris.space).
This abstracts individual satellite components for use by SatOS flight software.

Please engage with the maintainers here through issues and pull requests.
If you would like to reach out directly, feel free to send a message to opensource@antaris.space

This software has been developed by Antaris, Inc and released under the [APACHE 2.0 license](./LICENSE).
It is provided without any guarantee or warranty, and you may use it at your own risk.

Some other open source components have been used within this project. Their licenses are embedded within this repo
alongside the open source code.

## Documentation

Docs are automatically built from the source and published using Github Pages.
The latest docs are always available here: https://antaris-inc.github.io/SatOS-HAL/.

You may build the docs locally with `doxygen`.
On an Ubuntu 22.04 machine, you can easily `apt install doxygen` then `doxygen Doxyfile` to produce them yourself.

## Build Process

The build process is supported on Ubuntu 22.04 x86_64:

1. Download the appropriate ARM toolchain from https://developer.arm.com/downloads/-/gnu-rm. Specific toolchain in use
   is `arm-none-eabi-gcc` at version `9-2020-q2-update`.

2. Unpack the ARM toolchain into /usr/share: tar -C /usr/share gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux.tar.bz2

3. Add the downloaded toolchain to your PATH:

```
export PATH=/usr/share/gcc-arm-none-eabi-9-2020-q2-update/bin/:$PATH
```

4. Run `make all`

Note that this is documented in the CI process artifacts, so they are also good references.
