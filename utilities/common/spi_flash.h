#ifndef __SPI_FLASH_H
#define __SPI_FLASH_H

#ifdef SPI_FLASH_AUTO
  #include "spi_flash_auto.h"
#else

#ifdef __cplusplus
 extern "C" {
#endif
#include "ht32_board.h"

/* Includes ------------------------------------------------------------------------------------------------*/


/** @addtogroup Utilities
  * @{
  */

/** @addtogroup Common
  * @{
  */

/** @addtogroup SPI_FLASH SPI_FLASH
  * @{
  */


/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup SPI_FLASH_Exported_Constants SPI FLASH exported constants
  * @{
  */
#define SPI_FLASH_PAGESIZE              256
#define SPI_FLASH_SECTOR_SIZE           (1024 * 4)

#define SPI_FLASH_CMD_WRITE             0x02  /*!< Program the selected page instruction                    */
#define SPI_FLASH_CMD_WRSR              0x01  /*!< Write Status Register instruction                        */
#define SPI_FLASH_CMD_WREN              0x06  /*!< Write enable instruction                                 */
#define SPI_FLASH_CMD_WRDI              0x04  /*!< Write disable instruction                                */

#define SPI_FLASH_CMD_READ              0x03  /*!< Read Data instruction                                    */
#define SPI_FLASH_CMD_FREAD             0x0B  /*!< Read Data at high speed instruction                      */
#define SPI_FLASH_CMD_DREAD             0x3B  /*!< Dual Output Mode Read instruction                        */
#define SPI_FLASH_CMD_RDSR              0x05  /*!< Read Status Register instruction                         */
#define SPI_FLASH_CMD_RDID              0x9F  /*!< Read JEDEC ID instruction                                */
#define SPI_FLASH_CMD_REMS              0x90  /*!< Read electronic manufacturer & device ID instruction     */
#define SPI_FLASH_CMD_SE                0x20  /*!< Sector Erase instruction                                 */
#define SPI_FLASH_CMD_BE                0x52  /*!< Block Erase instruction                                  */
#define SPI_FLASH_CMD_CE                0x60  /*!< Chip Erase instruction                                   */

#define SPI_FLASH_BUSY_FLAG             0x01  /*!< Write operation in progress                              */

#define SPI_FLASH_DUMMY_BYTE            0x00

#define MX25L1606E_FLASH_JEDEC_ID       0xC22015
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------------------------------------*/
/** @defgroup SPI_FLASH_Exported_Macros SPI FLASH exported macros
  * @{
  */
#define SPI_FLASH_SEL_ACTIVE()      GPIO_ClearOutBits(GPIO_PORT[FLASH_SPI_SEL_GPIO_ID], FLASH_SPI_SEL_GPIO_PIN)
#define SPI_FLASH_SEL_INACTIVE()    GPIO_SetOutBits(GPIO_PORT[FLASH_SPI_SEL_GPIO_ID], FLASH_SPI_SEL_GPIO_PIN)
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup SPI_FLASH_Exported_Functions SPI FLASH exported functions
  * @{
  */
u32 SPI_FLASH_Init(void);
u32 SPI_FLASH_ReadJEDECID(void);
void SPI_FLASH_ChipErase(void);
void SPI_FLASH_SectorErase(u32 SectorAddr);
void SPI_FLASH_BlockErase(u32 BlockAddr);
void SPI_FLASH_PageWrite(u8* WriteBuffer, u32 WriteAddr, u32 NumOfWriteByte);
void SPI_FLASH_BufferWrite(u8* WriteBuffer, u32 WriteAddr, u32 NumOfWriteByte);
void SPI_FLASH_BufferRead(u8* ReadBuffer, u32 ReadAddr, u32 NumOfReadByte);
void SPI_FLASH_BufferDualRead(u16* ReadBuffer, u32 ReadAddr, u32 NumOfReadByte);
void SPI_FLASH_WriteStatus(u32 Value);
u16 SPI_FLASH_SendByte(u8 byte);
void SPI_FLASH_WriteEnable(void);
void SPI_FLASH_WriteDisable(void);
void SPI_FLASH_WaitForWriteEnd(void);
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif

#endif /* __SPI_FLASH_H ------------------------------------------------------------------------------------*/
