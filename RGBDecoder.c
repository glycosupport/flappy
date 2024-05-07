#include "RGBDecoder.h"

EFI_STATUS RGBDecoderDecodeImage(
    IN  UINT8 *Buffer,
    IN  UINTN BufferSize,
    IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL **bltBuffer,
    OUT UINTN *bltSize,
    OUT UINTN *width,
    OUT UINTN *height
) {

    EFI_STATUS Status = EFI_SUCCESS;

    // *_bltBuffer = AllocatePool(sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) * *width * *height);
    // CopyMem(*_bltBuffer, Buffer, BufferSize);

    // EFI_PHYSICAL_ADDRESS _PhysBuffer;

    // UINTN _bltMemSize = sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL*);
    // Status = gBS->AllocatePages(AllocateAnyPages,
    //               EfiLoaderData, EFI_SIZE_TO_PAGES(_bltMemSize), &_PhysBuffer);
    // if (EFI_ERROR(Status)) {
    //     Print(L"Unable to allocate Buffer\n");
    //     return EFI_NOT_STARTED;
    // }

    // _bltBuffer = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL**)(UINTN)_PhysBuffer;
    // EFI_GRAPHICS_OUTPUT_BLT_PIXEL *bltBuffer = *_bltBuffer;
    // EFI_PHYSICAL_ADDRESS PhysBuffer;

    // Print(L"Buffer addr: %x\n", Buffer);
    // Print(L"Buffer size: %d\n", BufferSize);
    // Print(L"Blt buffer addr: %x\n", bltBuffer);
    // Print(L"Blt buffer size: %d\n", *bltSize);
    // Print(L"Width: %d\n", *width);
    // Print(L"Height: %d\n", *height);

    // *width = Buffer[8] + (Buffer[9] << 8) + 1;
    // *height  = Buffer[10] + (Buffer[11] << 8) + 1; 

    // *bltSize = *width * *height;

    // UINTN bltMemSize = *bltSize * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) * 4;

    // Print(L"Width: %d\n", *width);
    // Print(L"Height: %d\n", *height);
    // Print(L"Blt buffer size: %d\n", *bltSize);


    // UINTN bltMemSize = *bltSize * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
    // Status = gBS->AllocatePages(AllocateAnyPages,
    //               EfiLoaderData, EFI_SIZE_TO_PAGES(bltMemSize), &PhysBuffer);
    // if (EFI_ERROR(Status)) {
    //     Print(L"Unable to allocate Buffer\n");
    //     return EFI_NOT_STARTED;
    // }

    // bltBuffer = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)(UINTN)PhysBuffer;

    *bltBuffer = AllocatePool(BufferSize); 

    CopyMem(*bltBuffer, Buffer, BufferSize);
    return Status;
}