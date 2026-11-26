# Samsung NX500 Firmware Recovery Mode (Unbrick Without Disassembly)

A previously undocumented built-in firmware recovery mode on the **Samsung NX500** makes it possible to recover from a **soft brick** (for example after a failed `nx-on-wake` installation, `systemctl rescue`, or broken hibernation/rootfs state) using an official firmware file on an SD card—**without disassembly, motherboard test-point shorting, UART wiring, Samsung service software, or `downloader.bin`**.

> **Scope and verification:** Independently identified and physically verified on real **Samsung NX500** hardware (soft-bricked during an `nx-on-wake` installation, booted into Recovery Mode, and restored end-to-end with official `nx500.bin` v1.12 through `F/W Check` -> `Updating` -> `Update Finish` to normal operation). **Not verified on the NX1** or other Samsung NX cameras (the NX1 uses different GPIO mappings and has no flip-up display).

---

## Recovery Button Combination (NX500)

Prepare an SD card first:

1. Download an official, unmodified Samsung NX500 firmware package (for example **v1.12** from Samsung Download Center or the [NX firmware archive](https://nxfiles.nx.tc/files/NX500/Firmware/)).
2. Extract `nx500.bin` to the **root** of a clean **FAT32** SD card.

Trigger Recovery Mode on the camera:

1. Remove the battery from the camera and insert the prepared FAT32 SD card.
2. Flip the rear display **fully upward into the selfie position**.
3. Reinsert the battery (leave the power switch **OFF**).
4. Simultaneously press and hold:
   - **MOBILE (Wi-Fi)** button
   - **AEL** button
   - **Shutter button** (fully depressed)
5. While holding all three buttons, switch the camera power **ON**.
6. Once the blue **Recovery Mode** screen appears (`F/W Check` / `Update` / `Update Finish`), release the buttons.
7. Follow the on-screen instruction: **hold down the shutter button** to begin flashing `nx500.bin` from the SD card.

### Important Warnings

- **Use official, unmodified `nx500.bin` firmware only.**
- **Use a well-charged battery and do not power off or remove the battery** while `Updating / Do not power off.` is displayed. Wait until `Update Finish` completes.
- This recovers **soft bricks** where the bootloader (`boot0`) and internal recovery kernel (`rImage` / `p13`) are still intact. If `boot0` itself is damaged or the camera cannot reach `boot0`, hardware/Boot ROM recovery (`downloader.bin` or UART bootloader shell) is still required.

---

## Technical Background and Evidence

Reverse engineering of the NX500 `boot0` bootloader (documented in [`WApaperplane/nx500-dnloader`](https://github.com/WApaperplane/nx500-dnloader/blob/main/docs/BOOT0_ANATOMY.md)) showed a recovery branch that checks four GPIO pins and jumps to the internal `rImage` recovery kernel (`load_image(0x86007FC0, 0x002D4801, 0x4C4C)`) after enabling SD card power (`GPIO 179` / `GPIO_SD_3_3V_CTL`).

Cross-referencing those four GPIO numbers against Samsung's official NX500 GPL kernel definitions (`include/gpio_map_nx500.h`, where `DRIME5_GPIOx(y) = x * 8 + y`) reveals that all four are externally accessible controls rather than internal motherboard shorting pads:

| GPIO | Macro in `gpio_map_nx500.h` | Kernel Definition | Physical Control on NX500 |
|---|---|---|---|
| `19` | `DRIME5_GPIO2(3)` | `GPIO_WIFI_KEY` | MOBILE (Wi-Fi) button |
| `27` | `DRIME5_GPIO3(3)` | `GPIO_SHUTTER_KEY2` | Full shutter button press |
| `30` | `DRIME5_GPIO3(6)` | `GPIO_FLIPUP_INT` | Display flipped fully upward (selfie position) |
| `31` | `DRIME5_GPIO3(7)` | `GPIO_AEL_KEY` | AEL button |

When all four inputs read active-low (`0`) at cold boot, `boot0` logs `"Starting A9 for recovery."`, powers the SD slot, and launches the internal recovery kernel (`rImage`) to validate and flash `nx500.bin` from the SD card.

---

## Credits and References

- **WApaperplane** ([`WApaperplane/nx500-dnloader`](https://github.com/WApaperplane/nx500-dnloader/blob/main/docs/BOOT0_ANATOMY.md)): disassembly of `boot0` and identification of the four-GPIO recovery branch.
- **ge0rg** ([`ge0rg/samsung-nx-hacks`](https://github.com/ge0rg/samsung-nx-hacks), [issue #121](https://github.com/ottokiksmaler/nx500_nx1_modding/issues/121)): documentation of the SLP format, `rImage` / `fw_recovery`, and bootloader dumps.
- **REVPKD**: independent correlation of the `boot0` GPIO branch with Samsung GPL kernel GPIO definitions and physical hardware verification of the closed-case NX500 unbrick flow.
