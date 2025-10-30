# AvaloniaNativeAuth
## 🧩 Native Authentication Binaries for Avalonia (.NET)

AvaloniaNativeAuth provides ready-to-use native authentication programs for Windows and macOS, enabling Avalonia and other .NET desktop apps to securely use Touch ID or Windows Hello for local user authentication — without needing direct OS-specific bindings.

## 🚀 Overview

Avalonia doesn’t directly expose native biometric APIs on macOS or Windows.
This repository solves that by including small native executables that your .NET app can call to perform OS-level authentication, then return a simple exit code indicating success or failure.

These binaries can be called from Avalonia (or any .NET 6+) project using System.Diagnostics.Process.

## 🖥️ Platforms
| Platform |	Binary |	Language |	Features |
| macOS |	AkademiAuth |	Swift |	Touch ID authentication with password fallback |
| Windows |	WinHelloAuth.exe |	C++ |	Windows Hello login prompt and verification |
