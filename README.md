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
├─ VITA_UI_Patch_0.1.pro     # project qmake (TARGET = VITA_UI_Patch_0.1)
├─ resource.qrc               # aset gambar sebagai Qt Resource (prefix /images)
├─ assets/images/            # ikon tombol + background halaman
├─ release/                  # bundle siap pakai (exe + Qt DLL + plugin)
├─ .vscode/                  # task build & include path Qt
└─ .gitignore                # mengabaikan artefak build & plugin debug
```

## Mulai Cepat

### Cuma mau menjalankan aplikasinya

Unduh folder **[release/](https://github.com/Tiyanzr/VITA_UI_Patch_0.1/tree/main/release)**
(salin semua isinya, jangan hanya file `.exe`), lalu jalankan:

```powershell
.\release\VITA_UI_Patch_0.1.exe
```

> `.exe` tidak bisa jalan sendirian — harus satu folder dengan `Qt5*.dll`, `libgcc_s_dw2-1.dll`,
> `libstdc++-6.dll`, `libwinpthread-1.dll`, dan `platforms\qwindows.dll`.
> Rinciannya ada di [Prasyarat Runtime](#prasyarat-runtime-bundle-exe).

### Mau build dari source

Butuh **Qt 5.11.2 MinGW 32-bit** ([arsip installer](https://download.qt.io/archive/qt/5.11/5.11.2/),
pilih `qt-opensource-windows-x86-mingw530-5.11.2.exe`).

```powershell
# ganti <folder-tujuan> dengan lokasi pilihan Anda, mis. D:\Projects\VITA_UI_Patch_0.1
git clone https://github.com/Tiyanzr/VITA_UI_Patch_0.1.git "<folder-tujuan>"
cd "<folder-tujuan>"

# pastikan compiler Qt (GCC 5.3.0) dipakai lebih dulu daripada compiler lain di PATH
$env:PATH = "C:\Qt\Qt5.11.2\5.11.2\mingw53_32\bin;C:\Qt\Qt5.11.2\Tools\mingw530_32\bin;" + $env:PATH

qmake VITA_UI_Patch_0.1.pro
mingw32-make -f Makefile.Release -j4

# jalankan
.\release\VITA_UI_Patch_0.1.exe
```

Untuk **CMD**, ganti baris PATH menjadi:

```bat
set PATH=C:\Qt\Qt5.11.2\5.11.2\mingw53_32\bin;C:\Qt\Qt5.11.2\Tools\mingw530_32\bin;%PATH%
```

Penjelasan lengkap (deploy `windeployqt`, error `0xC0000139`) ada di
[Cara Build dari Source](#cara-build-dari-source).

## Prasyarat Runtime (bundle exe)

Setelah ZIP diekstrak, aplikasi dijalankan langsung dari folder `release\` — tidak ada proses
instalasi. Yang perlu dipastikan:

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

## Yang belum di-commit (sengaja)

Agar repo tidak membengkak, file berikut diabaikan lewat `.gitignore` (tetap ada di mesin lokal):

- `release\platforms\qwindowsd.dll`, `qminimald.dll`, `qoffscreend.dll` — plugin khusus build debug (±52 MB).
- `release\translations\*.qm` — aplikasi tidak memakai `QTranslator`.
- `Makefile*`, `.qmake.stash`, `*.o`, `ui_*.h` — hasil generate qmake/uic.

## Cara Build dari Source

Prasyarat: Qt 5.11.2 MinGW 32-bit terpasang di `C:\Qt\Qt5.11.2`.

> **Penting:** `Makefile` memanggil `g++` tanpa path absolut, jadi compiler pertama di `PATH` yang
> dipakai. Pastikan `C:\Qt\Qt5.11.2\Tools\mingw530_32\bin` berada **sebelum** compiler lain
> (mis. Strawberry Perl 4.9.2). Kalau tidak, exe akan ter-link dengan `libgcc_s_sjlj-1.dll` dan
> gagal start dengan exit code `0xC0000139` (STATUS_ENTRYPOINT_NOT_FOUND).

```powershell
# dari folder proyek
$env:PATH = "C:\Qt\Qt5.11.2\5.11.2\mingw53_32\bin;C:\Qt\Qt5.11.2\Tools\mingw530_32\bin;" + $env:PATH
qmake VITA_UI_Patch_0.1.pro
mingw32-make -f Makefile.Release -j4
```

Atau pakai task VS Code **Build Qt (QMake)** (`.vscode/task.json`; PATH-nya sudah diatur di
`.vscode/settings.json`).

Hasil build langsung bernama `release\VITA_UI_Patch_0.1.exe` (sesuai `TARGET` di `.pro`).
Resources dari `resource.qrc` dikompilasi menjadi `release\qrc_resource.o` dan ikut di-link,
sehingga gambar tidak lagi dibaca dari file eksternal saat runtime.

Deploy ulang dependency (misal setelah menambah modul Qt):

```powershell
& "C:\Qt\Qt5.11.2\5.11.2\mingw53_32\bin\windeployqt.exe" --release --no-translations release\VITA_UI_Patch_0.1.exe
```

## Catatan Desain

1. **Aset memakai Qt Resource.** `Landingpage.ui` mereferensikan `:/images/...` (prefix di
   `resource.qrc`) untuk background dan ikon tombol durasi. Tidak ada lagi path `D:/...` atau
   `../../../Downloads/...`, sehingga exe bisa dijalankan dari folder mana pun.
2. **Label scenario tercetak di background.** `Scenario (1).png` sudah memuat teks
   *Normal Condition*, *High PEEP*, dst. Karena itu widget `radioButton_1..5` tetap 20×20 tanpa
   jarak (`spacing: 0px`, `color: transparent`) hanya sebagai indikator di atas gambar. Teks pada
   widget tetap diisi di `.ui` karena `main.cpp` membacanya lewat `QRadioButton::text()`.
   Jangan hapus properti `text` radio meski tidak terlihat.
3. **`Scenario.png` tidak di-bundle** karena tidak dipakai (menghemat ±168 KB di exe).
4. **`stackedWidget` `currentIndex` = 0** agar preview Designer dan aplikasi sama-sama mulai dari
   landing page. `main.cpp` juga men-set index 0 secara eksplisit.
5. **`frame`, `frame_2`, `frame_3`, `frame_4` memakai `frameShape = NoFrame`** supaya Qt tidak
   menggambar kotak border di atas gambar desain.

## Checklist

- [x] `git init` dengan branch `main`
- [x] Remote `origin` terhubung ke GitHub
- [x] Source Qt (`main.cpp`, `Landingpage.ui`, `.pro`) masuk repo
- [x] Bundle `release/` (exe + Qt DLL) diuji jalan di Windows
- [x] Migrasi path aset ke `.qrc` / path relatif
- [x] Selaraskan `TARGET` di `.pro` dengan nama exe rilis

