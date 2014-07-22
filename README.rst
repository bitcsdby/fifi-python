===========
fifi-python
===========

This repository contains high-level Python bindings for the Fifi Finite Field
library.

How to Get It
=============
To get the Python bindings, you can either build them from source or download
a prebuilt version from `here`_, or simply get it from pip:

.. image:: https://badge.fury.io/py/fifi.svg
    :target: http://badge.fury.io/py/fifi


.. _here: http://bongo.steinwurf.dk/files/bin/fifi-python


Requirements
============

Depending on your platform, you'll need the following to build fifi-python.

Besides the requirements below, you'll need a recent c++ compiler.
The compilers used by Steinwurf is listed on the `buildbot page`_.

.. _buildbot page: http://buildbot.steinwurf.dk

Linux
-----
You'll need the the Python development headers to build fifi-python. These can
be acquired using your distro's package manager.

On Ubuntu and Debian, you can install the Python development package like this::

    sudo apt-get install libpython-dev

If you are using Python 3.x, then use this package instead::

    sudo apt-get install libpython3-dev

Mac
---

The default installation of python which exists on OSX doesn't include the
python development header, which is required for fifi-python.
Therefore you'll need to install python, e.g. using MacPorts.
When you have acquired python use that installation of python to execute the
waf commands.

Windows
-------

After installing a 32-bit Python and Visual Studio 2013, set the following
environment variable so that Python distutils can detect the new compiler::

  VS90COMNTOOLS=C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\Tools\

How to Build It
===============

fifi-python can be built like any other Steinwurf project::

  python waf configure
  python waf build
