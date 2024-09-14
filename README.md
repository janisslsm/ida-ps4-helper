# IDA PS4 Helper

This is a helper plugin intended for [ps4-module-loader](https://github.com/SocraticBliss/ps4_module_loader)

# Building

You'll need to set IDASDK in environment variables before running these commands. This is for IDA 9.0 specifically, you might have to adapt these commands for older versions.
```
cmake -B build -DEA64=1 -DCMAKE_BUILD_TYPE=RelWithDebInfo  .
cmake --build .
```

# Credits
[allthingsida](https://github.com/allthingsida/allthingsida/) for the [base plugin](https://github.com/allthingsida/allthingsida/) to add functions to IDAPython API via C++.
