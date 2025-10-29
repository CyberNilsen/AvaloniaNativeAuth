# AkademiAuth — macOS Biometric Authentication for Avalonia (.NET)

**AkademiAuth** is a native macOS binary that enables secure biometric authentication (Touch ID) with password fallback. It’s designed for Avalonia and other .NET desktop apps that can’t access macOS’s `LocalAuthentication` framework directly.

---

## 🔐 Features

- ✅ Touch ID authentication via macOS system prompt  
- ✅ Automatic fallback to password if biometrics unavailable  
- ✅ Secure, OS-enforced identity verification  
- ✅ Simple exit code interface for .NET integration  
- ✅ No UI — uses native macOS dialogs  

---

## 🧰 Requirements

- macOS 10.13+  
- Avalonia or any .NET 6+ desktop app  
- This repo’s precompiled binary: `AkademiAuth`  

---

## 📦 Setup

### 1. Add the binary to your project

Place the `AkademiAuth` binary in your Avalonia project folder:

```
bash
Assets/Helpers/AkademiAuth
```

### 2. Add the authentication service

Create a class like this:

```
bash
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using System.IO;

public class MacOSAuthService : ISecureAuthService
{
    public async Task<bool> AuthenticateAsync(string reason)
    {
        if (!RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
            return false;

        var helperPath = Path.Combine(AppContext.BaseDirectory, "Assets", "Helpers", "AkademiAuth");

        if (!File.Exists(helperPath))
            return false;

        var process = new Process
        {
            StartInfo = new ProcessStartInfo
            {
                FileName = helperPath,
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

### 3. Use it in your app

Inject or call MacOSAuthService.AuthenticateAsync(...) wherever you need secure user verification — for example, before showing sensitive content or unlocking settings.

### 📦 License

MIT — free to use, modify, and distribute.

🙌 Credits

Created by [github.com/CyberNilsen](CyberNilsen) for AkademiTrack and the Avalonia community.



