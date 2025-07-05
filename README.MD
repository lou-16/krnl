# krnl
# a WIP kernel created from scratch in C.
 
![Alt text]( https://github.com/lou-16/krnl/blob/main/docs/mykernel.png "hello world")
# krnl — A Simple x86 Kernel

Welcome to **krnl**, a minimal 32-bit x86 kernel built from scratch. It boots using GRUB, prints via serial, and lays the foundation for more advanced OS concepts like memory management, paging, and drivers.

![Boot Screenshot](docs/assets/boot-success.png)

---

## ✨ Features

- 🧱 Written in C + NASM (Assembly)
- 📦 Multiboot-compliant, booted via GRUB
- 📜 Serial port output (COM1)
- 🧠 GDT (Global Descriptor Table) setup
- 🧼 Clean ISO build pipeline using CMake + Bash
- 🗺️ Memory map parsing from Multiboot

---

## 🚀 Booting the Kernel

### Build & ISO Generation

```bash
./build_iso.sh
