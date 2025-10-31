# krnl
# a WIP kernel created from scratch in C.
 
![Alt text]( https://github.com/lou-16/krnl/blob/main/docs/mykernel.png "hello world")
# krnl — A Simple x86 Kernel

Welcome to **krnl**, a minimal 32-bit x86 kernel built from scratch. It boots using GRUB, prints via serial, and lays the foundation for more advanced OS concepts like memory management, paging, and drivers.

## History / Devlog

I also implemented some simple interrupts. for the first 32 interrupts, which are CPU's own internal IRQs, i simply created a stub that resets them to 0 for now. but the later 8, and then 8 ISRs are for the Master and Slave PIC. which obviously means that this isn't relying on the modern APIC microcontrollers. which is fine.

Next i aim to use the IRQ0 and IRQ1, which are essentially the IRQ32, and IRQ33 if we look at the IDT, for timing (using PIT), and for a PS/2 Keyboard that will allow me to get some input. which means in the near future, i'll be able to get a tty working. Meanwhile i implemented 2 syscalls, although i have not added a syscall_table that i can use to create a table for my syscalls. so if im being honest, its really just a sleep and a abort function for now.

- lou-16 (30-10-2025)

Got the Bochs Graphics Adapter (BGA) working with a simple driver — enough to get a framebuffer up and running. Added a basic PCI config reader to detect devices like the BGA.

Cleaned up the project quite a bit: removed old video and fs headers, simplified CMakeLists.txt, and trimmed unused files.

Set up the first version of memory management, with kmalloc and kfree handling full-page allocations for now. This will later evolve into a proper heap allocator.

Implemented some basic interrupts — the first 32 CPU exceptions are stubbed, while the PIC handles IRQs 32–47. Not using APIC yet, just the legacy setup.

Next up: IRQ0 (timer) and IRQ1 (keyboard) for the PIT and PS/2 input, which should finally get a TTY working. Also added two early syscalls (sleep and abort) — no syscall table yet, just enough to test the mechanism.

- lou-16 (1-11-2025)

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
