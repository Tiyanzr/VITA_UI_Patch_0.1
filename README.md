# VITA UI Patch 0.1

Patch UI untuk VITA — aplikasi desktop Qt Widgets (C++14, qmake) berisi halaman landing
dengan pemilihan durasi latihan (5/10/15/20 menit).

## Info Repository

| Item | Keterangan |
|---|---|
| Lokal | `D:\Projects\10_Instrumentation\VITA_UI_Patch_0.1` |
| Remote | https://github.com/Tiyanzr/VITA_UI_Patch_0.1.git |
| Branch utama | `main` |
| Toolchain build | Qt 5.11.2 `mingw53_32` (32-bit) + MinGW GCC 5.3.0 |
| Output rilis | `release\VITA_UI_Patch_0.1.exe` |

## Struktur Folder

```
VITA_UI_Patch_0.1/
├─ main.cpp                  # entry point, memuat ui_landingpage.h
├─ Landingpage.ui            # desain halaman (Qt Designer)
├─ VITA_UI_Patch_0.1.pro     # project qmake (TARGET masih VITA_Patch_Testing)
├─ assets/images/            # ikon tombol + gambar referensi desain
├─ release/                  # bundle siap pakai (exe + Qt DLL + plugin)
├─ .vscode/                  # task build & include path Qt
└─ .gitignore                # mengabaikan artefak build & plugin debug
```

## Cara Menjalankan (end user)

1. Ambil seluruh isi repository (jangan hanya menyalin file `.exe`).
2. Buka folder `release\` lalu jalankan `VITA_UI_Patch_0.1.exe` (double click).

### Prasyarat runtime

- Windows 32-bit atau 64-bit (exe bertipe `pei-i386`, jadi tetap jalan di Windows 64-bit).
- **Tidak perlu** install Qt maupun Visual C++ Redistributable — semua runtime sudah dibundel.
- File berikut wajib berada di folder yang sama dengan exe (sudah tersedia di repo):

| File / Folder | Fungsi | Wajib? |
|---|---|---|
| `Qt5Core.dll` | inti Qt (import langsung dari exe) | ya |
| `Qt5Gui.dll` | grafis (import langsung dari exe) | ya |
| `Qt5Widgets.dll` | widget UI (import langsung dari exe) | ya |
| `libgcc_s_dw2-1.dll` | runtime GCC (import langsung dari exe) | ya |
| `libstdc++-6.dll` | runtime C++ MinGW | ya |
| `libwinpthread-1.dll` | thread runtime MinGW (dipakai Qt5Core) | ya |
| `platforms\qwindows.dll` | plugin platform Windows — tanpa ini aplikasi gagal start | ya |
| `imageformats\qjpeg.dll` | loader gambar JPEG | ya bila ada aset JPEG |
| `imageformats\qgif.dll`, `qico.dll`, `qsvg.dll`, dll. | loader format gambar lain | opsional |
| `styles\qwindowsvistastyle.dll` | tema native Windows | opsional |
| `libEGL.dll`, `libGLESV2.dll`, `D3Dcompiler_47.dll`, `opengl32sw.dll` | fallback OpenGL/ANGLE | opsional (app tidak pakai OpenGL) |

Plugin wajib tetap berada di subfolder `release\platforms\`. Bila exe dipindah sendirian,
aplikasi akan error *"This application failed to start because no Qt platform plugin could be
initialized"*.

### Yang belum di-commit (sengaja)

Agar repo tidak membengkak, file berikut diabaikan lewat `.gitignore` (tetap ada di mesin lokal):

- `release\platforms\qwindowsd.dll`, `qminimald.dll`, `qoffscreend.dll` — plugin khusus build debug (±52 MB).
- `release\translations\*.qm` — aplikasi tidak memakai `QTranslator`.
- `Makefile*`, `.qmake.stash`, `*.o`, `ui_*.h` — hasil generate qmake/uic.

## Cara Build dari Source

Prasyarat: Qt 5.11.2 MinGW 32-bit terpasang di `C:\Qt\Qt5.11.2`.

```powershell
# dari folder proyek
& "C:\Qt\Qt5.11.2\5.11.2\mingw53_32\bin\qmake.exe" VITA_UI_Patch_0.1.pro
mingw32-make -j4
```

Atau pakai task VS Code **Build Qt (QMake)** (`.vscode/task.json`).

Hasil build bernama `VITA_Patch_Testing.exe` (sesuai `TARGET` di `.pro`), lalu disalin/di-rename
menjadi `release\VITA_UI_Patch_0.1.exe`. Nama file project sudah `VITA_UI_Patch_0.1.pro`, tetapi
`TARGET` di dalamnya masih `VITA_Patch_Testing`; ubah `TARGET` bila ingin nama output konsisten.

Deploy ulang dependency (misal setelah menambah modul Qt):

```powershell
& "C:\Qt\Qt5.11.2\5.11.2\mingw53_32\bin\windeployqt.exe" --release --no-translations release\VITA_UI_Patch_0.1.exe
```

## Catatan / Known Issue

1. **Path gambar masih absolut.** `Landingpage.ui` (dan `ui_landingpage.h` hasil generate)
   mereferensikan:
   - `D:/Projects/10_Instrumentation/VITA_Patch_Testing/assets/images/btn*.png` (stylesheet tombol)
   - `../../../Downloads/Landing Page.png` (pixmap background)

   Efeknya, di mesin/folder lain ikon tombol dan background bisa tidak muncul tanpa error.
   Perbaikan yang disarankan: pindahkan aset ke Qt Resource (`.qrc`) atau ubah ke path relatif
   `assets/images/...`, lalu generate ulang dengan `qmake` + `make`.
2. Nama `TARGET` di `.pro` (`VITA_Patch_Testing`) belum sama dengan nama exe rilis
   (`VITA_UI_Patch_0.1`).
3. `assets/images/Landing Page.png`, `Form Student.png`, dan `Scenario*.png` saat ini hanya
   gambar referensi desain, belum di-bundle sebagai resource aplikasi.

## Checklist

- [x] `git init` dengan branch `main`
- [x] Remote `origin` terhubung ke GitHub
- [x] Source Qt (`main.cpp`, `Landingpage.ui`, `.pro`) masuk repo
- [x] Bundle `release/` (exe + Qt DLL) diuji jalan di Windows
- [ ] Migrasi path aset ke `.qrc` / path relatif
- [ ] Selaraskan `TARGET` di `.pro` dengan nama exe rilis
