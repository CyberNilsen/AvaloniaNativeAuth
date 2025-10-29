\# AkademiAuth — macOS Biometric Authentication for Avalonia (.NET)



\*\*AkademiAuth\*\* is a native macOS binary that enables secure biometric authentication (Touch ID) with password fallback. It’s designed for Avalonia and other .NET desktop apps that can’t access macOS’s `LocalAuthentication` framework directly.



---



\## 🔐 Features



\- ✅ Touch ID authentication via macOS system prompt

\- ✅ Automatic fallback to password if biometrics unavailable

\- ✅ Secure, OS-enforced identity verification

\- ✅ Simple exit code interface for .NET integration

\- ✅ No UI — uses native macOS dialogs



---



\## 🧰 Requirements



\- macOS 10.13+

\- Avalonia or any .NET 6+ desktop app

\- This repo’s precompiled binary: `AkademiAuth`



---



\## 📦 Setup



\### 1. Add the binary to your project



Place the `AkademiAuth` binary in your Avalonia project folder:



```

bash
Assets/Helpers/AkademiAuth
```



Then update your `.csproj` to include it:



```
bash
<ItemGroup>

&nbsp; <Content Include="Assets/Helpers/AkademiAuth">

&nbsp;   <CopyToOutputDirectory>PreserveNewest</CopyToOutputDirectory>

&nbsp; </Content>

</ItemGroup>
```

### 2. Add the authentication service



```
bash
using System.Diagnostics;

using System.Runtime.InteropServices;

using System.Threading.Tasks;

using System.IO;



public class MacOSAuthService : ISecureAuthService

{

&nbsp;   public async Task<bool> AuthenticateAsync(string reason)

&nbsp;   {

&nbsp;       if (!RuntimeInformation.IsOSPlatform(OSPlatform.OSX))

&nbsp;           return false;



&nbsp;       var helperPath = Path.Combine(AppContext.BaseDirectory, "Assets", "Helpers", "AkademiAuth");



&nbsp;       if (!File.Exists(helperPath))

&nbsp;           return false;



&nbsp;       var process = new Process

&nbsp;       {

&nbsp;           StartInfo = new ProcessStartInfo

&nbsp;           {

&nbsp;               FileName = helperPath,

&nbsp;               UseShellExecute = false,

&nbsp;               RedirectStandardOutput = true,

&nbsp;               RedirectStandardError = true,

&nbsp;               CreateNoWindow = true

&nbsp;           }

&nbsp;       };



&nbsp;       process.Start();

&nbsp;       await process.WaitForExitAsync();



&nbsp;       return process.ExitCode == 0;

&nbsp;   }

}
```

