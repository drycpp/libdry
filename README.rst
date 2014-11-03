***********************************
libdry++: Data structures for C++14
***********************************

.. image:: https://api.travis-ci.org/dryproject/libdry.svg?branch=master
   :target: https://travis-ci.org/dryproject/libdry
   :alt: Travis CI build status

.. image:: https://scan.coverity.com/projects/3233/badge.svg
   :target: https://scan.coverity.com/projects/3233
   :alt: Coverity Scan build status

Build Prerequisites
===================

* Clang_ (>= 3.2) or GCC_ (>= 4.8)
* Autoconf_ (>= 2.68)
* Automake_ (>= 1.11)
* Libtool_ (>= 2.2)

.. note::

   Older releases may work, but are not actively tested for.

.. _Clang:    http://clang.llvm.org/
.. _GCC:      http://gcc.gnu.org/
.. _Autoconf: http://www.gnu.org/software/autoconf/
.. _Automake: http://www.gnu.org/software/automake/
.. _Libtool:  http://www.gnu.org/software/libtool/

Installation
============

Installation on Unix
--------------------

::

   $ ./autogen.sh
   $ ./configure
   $ make
   $ sudo make install

Elsewhere
=========

Author
======

This project is part of the `DRY <http://dryproject.org/>`_ initiative.

* `Arto Bendiken <https://github.com/bendiken>`_ - http://ar.to/

Donations
=========

If you found this software useful and would like to encourage its
maintenance and further development, please consider making a $5 donation
to the author(s) via Gratipay_ or Bitcoin_.

.. _Gratipay: https://gratipay.com/bendiken/
.. _Bitcoin:  bitcoin:1P5GPsDXAM8tr1cqQ1J7jStwfjeovDUh77?label=libdry.org&message=Donation

License
=======

This is free and unencumbered public domain software. For more information,
see http://unlicense.org/ or the accompanying ``UNLICENSE`` file.
