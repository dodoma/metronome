#ifndef __EEPROM_H__
#define __EEPROM_H__

#define EEPROM_ADDR 0x2000        /* 2000 ~ 2FFF 共4K字节，8个扇区，每扇区512字节 */
#define EEPROM_SECTOR_STEP 0x200  /* 200 512字节，下一个扇区的起始地址 */

void eepr_erase(uint16_t addr);
void eepr_write(uint16_t addr, uint8_t *buf, uint16_t num);
void eepr_read(uint16_t addr, uint8_t *buf, uint16_t num);

#endif
