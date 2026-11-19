# VITA UI Patch 0.1

Dummy README — dipakai untuk memastikan folder lokal sudah terhubung dengan repository GitHub.

## Info Repository

| Item | Keterangan |
|---|---|
| Lokal | `D:\Projects\10_Instrumentation\VITA_UI_Patch_0.1` |
| Remote | https://github.com/Tiyanzr/VITA_UI_Patch_0.1.git |
| Branch utama | `main` |
| Status | Tahap awal / dummy (belum ada source code) |

## Rencana Isi

Patch UI untuk VITA, rencananya memakai Qt Widgets dengan qmake (C++14), mengikuti pola percobaan di folder `VITA_Patch_Testing`:

- `main.cpp` — entry point aplikasi
- `*.ui` — desain halaman (Qt Designer)
- `*.pro` — konfigurasi qmake

## Cara Build (rencana)

```powershell
qmake VITA_UI_Patch_0.1.pro
mingw32-make        # atau nmake / jom sesuai toolchain
```

## Checklist

- [x] `git init` dengan branch `main`
- [x] Remote `origin` terhubung ke GitHub
- [x] Push pertama (tes koneksi)
- [ ] Tambahkan source code UI patch

## Catatan

Isi repository ini masih placeholder. README akan diperbarui setelah struktur proyek final ditentukan.
