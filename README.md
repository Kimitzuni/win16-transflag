# Win16 Trans Flag

This is a trans flag, written in C and compiled using Microsoft Visual C++ 1.5 on
Windows 3.1. This is mostly a modified version of the `HELLO.C` program from the
Windows 1.03 SDK, modified to work under Windows 3.0+ However you obtain your copy
of Windows 3.1 and VC++1.5 is up to you.

## Porter's Note:
It does run under Windows NT 4.0 without recompiling. However, later versions of
Windows require a recompilition due to elements of the Win16 API being missing.

To help you out a bit, you simply will need to comment out the `GetInstanceData`
stuff from line 113 to line 116. This is because `GetInstanceData` doesn't exist
in the Windows API anymore. I tried this on Windows 8 with Visual Studio 2010, and
so (in theory) it should work on Windows 11 with VS2022. Though how it works in
practice - I do not know.

## Additional Note
I don't think I've done some of it correctly, and I am 100% going about it the
purely bruteforce way of drawing multiple rectangles in a set position. And
because of that - It only looks correct in the starting window size. And because
I don't think I've done things correctly, this program might have memory leaks
due to me being incompetent with the Win16 API.

## Building on Windows 3.1
To build on Windows 3.1, you will need to have a copy of Microsoft Visual C++ 1.5
(or later) installed. Once you have that, you can simply open the `HELLO.MAK` file
from in VC++1.5, and build.

## Preview
![The Trans Flag](https://link.storjshare.io/raw/jvxikkhiqnksyeatwcn3iigoa3ta/techlgbt/media_attachments/files/109/667/719/965/591/782/small/fe3711889cb5dbe7.png)

[Twitter Post (@Kimitzuni)](https://twitter.com/Kimitzuni/status/1612986760312627200) |
[Mastodon Post (@kimitzuni@tech.lgbt)](https://tech.lgbt/@kimitzuni/109667720255141430)

## LICENSE
```
Win16 Trans Flag
Copyright (c) Rebecca White 2023
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
```
