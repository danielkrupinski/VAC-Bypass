# VAC Bypass

Valve Anti-Cheat bypass written in C.

## Getting started

### Prerequisites
Microsoft Visual Studio 2019 (preferably latest version i.e. 16.2.5), platform toolset v142 and Windows SDK 10.0 are required in order to compile VAC Bypass. If you don't have ones, you can download VS [here](https://visualstudio.microsoft.com/) (Windows SDK is installed during Visual Studio Setup).

### Cloning
The very first step in order to compile VAC Bypass is to clone this repo from GitHub to your local computer. Git is required to step futher, if not installed download it [here](https://git-scm.com). Open git bash / git cmd / cmd and enter following command:
```
git clone https://github.com/danielkrupinski/VAC-Bypass.git
```
`VAC-Bypass` folder should have been succesfully created, containing all the source files.

### Compiling from source
When you have equiped a copy of source code, next step is opening **VAC-Bypass.sln** in Microsoft Visual Studio 2019.

Then change build configuration to `Release | x86` and simply press **Build solution**.

If everything went right you should receive `VAC-Bypass.dll`  binary file.

### Loading

It is mandatory to strictly follow each step of loading in order to make bypass work.

**Method 1**:
1. Close Steam client if open.
1. Disconnect from the internet.
1. Run Steam as Administrator.
1. Inject `VAC-Bypass.dll` into `Steam.exe` process.
1. After successful injection messagebox saying `Initialization was successful!` should appear.
1. Reconnect to the internet.
1. Press `Retry` in steam window saying 'Could not connect to Steam servers'.

**Method 2**:
1. Close Steam client if open.
1. Compile and run [VAC Bypass Loader](https://github.com/danielkrupinski/VAC-Bypass-Loader)

## Experiment
Bypass has been tested with CS:GO game and Cheat Engine cheating program attached to the game process.

Without bypass:
* [VAC Error](https://support.steampowered.com/kb_article.php?ref=2117-ilzv-2837), then VAC Ban within an hour.

With bypass:
* No [VAC Error](https://support.steampowered.com/kb_article.php?ref=2117-ilzv-2837) during play, no VAC Ban at all.

## How it works
The goal is to make https://github.com/danielkrupinski/VAC/blob/2eeb40e38d0f0d7b828dbacb663ee00aef15c1ca/VAC/Utils.c#L187
function return `false` then VAC aborts scan for cheats. It can be done by bypassing [this check](https://github.com/danielkrupinski/VAC/blob/2eeb40e38d0f0d7b828dbacb663ee00aef15c1ca/VAC/Utils.c#L195) for example.

## See also
- [VAC](https://github.com/danielkrupinski/vac) - source code of Valve Anti-Cheat obtained from disassembly of compiled modules.
- [VAC Bypass Loader](https://github.com/danielkrupinski/vac) - loader for VAC Bypas written in C.

## License
> Copyright (c) 2019 Daniel Krupiński

This project is licensed under the [MIT License](https://opensource.org/licenses/mit-license.php) - see the [LICENSE](LICENSE) file for details.
