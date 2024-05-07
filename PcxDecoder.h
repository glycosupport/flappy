#ifndef PCX_DECODER_H
#define PCX_DECODER_H


#include <Library/BaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Guid/FileInfo.h>
#include <Protocol/DevicePath.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/SimpleFileSystem.h>
#include <Library/PciLib.h>
#include <Library/BaseMemoryLib.h>

EFI_STATUS PcxDecoderDecodeImage(UINT8* Buffer, UINTN BufferSize, EFI_GRAPHICS_OUTPUT_BLT_PIXEL** BltBuffer, UINTN* BltSize, UINTN* Width, UINTN* Height);

#endif
