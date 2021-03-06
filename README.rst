fifi-python
===========

fifi-python contains a set of high-level Python bindings for the `Fifi
<https://github.com/steinwurf/fifi>`_ finite field C++ library. The
bindings provide access to the arithmetic operations provided by Fifi. The
examples folder provides sample applications showing the usage of the
Python API.

.. image:: http://buildbot.steinwurf.dk/svgstatus?project=fifi-python
    :target: http://buildbot.steinwurf.dk/stats?projects=fifi-python
    :alt: Buildbot status
.. image:: https://badge.fury.io/py/fifi.svg
    :target: http://badge.fury.io/py/fifi
.. image:: https://pypip.in/download/fifi/badge.svg
    :target: https://pypi.python.org/pypi/fifi
    :alt: Downloads
.. image:: https://pypip.in/py_versions/fifi/badge.svg
    :target: https://pypi.python.org/pypi/fifi
    :alt: Supported Python versions
.. image:: https://pypip.in/format/fifi/badge.svg
    :target: https://pypi.python.org/pypi/fifi
    :alt: Download format
.. image:: https://pypip.in/license/fifi/badge.svg
    :target: https://pypi.python.org/pypi/fifi
    :alt: License

.. contents:: Table of Contents:
   :local:

License
-------

A valid license is required if you wish to use and install this library. Please
request a license by filling out the license request form_.

This project is available under a research- and education-friendly license,
see the details in the `LICENSE.rst file
<https://github.com/steinwurf/fifi-python/blob/master/LICENSE.rst>`_.

.. _form: http://steinwurf.com/license/

If you have any questions or suggestions about this library, please contact
us at our developer mailing list (hosted at Google Groups):

* http://groups.google.com/group/steinwurf-dev

Installation
------------

We provide a `pip
<http://en.wikipedia.org/wiki/Pip_%28package_manager%29>`_ package for the
easy installation of the fifi-python library.

To install this you'll need python and pip installed:

- To install Python `go here <https://www.python.org/downloads/>`_.
- To install pip `follow this guide <https://pip.pypa.io/en/latest/installing.html>`_.

You will need a set of tools and packages to build the library.

On all platforms, you will need a recent C++11 compiler.
The compilers used by Steinwurf are listed on our
`buildbot page <http://buildbot.steinwurf.com>`_.

In the following we provide platform specific installation instructions.

Linux
.....

These steps may not work with your specific Linux distribution, but they may
guide you in the right direction.

First, acquire the required packages from your package management system::

  sudo apt-get update
  sudo apt-get install python git build-essential libpython-dev

If you are using Python 3, you'll need to install ``libpython3-dev`` instead.

When you are ready to install the package, you can simply type::

  sudo pip install fifi

Mac OSX
.......

Follow `this guide
<https://help.github.com/articles/set-up-git#setting-up-git>`_ to install git.

Install the latest XCode and Command-line Tools from the Mac App Store.

When you are ready to install the package, you can simply type::

  sudo pip install fifi

Windows
.......

Install Python 2.7 (32-bit) and Visual Studio Express 2013 for Windows Desktop.
Then set the ``VS90COMNTOOLS`` environment variable to::

  C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\Tools\

so that Python distutils can detect your new compiler.

To enable the use of pip from the command line, ensure that the ``Scripts``
subdirectory of your Python installation is available on the system ``PATH``.
(This is not done automatically.)

When you are ready to install the package, you can simply type::

  pip install fifi

Building From Source
--------------------

You can also build the bindings from source, if you don't want to use pip.

Before doing anything, please install the requirements specified in
the previous section (you can ignore the parts about pip).

After that you can clone the project::

  git clone git@github.com:steinwurf/fifi-python.git

Configure and build the project::

  cd fifi-python
  python waf configure
  python waf build

Now the project is built and you should be able to find the resulting
``fifi.so`` or ``fifi.pyd`` file here (the actual path and extension is
dependent on your OS and Python version)::

  build/linux/src/fifi_python/fifi.so
  build/darwin/src/fifi_python/fifi.dylib
  build/win32/src/fifi_python/fifi.pyd

To use the bindings in your Python project you can do the following:

Using `PYTHONPATH` 
..................

You can add the ``build/platform/src/fifi_python/`` path to your ``PYTHONPATH`` 
and import the module in your Python script::

  >>> import fifi

Copy the bindings to your project
.................................

Another option is to copy the built bindings e.g. ``build/linux/src/fifi_python/fifi.so``
(for Linux) to your project directory. As an example if your script is stored in
``/path/to/hello.py``, then copy the bindings to ``/path/to/fifi.so`` and you should be
able to ``import fifi`` from within the ``hello.py`` script.
