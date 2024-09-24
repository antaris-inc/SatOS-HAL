# SatOS-HAL

This repository contains the SatOS(TM) hardware abstraction layer (HAL) and UHF specific SDR interfaces, which has been developed by [Antaris, Inc](https://antaris.space).
This abstracts individual satellite components for use by SatOS flight software.

Please engage with the maintainers here through issues and pull requests.
If you would like to reach out directly, feel free to send a message to opensource@antaris.space

This software has been developed by Antaris, Inc and released under the [APACHE 2.0 license](./LICENSE).
It is provided without any guarantee or warranty, and you may use it at your own risk.

Some other open source components have been used within this project. Their licenses are embedded within this repo
alongside the open source code.

## UHF SDR Support

This repository includes full SW support for satellite communications via UHF SDR modules.
This may be used to interface any OBC with any UHF radio, provided the necessary abstraction layer is implemented.
Key features include:
* Periodic UHF beacon transmission
* Periodic UHF health metric retrieval and transmission
* APIs for beacon content/period customization
* Extensible TC & TM framework
* Back door socket (used to facilitate development)

Onboard computer (OBC) support is available for:
* STM32 dev kit (discovery board)
* [Antaris Core OBC](https://github.com/antaris-inc/Satellite-Design-Library?tab=readme-ov-file#core-board-gen-1)
* Generic x86 Platform

Tested operating systems include FreeRTOS, CentOS and Ubuntu.

Please find comprehensive documentation here: [SatOS UHF SDR Guide](<./docs/SatOS UHF User Guide.pdf>).

### OpenLST

The [OpenLST SDR](https://github.com/openlst/openlst) is fully supported here is completey open source (software and hardware).
This flight qualified system is highly recommended for anyone considering a UHF radio for their satellite mission.

## Documentation

Docs are automatically built from the source and published using Github Pages.
The latest docs are always available here: https://antaris-inc.github.io/SatOS-HAL/.

You may build the docs locally with `doxygen`.
On an Ubuntu 22.04 machine, you can easily `apt install doxygen` then `doxygen Doxyfile` to produce them yourself.

## Build Process

The build process is supported on Ubuntu 22.04 x86_64:

1. First, install system dependencies: `apt install bzip2 make g++ libjansson-dev`

2. Download the appropriate ARM toolchain from https://developer.arm.com/downloads/-/gnu-rm. Specific toolchain in use
   is `arm-none-eabi-gcc` at version `9-2020-q2-update`.

3. Unpack the ARM toolchain into /usr/share: `tar -C /usr/share -xf gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux.tar.bz2`

4. Add the downloaded toolchain to your PATH: `export PATH=/usr/share/gcc-arm-none-eabi-9-2020-q2-update/bin/:$PATH`

5. Run `make all`

Note that this is documented in the CI process artifacts, so they are also good references.
