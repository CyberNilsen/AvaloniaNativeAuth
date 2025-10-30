# WinHelloAuth

🔐 Native Windows Hello Authentication Helper for Avalonia (.NET) and Desktop Apps

WinHelloAuth is a lightweight native C++ executable that triggers the Windows Hello authentication prompt.
It’s designed for Avalonia or other .NET desktop applications that need secure user verification through Windows Hello without directly using WinRT APIs.

---

## ⚙️ Overview

The program uses the Windows.Security.Credentials.UI API from the Windows Runtime (WinRT) to show the system’s native authentication dialog.
It waits for the user to verify their identity using Windows Hello (face, fingerprint, or PIN), and returns a simple exit code representing the result.

---

## 📁 File Structure

Windows/
├── WinHelloAuth.exe     # Prebuilt Windows Hello authentication binary
├── main.cpp             # Source code (WinRT C++ implementation)
└── README.md            # (this file)

---

## 🧠 How It Works

1. Initializes the Windows Runtime apartment
2. Checks if Windows Hello is available on the device
3. Displays a system authentication prompt ("Bekreft identitet")
4. Returns an exit code based on the authentication result

---

## 📜 Exit Codes

0: Authentication successful
1: Authentication failed or cancelled
2: Windows Hello not available

---

## 💻 Source Code

#include <winrt/Windows.Security.Credentials.UI.h>
#include <winrt/Windows.Foundation.h>
#include <iostream>

using namespace winrt;
using namespace Windows::Security::Credentials::UI;
using namespace Windows::Foundation;

int main()
{
    init_apartment();

    auto availability = UserConsentVerifier::CheckAvailabilityAsync().get();

    if (availability != UserConsentVerifierAvailability::Available)
        return 2;

    auto result = UserConsentVerifier::RequestVerificationAsync(L"Bekreft identitet").get();

    if (result == UserConsentVerificationResult::Verified)
        return 0;
    else
        return 1;
}

---

## 🧱 Building from Source

🪟 Requirements:
- Windows 10 or newer
- Visual Studio 2019 / 2022 with C++/WinRT support
- Windows SDK 10.0.18362.0 or higher

🧩 Build Steps:

Open Developer Command Prompt for Visual Studio and run:
cl main.cpp /await /std:c++20 /EHsc /Fe:WinHelloAuth.exe

This will produce WinHelloAuth.exe in the same folder.

Optional Visual Studio build steps:
1. Create a new Console Application project
2. Add main.cpp
3. Enable Consume Windows Runtime Extension (/await)
4. Link WindowsApp.lib
5. Build in Release mode

---

## 🧩 Integration with Avalonia / .NET

Example C# usage:

using System;
using System.Diagnostics;
using System.IO;
using System.Threading.Tasks;

public class WindowsHelloService
{
    public async Task<bool> AuthenticateAsync()
    {
        string exePath = Path.Combine(AppContext.BaseDirectory, "Assets", "Helpers", "WinHelloAuth.exe");

        if (!File.Exists(exePath))
            return false;

        var process = new Process
        {
            StartInfo = new ProcessStartInfo
            {
                FileName = exePath,
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

Usage:
bool result = await new WindowsHelloService().AuthenticateAsync();
if (result)
    Console.WriteLine("User verified!");
else
    Console.WriteLine("Authentication failed or unavailable.");

---

## 🪟 Windows Hello Capabilities

- Face recognition
- Fingerprint recognition
- PIN fallback
- Secure system dialog (no custom UI)
- Enforced by Windows security subsystem

---

## 🧩 Use Cases

- Unlocking secure sections of an Avalonia app
- Biometric login for password managers
- Two-step verification for sensitive actions
- Cross-platform authentication (macOS Touch ID + Windows Hello)

---

## 📦 License

MIT — free to use, modify, and distribute.

---

## 🙌 Credits

Created by CyberNilsen  
Part of the AvaloniaNativeAuth project for cross-platform native authentication.  
GitHub: https://github.com/CyberNilsen

---

## 💬 Notes

- The displayed text ("Bekreft identitet") can be localized.
- Exit code 2 means Windows Hello is not configured.
- The program performs no data collection; all authentication is handled by Windows.
