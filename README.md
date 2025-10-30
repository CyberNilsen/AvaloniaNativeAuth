# AvaloniaNativeAuth

### 🧩 Native Authentication Binaries for Avalonia (.NET)

**AvaloniaNativeAuth** provides **ready-to-use native authentication programs** for **Windows** and **macOS**, enabling Avalonia and other .NET desktop apps to securely use **Touch ID** or **Windows Hello** for local user authentication — without needing direct OS-specific bindings.


## 🚀 Overview

Avalonia doesn’t directly expose native biometric APIs on macOS or Windows.  
This repository solves that by including small native executables that your .NET app can call to perform OS-level authentication, then return a simple exit code indicating success or failure.

These binaries can be called from Avalonia (or any .NET 6+) project using `System.Diagnostics.Process`.


## 🖥️ Platforms

| Platform | Binary | Language | Features |
|-----------|---------|-----------|-----------|
| **macOS** | `AkademiAuth` | Swift | Touch ID authentication with password fallback |
| **Windows** | `WinHelloAuth.exe` | C++ | Windows Hello login prompt and verification |



## 🔐 How It Works

Both programs use the **native OS authentication dialogs**, perform biometric (or fallback password) verification, and then **return an exit code**:

| Exit Code | Meaning |
|------------|----------|
| `0` | Authentication successful |
| `1` | Authentication failed or cancelled |
| `2` | No biometric hardware or feature unavailable |

Your .NET or Avalonia app can run these helpers invisibly and check the exit code to determine the result.


## 🧰 Requirements

- .NET 6+ (for the Avalonia app using the binaries)
- macOS 10.13+ for Touch ID
- Windows 10+ for Windows Hello
- Avalonia 11+ (recommended)


## 💻 Integration Example (Cross-Platform C#)

```csharp
using System;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading.Tasks;

public static class NativeAuthService
{
    public static async Task<bool> AuthenticateAsync()
    {
        string fileName;

        if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
            fileName = Path.Combine(AppContext.BaseDirectory, "Assets", "Helpers", "AkademiAuth");
        else if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
            fileName = Path.Combine(AppContext.BaseDirectory, "Assets", "Helpers", "WinHelloAuth.exe");
        else
            return false;

        if (!File.Exists(fileName))
            return false;

        var process = new Process
        {
            StartInfo = new ProcessStartInfo
            {
                FileName = fileName,
                UseShellExecute = false,
                RedirectStandardOutput = true,
                RedirectStandardError = true,
                CreateNoWindow = true
            }
        };

        process.Start();
        await process.WaitForExitAsync();
        return process.ExitCode == 0;
    }
}

```

Call await NativeAuthService.AuthenticateAsync(); wherever secure user verification is needed.


## 🧱 Building from Source
macOS
```
bash
cd Mac
swiftc touchid-auth.swift -o AkademiAuth
```

Windows
```
bash
cd Windows
cl main.cpp /Fe:WinHelloAuth.exe
```
Both outputs can then be included in your Avalonia project under something like Assets/Helpers/.
 

## 📦 License
MIT — free to use, modify, and distribute. 

## 🙌 Credits
[Cyberilsen](https://github.com/Cybernilsen)
Built for Avalonia and AkademiTrack, and shared for the community.
