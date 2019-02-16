#pragma once

#include <AK/Types.h>
#include <AK/AKString.h>
#include <SharedGraphics/Size.h>
#include <Kernel/types.h>
#include <Kernel/BlockDevice.h>

class BochsVGADevice final : public BlockDevice {
    AK_MAKE_ETERNAL
public:
    static BochsVGADevice& the();

    BochsVGADevice();

    PhysicalAddress framebuffer_address() const { return m_framebuffer_address; }
    void set_resolution(int width, int height);
    void set_y_offset(int);


    virtual Region* mmap(Process&, LinearAddress preferred_laddr, size_t offset, size_t) override;

    size_t framebuffer_size_in_bytes() const { return m_framebuffer_size.area() * sizeof(dword) * 2; }
    Size framebuffer_size() const { return m_framebuffer_size; }

private:
    virtual const char* class_name() const override { return "BochsVGADevice"; }
    virtual bool can_read(Process&) const override;
    virtual bool can_write(Process&) const override;
    virtual ssize_t read(Process&, byte*, size_t) override;
    virtual ssize_t write(Process&, const byte*, size_t) override;

    void set_register(word index, word value);
    dword find_framebuffer_address();

    PhysicalAddress m_framebuffer_address;
    Size m_framebuffer_size;
};
