# DLL to LIB Converter

This tool converts DLL files to LIB files by first generating a `.def` file and then using Visual Studio tools to generate the `.lib` file.

## Prerequisites

- Windows operating system.
- MSVC Build Tools installed and properly configured in the system's PATH. Specifically, you'll need `dumpbin` and `lib.exe` from Visual Studio.

## How to Use

1. Download and extract the source code or the precompiled `.exe`.
2. If you're using the source code, compile it using Visual Studio or MinGW.
3. Run the executable, and it will prompt you to select a DLL file.
4. The tool will create a `.def` file and then use Visual Studio's `lib.exe` to generate a `.lib` file. The .lib file will be output in the same folder as the selected .dll

## Troubleshooting

- Ensure that the Visual Studio tools (`dumpbin`, `lib.exe`) are in your system's PATH.
- If you encounter issues with Visual Studio not being recognized, follow the installation guide for setting up Visual Studio Build Tools [here](https://visualstudio.microsoft.com/visual-cpp-build-tools/).

## Support This Project

If you found this tool useful, consider buying me a coffee! Your support helps me keep making cool utilities like this.  

[![Donate via PayPal](https://img.shields.io/badge/Donate-PayPal-blue.svg)](https://www.paypal.com/donate/?hosted_button_id=RC5Y5MH5FWU3Q)
