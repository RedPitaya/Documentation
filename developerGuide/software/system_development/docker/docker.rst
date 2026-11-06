.. _SW_build_docker:

###################################
Build Red Pitaya with Docker images
###################################

This guide explains how to build and use Docker images for developing Red Pitaya OS components. Docker images
provide a portable, reproducible alternative to setting up a native Ubuntu host with ``schroot`` (as described in
:ref:`Build Red Pitaya ecosystem <SW_build_ecosystem>`).

.. contents:: Table of Contents
    :local:
    :depth: 1
    :backlinks: top

|

1. Introduction
*****************

The Red Pitaya source repository provides a ``docker`` directory with build definitions for several containerized
tools:

.. list-table::
    :header-rows: 1
    :widths: 25 75

    * - Directory
      - Purpose
    * - ``docker/vivado_2025.1``
      - Builds a Vivado/Vitis Docker image used for headless FPGA synthesis and implementation
    * - ``docker/ecosystem``
      - Uses the Vivado image above to build the complete Red Pitaya ecosystem
    * - ``docker/streaming``
      - Builds a multi-platform Python environment used to build the Red Pitaya streaming client

.. note::

    This page currently covers the Vivado image build in detail. The ecosystem and streaming images are summarized
    briefly below and will be expanded in future updates.

|


.. _SW_docker_vivado:

2. Building the Vivado Docker image
**************************************

This image (``vivado:2025.1``) packages the AMD Vitis Unified Software Platform (Vivado) for headless use, e.g. in
CI/CD pipelines for FPGA synthesis and development.

2.1. Requirements
===================

Building the full image requires approximately **600 GB** of free disk space:

* Roughly 120 GB for unpacking the Vivado installer archive
* Around 450 GB for building the Docker image

Once the build finishes, the temporary files can be deleted, bringing the final image size down to about 150 GB.

|

2.2. Build preparation
========================

1.  **Download the code**

    Clone the :rp-github:`Red Pitaya repository <RedPitaya>` and locate the ``docker/vivado_2025.1`` directory:

    .. code-block:: shell-session

        git clone https://github.com/RedPitaya/RedPitaya

    .. note::

        As of currently, the :rp-github:`unify/dev branch <RedPitaya/tree/unify/dev>` holds the most up-to-date build scripts and 
        Dockerfiles. Until the unify/dev branch is merged into main, it is recommended to use unify/dev for building the Vivado image.

        .. code-block:: shell-session

            git clone -b unify/dev https://github.com/RedPitaya/RedPitaya

2.  **Install Docker**

    Install `Docker <https://docs.docker.com/get-started/>`_ or its desktop variant (Docker Desktop).

3.  **Configure an external disk (optional)**

    If you want to build the image on an external disk:

    * **Linux** - Adjust the Docker and containerd services to enable building on an external drive
    * **Windows** - In Docker Desktop, open **Settings** > **Resources** > **Advanced** and change the **Disk image
      location** path to the external disk. This moves the image build location from the system drive to the
      external drive.

    .. figure:: img/Docker_image_location.png
        :alt: Docker Desktop disk image location
        :align: center

4.  **Obtain the Vivado installer files**

    Download the Vivado/Vitis installer from the official AMD (formerly Xilinx) website. Current Red Pitaya OS
    releases require **Vitis 2025.1**.

5.  **Extract the installer**

    Create a directory named ``vivado_installer`` inside the ``vivado_2025.1`` build directory, then extract the
    Vitis ``.tar`` image into it. Make sure the ``xsetup`` file is located directly inside ``vivado_installer`` -
    any intermediate folders will cause the build to fail:

    .. code-block:: shell-session

        # Create directory for the installer
        mkdir -p vivado_installer

        # Extract the archive (replace with actual filename)
        tar -xzf 3DFPGAs_AdaptiveSoCs_Unified_SDI_2025.1_0530_0145.tar -C vivado_installer

        # Verify the xsetup file exists
        ls -la vivado_installer/xsetup

6.  **Check the build directory**

    Ensure the following files/directories are all present in the same directory before building:

    .. code-block:: shell-session

        ls -la
        # Should see:
        # - install_config.txt
        # - Dockerfile.vivado
        # - vivado_installer/

|

2.3. Building the Docker image
===============================

.. note::

    The build process can take several hours depending on system performance. The resulting image is tagged as
    ``vivado:2025.1`` and can be used to build the Red Pitaya ecosystem or run Vivado in headless mode.

    Lack of space on the target disk or errors in the xsetup path will cause the build to fail. Check the output of the build process for any errors.

Basic build
-------------

.. code-block:: shell-session

    # Linux
    export DOCKER_BUILDKIT=1
    docker build -t vivado:2025.1 -f Dockerfile.vivado .

.. code-block:: shell-session

    :: Windows
    set DOCKER_BUILDKIT=1
    docker build -t vivado:2025.1 -f Dockerfile.vivado .

|

Build with platform specification
-----------------------------------

.. code-block:: shell-session

    # Linux - for AMD64 (x86_64)
    export DOCKER_BUILDKIT=1
    docker build --platform linux/amd64 -t vivado:2025.1 -f Dockerfile.vivado .

.. code-block:: shell-session

    :: Windows - for AMD64 (x86_64)
    set DOCKER_BUILDKIT=1
    docker build --platform linux/amd64 -t vivado:2025.1 -f Dockerfile.vivado .

|

Build without cache (clean build)
------------------------------------

.. code-block:: shell-session

    # Linux
    export DOCKER_BUILDKIT=1
    docker build --no-cache -t vivado:2025.1 -f Dockerfile.vivado .

.. code-block:: shell-session

    :: Windows
    set DOCKER_BUILDKIT=1
    docker build --no-cache -t vivado:2025.1 -f Dockerfile.vivado .

|

2.4. Configuration and build file overview
============================================

Vivado installation configuration (``install_config.txt``)
-------------------------------------------------------------

.. list-table::
    :header-rows: 1
    :widths: 20 40 40

    * - Parameter
      - Value
      - Description
    * - ``Edition``
      - Vitis Unified Software Platform
      - Software edition
    * - ``Destination``
      - ``/opt/Xilinx``
      - Installation path
    * - ``Modules``
      - ``Zynq-7000:1,DocNav:1``
      - Modules to install

The default configuration installs only **Zynq-7000** (SoC support) and **DocNav** (documentation). All other FPGA
families (Virtex, Kintex, Artix, etc.) are disabled.

.. note::

    If needed, uncomment the ``Modules`` line in ``install_config.txt`` and enable the required components by
    changing ``:0`` to ``:1``.

|

Dockerfile build details
-------------------------

The image is built in two stages:

.. list-table::
    :header-rows: 1
    :widths: 25 75

    * - Stage
      - Purpose
    * - ``builder``
      - Installs Vivado from the installer
    * - ``final``
      - Final image with minimal dependencies

The builder stage installs library compatibility packages (``libncurses6``, ``libtinfo6``, ``libstdc++6``,
``libc6-i386``), installer utilities (``python3``, ``python3-pip``), and CI/CD utilities (``openssh-server``,
``git``, ``curl``, ``locales``).

The final image sets the following environment variables:

.. code-block:: dockerfile

    ENV LANG=en_US.UTF-8 \
        LANGUAGE=en_US:en \
        LC_ALL=en_US.UTF-8
    ENV XILINX_VIVADO=/opt/Xilinx/2025.1/Vivado
    ENV PATH="${XILINX_VIVADO}/bin:${PATH}"

.. note::

    Docker BuildKit bind mounts (``--mount=type=bind``) used to copy the installer into the build container exist
    only during the execution of the ``RUN`` command and are automatically removed afterwards - no explicit
    ``umount`` is required.

|

Exporting and loading the image
---------------------------------

Export the built image to a compressed archive for transfer to another machine:

.. code-block:: shell-session

    # Export and compress in one step
    docker save vivado:2025.1 | gzip > vivado-2025.1.tar.gz

    # Maximum compression
    docker save vivado:2025.1 | gzip -9 > vivado-2025.1.tar.gz

On the target machine, load the image from the archive:

.. code-block:: shell-session

    gunzip -c vivado-2025.1.tar.gz | docker load

    # Verify
    docker images | grep vivado

|

2.5. Running the image
========================

.. code-block:: shell-session

    # Interactive run (debug/development mode)
    docker run -it --name vivado-dev -v "$(pwd)":/workspace vivado:2025.1

    # Run with explicit locale settings
    docker run -it -e LANG=en_US.UTF-8 -e LC_ALL=en_US.UTF-8 -e LANGUAGE=en_US:en vivado:2025.1

Verify that Vivado is working correctly inside the container:

.. code-block:: shell-session

    root@container:/# locale
    LANG=en_US.UTF-8
    LANGUAGE=en_US:en
    LC_ALL=en_US.UTF-8

    root@container:/# vivado -version

    root@container:/# echo $XILINX_VIVADO
    /opt/Xilinx/2025.1/Vivado

|

2.6. Troubleshooting
======================

.. list-table::
    :header-rows: 1
    :widths: 35 65

    * - Issue
      - Solution
    * - Locale error: ``cannot change locale (en_US.UTF-8)``
      - Ensure the ``locales`` package and locale generation are included in the Dockerfile, or specify locale
        variables at runtime with ``-e LANG=en_US.UTF-8 -e LC_ALL=en_US.UTF-8``
    * - ``libtinfo.so.5: cannot open shared object file``
      - Missing symbolic links to libraries; check with
        ``docker run --rm vivado:2025.1 ls -la /lib/x86_64-linux-gnu/libtinfo.so*``
    * - Vivado installer not found during build
      - Verify the directory structure - ``vivado_installer/xsetup`` must exist and be executable
        (``chmod +x vivado_installer/xsetup``)
    * - Vivado won't start (X server required)
      - Run Vivado in batch or Tcl mode instead of GUI mode: ``vivado -mode batch -source script.tcl``
    * - Insufficient memory during synthesis
      - Increase container memory limits: ``docker run --memory="16g" --memory-swap="16g" ...``
    * - TAR archive is too large
      - Clean the Docker build cache before exporting: ``docker system prune -a``, then use maximum
        compression (``gzip -9``)

|

3. Building the ecosystem with the Vivado image
**************************************************

The ``docker/ecosystem`` directory uses the Vivado image built above to assemble the complete Red Pitaya ecosystem
(FPGA bitstreams, kernel, boot files, API libraries, and web applications) without setting up a native Ubuntu host.

.. note::

    Building the ecosystem container requires approximately **350 GB** of additional free disk space, on top of
    the space used by the Vivado image.

Basic workflow:

1.  Build the Vivado image as described above (``docker build -t vivado:2025.1 -f Dockerfile.vivado .`` inside
    ``docker/vivado_2025.1``).
2.  Configure the FPGA repository source in ``docker/ecosystem/build.sh`` (or ``build.ps1`` on Windows) using the
    ``GIT_FPGA_CONFIG`` variable:

    * **Local repository** - point to an existing clone: ``GIT_FPGA_CONFIG="GIT_MODE=LOCAL GIT_LOCAL_PATH=/path/to/redpitaya-fpga"``
    * **Automatic download** - leave blank (``GIT_FPGA_CONFIG=""``) to let the script clone the FPGA repository
        from GitHub automatically.

3.  Run the build script from the ``docker/ecosystem`` directory:

    .. code-block:: shell-session

        # Linux
        chmod +x build.sh
        ./build.sh

    .. code-block:: powershell

        # Windows
        .\build.ps1

The build process can take several hours depending on system performance and produces the same
``ecosystem_*.zip`` output described in :ref:`Build Red Pitaya ecosystem <SW_build_ecosystem>`.

|

4. Building the streaming client with Docker
***********************************************

The ``docker/streaming`` directory builds an image used to compile the Red Pitaya streaming client for multiple
platforms and Python versions (3.9-3.13) in a single container, including native Linux (x86_64), cross-compiled
Linux ARM64, and cross-compiled Windows builds.

Build the image from the ``docker/streaming`` directory:

.. code-block:: shell-session

    ./build.sh

This tags the resulting image as ``rp-streaming``. The container can then be used to compile and package the
streaming client without installing multiple Python toolchains or cross-compilers on the host machine.
