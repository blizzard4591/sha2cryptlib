# sha2cryptlib
A cross-platform wrapper around the SHA2-CRYPT implementation by Ulrich Drepper.

# Content
This package consists of several parts:
 - a simple console utility which calculates SHA256-CRYPT and SHA512-CRYPT hashes of user-supplied passwords, like "doveadm pw -s",
 - the tests as written by Ulrich Drepper for his implementations, but cross-platform compileable,
 - a C interface to the implementation by Ulrich Drepper,
 - a C++ interface to the implementation by Ulrich Drepper,
 - and the implementations of SHA256 and SHA512 by Ulrich Drepper, remodeled to also run under Windows.

# Build and Installation
Use CMake to configure.
Options available:
 - SHA2CRYPTLIB_OPTION_BUILD_SHARED_LIBS: ON/OFF option to select whether to target SHARED or STATIC libraries.

There is an INSTALL target available, which takes all binaries and necessary header files to the chosen location.

# Credits
Most of the implementation is, as mentioned before, from Ulrich Drepper (http://www.akkadia.org/drepper/SHA-crypt.txt).
He placed his work under Public Domain.
Additionally this library uses Mathias Panzenböck's "portable_endian.h", an (almost) portable implementation of <endian.h>.
 
