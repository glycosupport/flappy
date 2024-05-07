#include "PcxDecoder.h"

EFI_STATUS PcxDecoderDecodeImage(
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

    *width = Buffer[8] + (Buffer[9] << 8) + 1;
    *height  = Buffer[10] + (Buffer[11] << 8) + 1; 

    *bltSize = *width * *height;

    // UINTN bltMemSize = *bltSize * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) * 4;

    // Print(L"Width: %d\n", *width);
    // Print(L"Height: %d\n", *height);
    // Print(L"Blt buffer size: %d\n", *bltSize);


    UINTN bltMemSize = *bltSize * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
    // Status = gBS->AllocatePages(AllocateAnyPages,
    //               EfiLoaderData, EFI_SIZE_TO_PAGES(bltMemSize), &PhysBuffer);
    // if (EFI_ERROR(Status)) {
    //     Print(L"Unable to allocate Buffer\n");
    //     return EFI_NOT_STARTED;
    // }

    // bltBuffer = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)(UINTN)PhysBuffer;

    *bltBuffer = AllocatePool(bltMemSize); 

    // UINTN paletteSize = BufferSize - 768;
    // UINTN* palette = (UINTN*)AllocatePool(paletteSize * sizeof(UINTN));

    // for (UINTN i = 768, j = 0; i < BufferSize && j < paletteSize; i++, j++) {
    //     palette[j] = Buffer[i];
    //     // if (j < 20) {
    //     //     Print(L"%d ", palette[j]);
    //     // }
    // }

    // Print(L"%d\n", paletteSize);

    // UINTN offset = 128;
    // UINTN p = 0;
    // UINTN pos = 0;
    // UINTN length = 0;
    // UINTN val = 0;

    // UINTN planes = 1;

    // UINTN* _bltBuffer = (UINTN*)*bltBuffer;

    // for (UINTN y = 0; y < *height; y++ ){
    //     for (p = 0; p < planes; p++) {
            
    //         pos = 4 * *width * y + p;
            
    //         for (UINTN byte = 0; byte < *width; byte++) {
    //             if (length == 0) {
    //                 if ((Buffer[offset] & 0xC0) == 0xC0) {
    //                     length = Buffer[offset] & 0x3F;
    //                     val = Buffer[offset + 1];
    //                     offset += 2;
    //                 } else {
    //                     length = 1;
    //                     val = Buffer[offset++];
    //                 }
    //             }

    //             length--;

    //             /* Since there may, or may not be blank data at the end of each
    //             scanline, we simply check we're not out of bounds
    //             */
    //             if (byte < *width) {
    //                 if (planes == 3) {
    //                     *(_bltBuffer + pos) = val;
    //                     // add alpha channel
    //                     if (p == planes - 1) {
    //                         *(_bltBuffer + pos + 1) = 255;
    //                     }
    //                 } else {    
    //                     UINTN start = val * 3;

    //                     *(_bltBuffer + pos) = palette[start];
    //                     *(_bltBuffer + pos + 1) = palette[start + 1];
    //                     *(_bltBuffer + pos + 2) = palette[start + 2];
    //                     // alpha channel
    //                     *(_bltBuffer + pos + 3) = 255;
    //                 }

    //                 pos += 4;
    //             }
    //         }
    //     }
    // }
    UINTN  index = 0;            /* Index into compressed scan line buffer */
    UINTN  total = 0;            /* Running total of decoded pixel values  */
    UINTN  byte;                 /* Data byte read from PCX file           */
    UINTN  runcount = 0;         /* Length of decoded pixel run            */
    UINTN  runvalue = 0;         /* Value of decoded pixel run             */
    UINTN  colorIndex = 0;
    UINTN  bufIndex = 128;


    do {
        for (total += runcount; runcount && index < *bltSize; runcount--, index++) {
            if (colorIndex == 0) {
                (*bltBuffer)[index].Reserved = runvalue;    
                colorIndex++;
            } else if (colorIndex == 1) {
                (*bltBuffer)[index].Blue = runvalue;   
                colorIndex++;
            } else if (colorIndex == 2) {
                (*bltBuffer)[index].Green = runvalue;  
                colorIndex++;
            } else if (colorIndex == 3) {
                (*bltBuffer)[index].Red = runvalue;  
                colorIndex = 0;
            }
        }

        if (runcount)           /* Encoded run ran past end of scan line    */
        {
            total -= runcount;  /* Subtract count not written to buffer     */
            return Status;
        }

        byte = Buffer[bufIndex++];                  /* Get next byte    */

        if ((byte & 0xC0) == 0xC0)                  /* Two-byte code    */
        {
            runcount = byte & 0x3F;                 /* Get run count    */
            runvalue = Buffer[bufIndex++];          /* Get pixel value  */
        }
        else                                        /* One byte code    */
        {
            runcount = 1;                           /* Run count is one */
            runvalue = byte;                        /* Pixel value      */
        }

    } while (index < *bltSize); 

    return Status;
}