/*
 * Copyright (c) 2021, Nico Weber <thakis@chromium.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <AK/Types.h>
#include <Kernel/Prekernel/Arch/aarch64/Mailbox.h>

extern "C" [[noreturn]] void halt();

extern "C" [[noreturn]] void init();
extern "C" [[noreturn]] void init()
{
    [[maybe_unused]] u32 firmware_version = Prekernel::Mailbox::query_firmware_version();
    halt();
}

// FIXME: Share this with the Intel Prekernel.
extern size_t __stack_chk_guard;
size_t __stack_chk_guard;
extern "C" [[noreturn]] void __stack_chk_fail();

[[noreturn]] void halt()
{
    for (;;) {
        asm volatile("wfi");
    }
}

void __stack_chk_fail()
{
    halt();
}
